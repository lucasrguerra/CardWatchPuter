#include <M5Cardputer.h>
#include <IRremote.hpp>



void televisionPower();
void televisionVolumeUp();
void televisionVolumeDown();
void televisionChannelUp();
void televisionChannelDown();



void televisionPower() {
    IrSender.sendNEC(0x20DF10EF, 32);
    IrSender.sendNEC(0x04FB08F7, 32);
}



void televisionVolumeUp() {
    IrSender.sendNEC(0x20DF40BF, 32);
    IrSender.sendNEC(0x04FB02FD, 32);
}



void televisionVolumeDown() {
    IrSender.sendNEC(0x20DFC03F, 32);
    IrSender.sendNEC(0x04FB03FC, 32);
}



void televisionChannelUp() {
    IrSender.sendNEC(0x20DF00FF, 32);
    IrSender.sendNEC(0x04FB00FF, 32);
}



void televisionChannelDown() {
    IrSender.sendNEC(0x20DF50AF, 32);
    IrSender.sendNEC(0x04FB01FE, 32);
}

