#ifndef WEBHOOK_H
#define WEBHOOK_H

#include <Arduino.h>

#include "configuration.h"
#include "monitor.h"
#include "network.h"

extern Monitor monitor;

class Webhook
{
	public:
		bool debug = true;
		char* key = WEBHOOK_KEY;
		char* address = WEBHOOK_ADDRESS;

		String get(char*);
		String post(char*, String);
		void sendData();
};

#endif