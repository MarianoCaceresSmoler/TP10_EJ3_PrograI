#include "leds.h"
#include "ports.h"
#include <stdio.h>

#define PORT PORT_A

void turnOnLED(int number)
{
	bitSet(PORT, number);
}

void toggleAllLEDs(void)
{
	maskToggle(PORT, 0xFF);
}

void turnOnAllLEDs(void)
{
	maskOn(PORT, 0xFF);

}

void turnOffAllLEDs(void)
{
	maskOff(PORT, 0xFF);
}

int getLedStatus(int numLed)
{
	return bitGet(PORT, numLed);

}
