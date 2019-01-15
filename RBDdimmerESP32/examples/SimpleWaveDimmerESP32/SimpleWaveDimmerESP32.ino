#include <RBDdimmerESP32.h>//

#define outPin  25 // GPIO for dimming, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8), 5(GPIO36), 8(GPIO39), 10(GPIO34), 11(GPIO35), 32(GPIO7) 
#define ZCPin   26 // GPIO for Zero-Cross, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8)
dimmerLampESP32 dimmer(outPin, ZCPin); //initialase port for dimmer 

void setup() {
  Serial.begin(9600);
  dimmer.begin(NORMAL_MODE, OFF); //dimmer initialisation: name.begin(MODE, STATE) 
  Serial.println("--- Simple dimmer example ---");
  dimmer.setPower(50); // setPower(0-100%);
  dimmer.setState(ON); // setState(ON/OFF);
  pinMode(5, INPUT);
}
void loop() {
  
  if (digitalRead(5) == 1) 
  {
    dimmer.changeState(); //changes state on the opposite: name.changeState(); 
  }
  Serial.print("Dimmer state: ");
  Serial.println(dimmer.getState());
  delay(1000);
}
