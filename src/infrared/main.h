#include <IRremote.hpp>



#define IR_TX_PIN 44



void initInfrared();



void initInfrared() {
    IrSender.begin(DISABLE_LED_FEEDBACK);
    IrSender.begin(IR_TX_PIN);
}