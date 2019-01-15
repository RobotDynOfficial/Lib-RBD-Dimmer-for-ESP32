#include <RBDdimmerESP32.h>//

#define outPin  25 // GPIO for dimming, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8), 5(GPIO36), 8(GPIO39), 10(GPIO34), 11(GPIO35), 32(GPIO7) 
#define ZCPin   26 // GPIO for Zero-Cross, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8)
dimmerLampESP32 dimmer(outPin, ZCPin); //initialase port for dimmer 

int outVal = 0;

void setup() {
  Serial.begin(9600);
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE) 
}

void loop() 
{
  outVal = map(analogRead(0), 1, 1024, 100, 0); // analogRead(analog_pin), min_analog, max_analog, 100%, 0%);
  Serial.println(outVal); 
  dimmer.setPower(outVal); // name.setPower(0%-100%)
}
