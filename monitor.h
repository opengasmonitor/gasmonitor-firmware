#ifndef MONITOR_H
#define MONITOR_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "configuration.h"

class Monitor
{
	public:
		char* key = WEBHOOK_KEY;
		bool debug = false;
		bool pulse = false;
		int pin = 0;
		int start = 0;
		int end = 0;
		int length = 0;
		int value = 0;
		double m3 = 0;
		double scale = 0;
		int trigger = 1000; // miliseconds
		String ipv4;
		String mac;

		Monitor();
		void setup();
		void loop();
		void restore();
};

#endif