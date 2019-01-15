#include <RBDdimmerESP32.h>//

#define outPin  25 // GPIO for dimming, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8), 5(GPIO36), 8(GPIO39), 10(GPIO34), 11(GPIO35), 32(GPIO7) 
#define ZCPin   26 // GPIO for Zero-Cross, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8)

dimmerLampESP32 dimmer(outPin, ZCPin); //initialase port for dimmer 

int outVal = 0;

void setup() {
  Serial.begin(9600); 
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE) 
  Serial.println("Dimmer Program is starting...");
  Serial.println("Set value");
}

void printSpace(int val)
{
  if ((val / 100) == 0) Serial.print(" ");
  if ((val / 10) == 0) Serial.print(" ");
}

void loop() {
  int preVal = outVal;

  if (Serial.available())
  {
    int buf = Serial.parseInt();
    if (buf != 0) outVal = buf;
    delay(200);
  }
  dimmer.setPower(outVal); // setPower(0-100%);

  if (preVal != outVal)
  {
    Serial.print("% lampValue -> ");
    printSpace(dimmer.getPower());
    Serial.print(dimmer.getPower());

  }
  delay(50);

}
