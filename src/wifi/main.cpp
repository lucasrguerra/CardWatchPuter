#include "wifi/main.h"



uint16_t scanWiFi() {
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	esp_wifi_init(&cfg);
	esp_wifi_set_mode(WIFI_MODE_STA);
	esp_wifi_start();
	wifi_scan_config_t scanConfig = {};
	esp_wifi_scan_start(&scanConfig, true);

    uint16_t numberOfAcessPoints;
    esp_wifi_scan_get_ap_num(&numberOfAcessPoints);
	if (numberOfAcessPoints != 0) {
        acessPointsList = (wifi_ap_record_t *)malloc(sizeof(wifi_ap_record_t) * numberOfAcessPoints);
        esp_wifi_scan_get_ap_records(&numberOfAcessPoints, acessPointsList);
    }

    return numberOfAcessPoints;
}