#include <RBDdimmerESP32.h>//

#define outPin  25 // GPIO for dimming, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8), 5(GPIO36), 8(GPIO39), 10(GPIO34), 11(GPIO35), 32(GPIO7) 
#define ZCPin   26 // GPIO for Zero-Cross, don't use pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8)#define LAMPMAXVALUE 100

dimmerLampESP32 dimmer(outPin, ZCPin); //initialase port for dimmer 


int stateL = 0, valLamp;
int DIM4 = 0;
int mainLamp = 0;
int buttonRed = 0; 
int buttonBlue = 0; 
bool setLamp = true;

void setup() {  
  Serial.begin(9600);
  dimmer.begin(NORMAL_MODE, ON); //dimmer initialisation: name.begin(MODE, STATE) 
}

void RiseFallLamp(bool RiseFallInt)
{
  if ((RiseFallInt == true) && (mainLamp < LAMPMAXVALUE)) mainLamp++;
  else if ((RiseFallInt != true) && (mainLamp > 0)) mainLamp--;
}

bool setLampState(int val)
{
  bool ret;
  if (val >= 1) ret = true;
  else ret = false;
  return ret;
}

void readButtonState()
{
  buttonRed = digitalRead(13);
  buttonBlue = digitalRead(15);
  
  if (buttonRed < 1) stateL++;
  if (buttonBlue < 1) stateL--;
  if (stateL < 0) stateL = 0;
  if (stateL > 1) stateL = 1;
}

void loop() {
  readButtonState();
  dimmer.setPower(mainLamp); // setPower(0-100%);
  RiseFallLamp(setLampState(stateL));
  delay(25);
}
