#include <RBDdimmerESP32.h>//

#define outPin  25 // GPIO for dimming, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8), 5(GPIO36), 8(GPIO39), 10(GPIO34), 11(GPIO35), 32(GPIO7) 
#define ZCPin   26 // GPIO for Zero-Cross, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8)
dimmerLampESP32 dimmer(outPin, ZCPin); //initialase port for dimmer 

int buttonRed = 0;

void setup() {
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE) 
  dimmer.setPower(50);
  pinMode(13, INPUT);
}

void loop() {
  buttonRed = digitalRead(13);  
  if (buttonRed == 1)
  {
    delay(10);
    dimmer.setState(ON); //name.setState(ON/OFF);
  }  
  if (buttonRed == 0)
  {
    delay(10);
    dimmer.setState(OFF); //name.setState(ON/OFF);
  }
}
