
#ifndef NETWORK_H
#define NETWORK_H

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include "monitor.h"
#include "configuration.h"
#include "led.h"

extern Monitor monitor;
extern Led led;

class Network
{
	public:
		bool debug = false;

		char* ssid = WIFI_SSID;
		char* password = WIFI_PASSWORD;

		void setup();
		void loop();
		void wifiOn();
		void wifiOff();
		void wifiConnect(char* ssid, char* pass);
		void wifiDisconnect();
		void printWifiStatus();

		String getLocalIP();
		String getSSID();
		String getRSSI();
		String getBSSID();
		String getMAC();
		String getGatewayIP();
};

#endif