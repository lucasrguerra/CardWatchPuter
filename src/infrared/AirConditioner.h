#include <M5Cardputer.h>
#include <IRremote.hpp>



void airConditionerPower();
void airConditionerTemperatureUp();
void airConditionerTemperatureDown();



void airConditionerPower() {
    IrSender.sendNEC(0x20DF10EF, 32);
}



void airConditionerTemperatureUp() {
    IrSender.sendNEC(0x20DF40BF, 32);
}



void airConditionerTemperatureDown() {
    IrSender.sendNEC(0x20DFC03F, 32);
}
