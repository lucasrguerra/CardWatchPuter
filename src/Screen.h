#include <M5Cardputer.h>

extern uint16_t titleColor;
extern uint16_t textColor;
extern uint16_t backgroundColor;
extern uint8_t machineState;
extern uint8_t actualItem;



const uint8_t screenInitialX = 2;
const uint8_t screenInitialY = 20;
const uint16_t updateScreenTime = 100;
const uint8_t buttonDelay = 200;
u64_t updateLastTime;
u64_t inactivityTime = 0;
u16_t inactivityTimeLimit = 20000;



void initScreen();
void drawSetupScreen();
void drawBatteryStatus();
void resetInactivityTime();
void updateScreen(String menuTitle, String menuItems[], uint8_t menuItemsLength, boolean &clearedScreen);
void updateItem(boolean next, uint8_t menuItemsLength);
void menuScreen(String menuTitle, String menuItems[], uint8_t menuItemsLength);



void initScreen() {
	M5Cardputer.Display.setRotation(1);
	M5Cardputer.Display.setCursor(0, 0);
	M5Cardputer.Display.fillScreen(TFT_BLACK);
	drawSetupScreen();
}



void drawSetupScreen() {
	M5Cardputer.Display.setTextSize(3);
	
	for (uint8_t index = 0; index < 255; index++) {
		uint32_t color = M5Cardputer.Display.color888(0, index, 0);
		M5Cardputer.Display.setTextColor(color);
		M5Cardputer.Display.drawString("CardWatch", 35, 35);
		M5Cardputer.Display.drawString("Puter", 75, 75);
		delay(1);
	}

	delay(250);
	
	for (uint8_t index = 255; index > 0; index--) {
		uint32_t color = M5Cardputer.Display.color888(0, index, 0);
		M5Cardputer.Display.setTextColor(color);
		M5Cardputer.Display.drawString("CardWatch", 35, 35);
		M5Cardputer.Display.drawString("Puter", 75, 75);
		delay(1);
	}
}



void drawBatteryStatus() {
	const uint8_t batteryWidth = 30;
	const uint8_t batteryHeight = 10;
	uint8_t batteryLevel = map(M5Cardputer.Power.getBatteryLevel(), 0, 100, 0, (batteryWidth - 2));
	uint16_t borderColor = TFT_WHITE;
	if (
		backgroundColor == TFT_WHITE  ||
		backgroundColor == TFT_YELLOW ||
		backgroundColor == TFT_CYAN   ||
		backgroundColor == TFT_MAGENTA
	) {
		borderColor = TFT_BLACK;
	}

	M5Cardputer.Display.setCursor(0, 0);
	M5Cardputer.Display.drawRect(2, 2, batteryWidth, batteryHeight, TFT_WHITE);
	M5Cardputer.Display.fillRect(3, 3, (batteryWidth - 2), (batteryHeight - 2), backgroundColor);
	M5Cardputer.Display.fillRect(3, 3, batteryLevel, (batteryHeight - 2), TFT_GREEN);
}



void resetInactivityTime() {
	inactivityTime = millis();
}



void updateScreen(String menuTitle, String menuItems[], uint8_t menuItemsLength, boolean &clearedScreen) {
	M5Cardputer.update();
	if (millis() - inactivityTime >= inactivityTimeLimit) {
		M5Cardputer.Power.powerOff();
	}

	drawBatteryStatus();

	uint8_t additionalIndex = 0;
	if (actualItem > 3) {
		additionalIndex = actualItem - 3;
	}
	uint8_t itemNumber = 0;
	uint8_t referenceIndex = (additionalIndex + 5);

	if (actualItem == (menuItemsLength - 1) && additionalIndex > 0) {
		referenceIndex = (additionalIndex + 4);
		if (clearedScreen == false) {
			M5Cardputer.Display.fillScreen(backgroundColor);
			clearedScreen = true;
		}
	} else { clearedScreen = false; }

	M5Cardputer.Display.setTextSize(3);
	M5Cardputer.Display.setTextColor(titleColor, backgroundColor);
	M5Cardputer.Display.drawString(menuTitle, screenInitialX, screenInitialY);
	M5Cardputer.Display.setTextSize(2);

	for (uint8_t index = additionalIndex; index < referenceIndex; index++) {
		if (index == actualItem) {
			M5Cardputer.Display.setTextColor(backgroundColor, textColor);
		} else {
			M5Cardputer.Display.setTextColor(textColor, backgroundColor);
		}
		
		if (index < menuItemsLength) {
			String menuItem = " " + menuItems[index]; 
			uint8_t lengthOfString = menuItem.length();
			while (lengthOfString < 20) {
				menuItem += " ";
				lengthOfString++;
			}
			if (lengthOfString > 20) {
				menuItem = menuItem.substring(0, 20);
			}
			M5Cardputer.Display.drawString(menuItem, screenInitialX, ((screenInitialY + 30) + (itemNumber * 20)));
		}
		itemNumber++;
	}
}



void updateItem(boolean next, uint8_t menuItemsLength) {
	if (next) {
		actualItem++;
		if (actualItem > (menuItemsLength - 1)) {
			actualItem = 0;
		}
	} else {
		actualItem--;
		if (actualItem == 255) {
			actualItem = (menuItemsLength - 1);
		}
	}
	delay(buttonDelay);
}



void menuScreen(String menuTitle, String menuItems[], uint8_t menuItemsLength) {
	boolean clearedScreen = false;
	boolean selectedItem = false;
	while (selectedItem == false) {
		if (millis() - updateLastTime >= updateScreenTime) {
			updateScreen(menuTitle, menuItems, menuItemsLength, clearedScreen);
			updateLastTime = millis();
		}


		M5Cardputer.update();
		if (M5Cardputer.Keyboard.isChange()) {
			resetInactivityTime();
		}

		if (M5Cardputer.Keyboard.isKeyPressed('.')) {
			updateItem(true, menuItemsLength);
		}

		if (M5Cardputer.Keyboard.isKeyPressed(';')) {
			updateItem(false, menuItemsLength);
		}

		if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
			selectedItem = true;
			delay(buttonDelay);
		}

		if (M5Cardputer.Keyboard.isKeyPressed('`')) {
			selectedItem = true;
			machineState = 0;
			actualItem = 255;
			delay(buttonDelay);
		}
	}
}