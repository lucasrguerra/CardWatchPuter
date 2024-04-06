#include <M5Cardputer.h>
#include <IRremote.hpp>



void televisionPower();
void televisionVolumeUp();
void televisionVolumeDown();
void televisionChannelUp();
void televisionChannelDown();



void televisionPower() {
    IrSender.sendNEC(0x20DF10EF, 32);
}



void televisionVolumeUp() {
    IrSender.sendNEC(0x20DF40BF, 32);
}



void televisionVolumeDown() {
    IrSender.sendNEC(0x20DFC03F, 32);
}



void televisionChannelUp() {
    IrSender.sendNEC(0x20DF906F, 32);
}



void televisionChannelDown() {
    IrSender.sendNEC(0x20DFD02F, 32);
}

