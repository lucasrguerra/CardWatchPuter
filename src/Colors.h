#include <M5Cardputer.h>
#include "SDCard/main.h"



const char * path_titleColor = "/titleColor.txt";
const char * path_textColor = "/textColor.txt";
const char * path_backgroundColor = "/backgroundColor.txt";
const char * path_brightness = "/screenBrightness.txt";



uint16_t titleColor;
uint16_t textColor;
uint16_t backgroundColor;
uint8_t screenBrightness = 255;



void initColors();
void setColor(uint16_t &variable, String colorName, uint16_t colorDefault);
void saveColor(uint16_t &variable, String colorName, const char * path);
void setBrightness(String brightness, uint8_t defaultBrightness);
void saveBrightness(String brightness);



void initColors() {
	String saved_titleColor = "";
	String saved_textColor = "";
	String saved_backgroundColor = "";
	String saved_brightness = "";

	readFile(SD, path_titleColor, saved_titleColor);
	readFile(SD, path_textColor, saved_textColor);
	readFile(SD, path_backgroundColor, saved_backgroundColor);
	readFile(SD, path_brightness, saved_brightness);

	setColor(titleColor, saved_titleColor, TFT_WHITE);
	setColor(textColor, saved_textColor, TFT_GREEN);
	setColor(backgroundColor, saved_backgroundColor, TFT_BLACK);
	setBrightness(saved_brightness, 255);
}



void setColor(uint16_t &variable, String colorName, uint16_t colorDefault) {
	if (colorName == "White") { variable = TFT_WHITE; }
	else if (colorName == "Green") { variable = TFT_GREEN; }
	else if (colorName == "Red") { variable = TFT_RED; }
	else if (colorName == "Blue") { variable = TFT_BLUE; }
	else if (colorName == "Yellow") { variable = TFT_YELLOW; }
	else if (colorName == "Black") { variable = TFT_BLACK; }
	else if (colorName == "Purple") { variable = TFT_PURPLE; }
	else if (colorName == "Orange") { variable = TFT_ORANGE; }
	else if (colorName == "Cyan") { variable = TFT_CYAN; }
	else if (colorName == "Magenta") { variable = TFT_MAGENTA; }
	else { variable = colorDefault; }
}



void saveColor(uint16_t &variable, String colorName, const char * path) {
	setColor(variable, colorName, variable);
	writeFile(SD, path, colorName);
}



void setBrightness(String brightness, uint8_t defaultBrightness = 255) {
	int16_t testBrightness = brightness.toInt();
	if (testBrightness > 0 && testBrightness <= 255) { screenBrightness = testBrightness; }
	else { screenBrightness = defaultBrightness; }
	M5Cardputer.Display.setBrightness(screenBrightness);
}



void saveBrightness(String brightness) {
	setBrightness(brightness, 255);
	writeFile(SD, path_brightness, brightness);
}