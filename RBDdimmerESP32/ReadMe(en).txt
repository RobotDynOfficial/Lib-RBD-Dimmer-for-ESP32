The following library is used for work with dimmer with the help of ESP32 based boards. It gives you the ability to control large ammount of dimmers by the means of hardware timer and external interrupt through previously defined pin.
Pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8), 5(GPIO36), 8(GPIO39), 10(GPIO34), 11(GPIO35), 32(GPIO7)  can't be used for dimming.
Pins 28(GPIO9), 29(GPIO10), 30(GPIO11), 31(GPIO6), 33(GPIO8) can't be used to work with Zero-Cross
This library can simplify user code with following functions:

    1. Function  dimmerLampESP32 - this function initializes the number of operating pin and Zero-Cross pin,and is defined by the user
    Example: dimmerLampESP32 dimmer(12, 14);   dimmer output DIM/PSM is initialized on the pin 12, Zero-Cross on pin 14/
     
    2. Function begin port initialization, timer and external interrupt from zero-cross.
        Initialization of zero-cross is set in sketch
        Example: dimmer4.begin(NORMAL_MODE, ON/OFF); port initialization, work mode choice, ON/OFF. 
    Parameter 1: dimmer working modes consist of two choices - NORMAL_MODE and TOGGLE_MODE 

        a. NORMAL_MODE to make dimmer work in defined value from 0 to 100 (%) (integer)
            Example of this mode located in \RBDdimmerESP32\examples\SimpleDimmerESP32
        b. TOGGLE_MODE smooth change of dimming value up or down in a defined range. This solutions implies change of dimming values by means of hardware timer, without using the cycle code.
            Example of this mode located in \RBDdimmerESP32\examples\SimpleToggleDimmerESP32

    Parameter 2: ON/OFF.
        a. ON - turns timer ON, allows to use dimmer.
        b. OFF - turns timer parameters OFF, prevents the use of dimmer.


    3. Function setPower sets dimming value from 0 to 100%
        Example: dimmer4.setPower(90);

    4. Function getPower to display current dimming value
        Example: Serial.print(dimmer4.getPower()); Result 0~100 int
   
    5. Function setMode sets and changes the work mode (NORMAL_MODE and TOGGLE_MODE)
                dimmer4.setMode(NORMAL_MODE/TOGGLE_MODE)

    6. Function getMode displays values of current work mode
        Example: Serial.print(dimmer4.getPower());  Result 0 (NORMAL_MODE) or 1 (TOGGLE_MODE)
   
    7. Function setState sets dimming state ON/OFF
        Example: dimmer4.setState(ON); delay(100); dimmer4.setState(OFF);
   
    8. Function getState displays current state of dimmer
        Serial.print(dimmer4.getState()); Result 0 (OFF) or 1 (ON)
   
    9. Function changeState changes dimmer state to the opposite one 
        Пример dimmer4.setState(ON); delay(100); dimmer4.changeState; delay(100);
  
    10. Function toggleSettings smooth change of dimming value up or down in a defined range
        Example located in \RBDdimmerESP32\examples\SimpleToggleDimmerESP32