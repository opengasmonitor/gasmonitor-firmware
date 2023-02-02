#ifndef LED_H
#define LED_H

#include <Arduino.h>

#include "monitor.h"

class Led
{
	public:
		bool debug = false;
		int pin = 2;
		int state = NULL;

		Led();
		void setup();
		void on();
		void off();
		void blink();
		void toggle();
};

#endif