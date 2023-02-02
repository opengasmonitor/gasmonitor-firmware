#ifndef API_H
#define API_H

#include "monitor.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <MQTT.h>

class API
{
	public:
		bool debug = false;
		void setup();
		void loop();
		static void get404();
		static void getRoot();
		static void postRoot();
};

#endif