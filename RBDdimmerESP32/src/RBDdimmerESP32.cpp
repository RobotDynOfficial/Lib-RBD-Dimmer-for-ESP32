
#include "Arduino.h"
#include "RBDdimmerESP32.h"

int dim_tim[10];
int dim_max[10];
int timeoutPin = 435; // 80us
int extIntPin = 2; //z-c

int pulseWidth = 6;
volatile int current_dim = 0;
int all_dim = 3;
int rise_fall = true;
static int tog;
static int max_tim_for_tog = 1;
char user_zero_cross = '0';

static int toggleCounter = 0;
static int toggleReload = 25;

static dimmerLampESP32* dimmer[ALL_DIMMERS];
volatile int dimPower[ALL_DIMMERS];
volatile int dimOutPin[ALL_DIMMERS];
volatile int dimZCPin[ALL_DIMMERS];
volatile int zeroCross[ALL_DIMMERS];
volatile DIMMER_MODE_typedef dimMode[ALL_DIMMERS];
volatile ON_OFF_typedef dimState[ALL_DIMMERS];
volatile int dimCounter[ALL_DIMMERS];
static uint16_t dimPulseBegin[ALL_DIMMERS];
volatile uint16_t togMax[ALL_DIMMERS];
volatile uint16_t togMin[ALL_DIMMERS];
volatile bool togDir[ALL_DIMMERS];

dimmerLampESP32::dimmerLampESP32(int user_dimmer_pin, int zc_dimmer_pin):
	dimmer_pin(user_dimmer_pin),
	zc_pin(zc_dimmer_pin)
{
	current_dim++;
	dimmer[current_dim-1] = this;
	current_num = current_dim-1;
	toggle_state = false;
	
	dimPulseBegin[current_dim-1] = 1;
	dimOutPin[current_dim-1] = user_dimmer_pin;
	dimZCPin[current_dim-1] = zc_dimmer_pin;
	dimCounter[current_dim-1] = 0;
	zeroCross[current_dim-1] = 0;
	dimMode[current_dim-1] = NORMAL_MODE;
	togMin[current_dim-1] = 0;
	togMax[current_dim-1] = 1;
	pinMode(user_dimmer_pin, OUTPUT);
}

void dimmerLampESP32::timer_init(void)
{
	hw_timer_t * timer = NULL;
	// Use 1st timer of 4 (counted from zero).
  	// Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more info).
	timer = timerBegin(0, 250, true);
	// Attach onTimer function to our timer.
	timerAttachInterrupt(timer, &onTimerISR, true);
	// Set alarm to call onTimer function every second (value in microseconds).
  	// Repeat the alarm (third parameter)
  	timerAlarmWrite(timer, 30, true);
  	// Start an alarm
  	timerAlarmEnable(timer);
}

void dimmerLampESP32::ext_int_init(void) 
{
	int inPin = dimZCPin[this->current_num];
	pinMode(inPin, INPUT_PULLUP);
    attachInterrupt(inPin, isr_ext, RISING);
}

void dimmerLampESP32::begin(DIMMER_MODE_typedef DIMMER_MODE, ON_OFF_typedef ON_OFF)
{
	dimMode[this->current_num] = DIMMER_MODE;
	dimState[this->current_num] = ON_OFF;
	timer_init();
	ext_int_init();	
}

void dimmerLampESP32::setPower(int power)
{	
	if (power >= 99) 
	{
		power = 99;
	}
	dimPower[this->current_num] = power;
	dimPulseBegin[this->current_num] = powerBuf[power];
	
	delay(1);
}

int dimmerLampESP32::getPower(void)
{
	if (dimState[this->current_num] == ON)
		return dimPower[this->current_num];
	else return 0;
}

void dimmerLampESP32::setState(ON_OFF_typedef ON_OFF)
{
	dimState[this->current_num] = ON_OFF;
}

bool dimmerLampESP32::getState(void)
{
	bool ret;
	if (dimState[this->current_num] == ON) ret = true;
	else ret = false;
	return ret;
}

void dimmerLampESP32::changeState(void)
{
	if (dimState[this->current_num] == ON) dimState[this->current_num] = OFF;
	else 
		dimState[this->current_num] = ON;
}

DIMMER_MODE_typedef dimmerLampESP32::getMode(void)
{
	return dimMode[this->current_num];
}

void dimmerLampESP32::setMode(DIMMER_MODE_typedef DIMMER_MODE)
{
	dimMode[this->current_num] = DIMMER_MODE;
}

void dimmerLampESP32::toggleSettings(int minValue, int maxValue)
{
	if (maxValue > 99) 
	{
    	maxValue = 99;
	}
	if (minValue < 1) 
	{
    	minValue = 1;
	}
	dimMode[this->current_num] = TOGGLE_MODE;
	togMin[this->current_num] = powerBuf[maxValue];
	togMax[this->current_num] = powerBuf[minValue];

	toggleReload = 50;
}
 
void IRAM_ATTR isr_ext()
{
	for (int i = 0; i < current_dim; i++ ) 
		if (dimState[i] == ON) 
		{
			zeroCross[i] = 1;
		}
}

static int k;
void IRAM_ATTR onTimerISR()
{	
	
	toggleCounter++;
	for (k = 0; k < current_dim; k++)
	{
		if (zeroCross[k] == 1 )
		{
			dimCounter[k]++;

			if (dimMode[k] == TOGGLE_MODE)
			{
			/*****
			 * TOGGLE DIMMING MODE
			 *****/
			if (dimPulseBegin[k] >= togMax[k]) 	
			{
				// if reach max dimming value 
				togDir[k] = false;	// downcount				
			}
			if (dimPulseBegin[k] <= togMin[k])
			{
				// if reach min dimming value 
				togDir[k] = true;	// upcount
			}
			if (toggleCounter == toggleReload) 
			{
				if (togDir[k] == true) dimPulseBegin[k]++;
				else dimPulseBegin[k]--;
			}
			}
			
			/*****
			 * DEFAULT DIMMING MODE (NOT TOGGLE)
			 *****/
			if (dimCounter[k] >= dimPulseBegin[k] )
			{
				digitalWrite(dimOutPin[k], HIGH);	
			}

			if (dimCounter[k] >=  (dimPulseBegin[k] + pulseWidth) )
			{
				digitalWrite(dimOutPin[k], LOW);
				zeroCross[k] = 0;
				dimCounter[k] = 0;
			}
		}
	}
	if (toggleCounter >= toggleReload) toggleCounter = 1;
	
}
