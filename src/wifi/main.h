#include <esp_system.h>
#include <esp_wifi.h>



wifi_ap_record_t accessPointInfo;
wifi_ap_record_t *acessPointsList;



void initWiFi();
uint16_t scanWiFi();