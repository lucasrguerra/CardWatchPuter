#include "SDCard/main.h"



void initSDCard() {
	SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
	if(!SD.begin(SD_SPI_CS_PIN, SPI, 25000000)) {
		Serial.println("SD Card initialization failed!");
	}

    uint8_t cardType = SD.cardType();
	if (cardType == CARD_NONE) {
		Serial.println("No SD card attached!");
	} else {
		Serial.print("SD Card Type: ");
		if (cardType == CARD_MMC) { Serial.println("MMC"); }
        else if (cardType == CARD_SD) { Serial.println("SDSC"); }
        else if (cardType == CARD_SDHC) { Serial.println("SDHC"); }
        else { Serial.println("UNKNOWN"); }
	}
}



void readFile(fs::FS &fs, const char * path, String &message) {
	File file = fs.open(path);
	if (!file) {
		Serial.println("Failed to open file for reading");
		return;
	}
	
	while (file.available()) {
		message += (char)file.read();
	}
	file.close();
}



void writeFile(fs::FS &fs, const char * path, const String message) {
	File file = fs.open(path, FILE_WRITE);
	if (!file) {
		Serial.println("Failed to open file for writing");
		return;
	}

	if (file.print(message)) {
		Serial.println("File written");
	} else {
		Serial.println("Write failed");
	}
	file.close();
}