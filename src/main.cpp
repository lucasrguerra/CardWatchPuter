#include <Arduino.h>
#include <M5Cardputer.h>


#include "wifi/main.h"
#include "wifi/DeauthAttack.h"
#include "infrared/AirConditioner.h"
#include "infrared/Television.h"
#include "infrared/main.h"
#include "SDCard/main.h"
#include "Colors.h"
#include "Screen.h"



uint8_t machineState = 0;
uint8_t actualItem = 0;
u64_t lastTime = 0;
uint8_t attackType = 0;



uint8_t screen_home(uint8_t backTo);
uint8_t screen_settings(uint8_t backTo);
uint8_t screen_titleColor(uint8_t backTo);
uint8_t screen_textColor(uint8_t backTo);
uint8_t screen_backgroundColor(uint8_t backTo);
uint8_t screen_wifi(uint8_t backTo);
uint8_t screen_selectNetwork(uint8_t backTo);
uint8_t screen_wifi_deauth(uint8_t backTo);
uint8_t screen_infrared(uint8_t backTo);
uint8_t screen_infrared_television(uint8_t backTo);
uint8_t screen_infrared_airConditioner(uint8_t backTo);
uint8_t screen_brightness(uint8_t backTo);



void setup() {
	auto configures = M5.config();
	M5Cardputer.begin(configures, true);
	Serial.begin(115200);

	initSDCard();
	initColors();
	initInfrared();

	drawSetupScreen();

}

void loop () {
	M5Cardputer.update();
	M5Cardputer.Display.fillScreen(backgroundColor);

	switch (machineState) {
		case 0: machineState = screen_home(0); break;
		case 1: machineState = screen_settings(0); break;
		case 2: machineState = screen_titleColor(1); break;
		case 3: machineState = screen_textColor(1); break;
		case 4: machineState = screen_backgroundColor(1); break;
		case 5: machineState = screen_wifi(0); break;
		case 6: machineState = screen_selectNetwork(5); break;
		case 7: machineState = screen_wifi_deauth(6); break;
		case 8: machineState = screen_infrared(0); break;
		case 9: machineState = screen_infrared_television(8); break;
		case 10: machineState = screen_infrared_airConditioner(8); break;
		case 11: machineState = screen_brightness(1); break;
		default: machineState = 0; break;
	}

	delay(10);
}



uint8_t screen_home(uint8_t backTo) {
	String menuTitle = "Home";
	String menuItems[] = {"Settings", "Wi-Fi", "Infrared"};
	uint8_t menuItemsLength = 3;

	menuScreen(menuTitle, menuItems, menuItemsLength);

	switch (actualItem) {
		case 0: return 1;
		case 1: return 5;
		case 2: return 8;
		case 255: return backTo;
		default: return 0;
	}
}



uint8_t screen_settings(uint8_t backTo) {
	String menuTitle = "Settings";
	String menuItems[] = {"Title Color", "Text Color", "Background Color", "Brightness"};
	uint8_t menuItemsLength = 4;

	menuScreen(menuTitle, menuItems, menuItemsLength);

	switch (actualItem) {
		case 0: return 2;
		case 1: return 3;
		case 2: return 4;
		case 3: return 11;
		case 255: return backTo;
		default: return 0;
	}
}



uint8_t screen_titleColor(uint8_t backTo) {
	String menuTitle = "Title Color";
	String menuItems[] = {"White", "Green", "Red", "Blue", "Yellow", "Black", "Purple", "Orange", "Cyan", "Magenta"};
	uint8_t menuItemsLength = 10;

	menuScreen(menuTitle, menuItems, menuItemsLength);

	switch (actualItem) {
		case 0: saveColor(titleColor, "White", path_titleColor); break;
		case 1: saveColor(titleColor, "Green", path_titleColor); break;
		case 2: saveColor(titleColor, "Red", path_titleColor); break;
		case 3: saveColor(titleColor, "Blue", path_titleColor); break;
		case 4: saveColor(titleColor, "Yellow", path_titleColor); break;
		case 5: saveColor(titleColor, "Black", path_titleColor); break;
		case 6: saveColor(titleColor, "Purple", path_titleColor); break;
		case 7: saveColor(titleColor, "Orange", path_titleColor); break;
		case 8: saveColor(titleColor, "Cyan", path_titleColor); break;
		case 9: saveColor(titleColor, "Magenta", path_titleColor); break;
		case 255: return backTo;
		default: return 0;
	}
	return 1;
}



