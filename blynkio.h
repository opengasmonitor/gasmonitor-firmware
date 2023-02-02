#ifndef BLYNKIO_H
#define BLYNKIO_H

#include "configuration.h"
#include "monitor.h"

extern Monitor monitor;

class BlynkIO
{
	public:
		bool enabled = BLYNK_ENABLED;
		void setup();
		void loop();
		void sendData();
};

#endif