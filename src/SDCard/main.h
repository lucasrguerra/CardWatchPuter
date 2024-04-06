#include <SPI.h>
#include <SD.h>



#define SD_SPI_SCK_PIN		GPIO_NUM_40
#define SD_SPI_MISO_PIN		GPIO_NUM_39
#define SD_SPI_MOSI_PIN		GPIO_NUM_14
#define SD_SPI_CS_PIN		GPIO_NUM_12



void initSDCard();
void readFile(fs::FS &fs, const char * path, String &message);
void writeFile(fs::FS &fs, const char * path, const String message);