uint8_t screen_textColor(uint8_t backTo) {
	String menuTitle = "Text Color";
	String menuItems[] = {"Green", "White", "Red", "Blue", "Yellow", "Black", "Purple", "Orange", "Cyan", "Magenta"};
	uint8_t menuItemsLength = 10;

	menuScreen(menuTitle, menuItems, menuItemsLength);

	switch (actualItem) {
		case 0: saveColor(textColor, "Green", path_textColor); break;
		case 1: saveColor(textColor, "White", path_textColor); break;
		case 2: saveColor(textColor, "Red", path_textColor); break;
		case 3: saveColor(textColor, "Blue", path_textColor); break;
		case 4: saveColor(textColor, "Yellow", path_textColor); break;
		case 5: saveColor(textColor, "Black", path_textColor); break;
		case 6: saveColor(textColor, "Purple", path_textColor); break;
		case 7: saveColor(textColor, "Orange", path_textColor); break;
		case 8: saveColor(textColor, "Cyan", path_textColor); break;
		case 9: saveColor(textColor, "Magenta", path_textColor); break;
		case 255: return backTo;
		default: return 0;
	}
	return 1;
}



uint8_t screen_backgroundColor(uint8_t backTo) {
	String menuTitle = "Background Color";
	String menuItems[] = {"black", "Green", "White", "Red", "Blue", "Yellow", "Purple", "Orange", "Cyan", "Magenta"};
	uint8_t menuItemsLength = 10;

	menuScreen(menuTitle, menuItems, menuItemsLength);

	switch (actualItem) {
		case 0: saveColor(backgroundColor, "Black", path_backgroundColor); break;
		case 1: saveColor(backgroundColor, "Green", path_backgroundColor); break;
		case 2: saveColor(backgroundColor, "White", path_backgroundColor); break;
		case 3: saveColor(backgroundColor, "Red", path_backgroundColor); break;
		case 4: saveColor(backgroundColor, "Blue", path_backgroundColor); break;
		case 5: saveColor(backgroundColor, "Yellow", path_backgroundColor); break;
		case 6: saveColor(backgroundColor, "Purple", path_backgroundColor); break;
		case 7: saveColor(backgroundColor, "Orange", path_backgroundColor); break;
		case 8: saveColor(backgroundColor, "Cyan", path_backgroundColor); break;
		case 9: saveColor(backgroundColor, "Magenta", path_backgroundColor); break;
		case 255: return backTo;
		default: return 0;
	}
	return 1;
}



uint8_t screen_wifi(uint8_t backTo) {
	String menuTitle = "Wi-Fi";
	String menuItems[] = {"DeAuth Attack"};
	uint8_t menuItemsLength = 1;

	menuScreen(menuTitle, menuItems, menuItemsLength);

	switch (actualItem) {
		case 0: attackType = 0; return 6;
		case 255: return backTo;
		default: return 0;
	}
}



uint8_t screen_selectNetwork(uint8_t backTo) {
	String menuTitle = "Select Wi-Fi";
	uint16_t menuItemsLength = scanWiFi();
	String menuItems[menuItemsLength];
	if (menuItemsLength == 0) {
		String menuItems[] = {"No networks found"};
		menuScreen(menuTitle, menuItems, 1);
		delay(2000);
		return 5;
	} else {
		for (uint8_t index = 0; index < menuItemsLength; index++) {
			menuItems[index] = (char *) acessPointsList[index].ssid;
		}
	}

	menuScreen(menuTitle, menuItems, menuItemsLength);

	accessPointInfo = acessPointsList[actualItem];
	if (actualItem < menuItemsLength) {
		switch (attackType) {
			case 0: return 7;
			default: return 0;
		}
	}
	
	if (actualItem == 255) { return backTo; }
}



