#include <RBDdimmerESP32.h>//

#define outPin  25 // GPIO for dimming, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8), 5(GPIO36), 8(GPIO39), 10(GPIO34), 11(GPIO35), 32(GPIO7) 
#define ZCPin   32 // GPIO for Zero-Cross, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8)
dimmerLampESP32 dimmer(outPin, ZCPin); //initialase port for dimmer 

void setup() {
  Serial.begin(9600);
  dimmer.begin(TOGGLE_MODE, OFF); //dimmer initialisation: name.begin(MODE, STATE) 
  Serial.println("--- Toggle dimmer example ---");
  dimmer.toggleSettings(0, 100); //Name.toggleSettings(MIN, MAX);
  dimmer.setState(ON); // state: dimmer1.setState(ON/OFF);
  pinMode(14, INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:

}