uint8_t screen_wifi_deauth(uint8_t backTo) {
	actualItem = 0;
	M5Cardputer.Display.setTextSize(3);
	M5Cardputer.Display.setTextColor(titleColor, backgroundColor);
	M5Cardputer.Display.drawString("DeAuth Attack", screenInitialX, screenInitialY);
	M5Cardputer.Display.setTextColor(textColor, backgroundColor);

	M5Cardputer.Display.setTextSize(2);
	M5Cardputer.Display.drawString((char *) accessPointInfo.ssid, screenInitialX, (screenInitialY + 30));
	bool runAttack = false;

	while (true) {
		M5Cardputer.update();
		if (runAttack) {
			M5Cardputer.Display.setTextColor(backgroundColor, textColor);
			M5Cardputer.Display.drawString("Stop Attack        ", screenInitialX, (screenInitialY + 60));
		} else {
			M5Cardputer.Display.setTextColor(backgroundColor, textColor);
			M5Cardputer.Display.drawString("Start Attack       ", screenInitialX, (screenInitialY + 60));
		}

		if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
			runAttack = !runAttack;
			delay(200);
		}

		if (M5Cardputer.Keyboard.isKeyPressed('`')) {
			delay(200);
			return backTo;
		}

		if (runAttack) { deauthAttack(); }
		delay(1);
	}
}



uint8_t screen_infrared(uint8_t backTo) {
	String menuTitle = "Infrared";
	String menuItems[] = {"Television", "Air Conditioner"};
	uint8_t menuItemsLength = 2;

	menuScreen(menuTitle, menuItems, menuItemsLength);

	switch (actualItem) {
		case 0: return 9;
		case 1: return 10;
		case 255: return backTo;
		default: return 0;
	}

	return 1;
}



uint8_t screen_infrared_television(uint8_t backTo) {
	String menuTitle = "Television";
	String menuItems[] = {"Power", "Volume Up", "Volume Down", "Channel Up", "Channel Down"};
	uint8_t menuItemsLength = 5;

	while (true) {
		menuScreen(menuTitle, menuItems, menuItemsLength);

		switch (actualItem) {
			case 0: televisionPower(); break;
			case 1: televisionVolumeUp(); break;
			case 2: televisionVolumeDown(); break;
			case 3: televisionChannelUp(); break;
			case 4: televisionChannelDown(); break;
			case 255: return backTo;
			default: return 0;
		}
	}
}



uint8_t screen_infrared_airConditioner(uint8_t backTo) {
	String menuTitle = "Air Cond.";
	String menuItems[] = {"Power", "Temperature Up", "Temperature Down"};
	uint8_t menuItemsLength = 3;

	menuScreen(menuTitle, menuItems, menuItemsLength);

	while (true) {
		switch (actualItem) {
			case 0: airConditionerPower(); break;
			case 1: airConditionerTemperatureUp(); break;
			case 2: airConditionerTemperatureDown(); break;
			case 255: return backTo;
			default: return 0;
		}
	}
}



uint8_t screen_brightness(uint8_t backTo) {
	String menuTitle = "Brightness";
	String menuItems[] = {"Increase", "Decrease", "100%", "75%", "50%", "25%", "1%"};
	uint8_t menuItemsLength = 7;

	while (true) {
		menuScreen(menuTitle, menuItems, menuItemsLength);
		int16_t brightness = screenBrightness;
		switch (actualItem) {
			case 0:
				brightness += 25;
				if (brightness > 255) { brightness = 255; }
				saveBrightness(String(brightness));
				break;

			case 1:
				brightness -= 25;
				if (brightness < 0) { brightness = 0; }
				saveBrightness(String(brightness));
				break;

			case 2: saveBrightness((String) 255); break;
			case 3: saveBrightness((String) 192); break;
			case 4: saveBrightness((String) 128); break;
			case 5: saveBrightness((String) 64); break;
			case 6: saveBrightness((String) 1); break;
			case 255: return backTo;
			default: return 0;
		}
	}
}