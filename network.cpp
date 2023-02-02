#include "network.h"

void Network::setup()
{
	if (debug) Serial.println("FN: Network::setup()");

	Serial.println("LOG: connecting to wifi");

	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		led.toggle();
		delay(500);
		led.toggle();
		delay(500);
	}

	Serial.print("LOG: connected as ");
	Serial.println(WiFi.localIP().toString());
 
	monitor.ipv4 = WiFi.localIP().toString();
	monitor.mac = WiFi.macAddress();

	switch(MDNS.begin(MDNS_HOSTNAME, WiFi.localIP())) {
		case 0:
			Serial.println("ERROR: error starting mDNS");
		break;
		case 1:
			MDNS.addService("http", "tcp", 80);
			Serial.println("LOG: mDNS started");
		break;
	};

	Serial.println("LOG: network setup complete");
}

void Network::loop()
{
	if (WiFi.status()!=3) {
		Serial.println("LOG: reconnecting to wifi");
		WiFi.begin(ssid, password);
		if (WiFi.status()!=3) Serial.println("ERROR: error reconnecting to wifi");
	}
	MDNS.update();
}

void Network::wifiOn()
{
	Serial.println("Network::wifiOn()");
	WiFi.forceSleepWake();
	delay(1);  
}

void Network::wifiOff()
{
	Serial.println("Network::wifiOff()");
	WiFi.mode(WIFI_OFF);
	WiFi.forceSleepBegin();
	delay(1);
}

void Network::wifiConnect(char* ssid, char* pass)
{
	if (debug) Serial.println("Network::wifiConnect()");
	WiFi.persistent(false); // dont load settings into the flash memory
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, pass);
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
	}
	Serial.print("\n");  
}

void Network::wifiDisconnect()
{
	if (debug) Serial.println("Network::wifiDisconnect()");
	WiFi.disconnect();
}

String Network::getLocalIP()
{
	if (debug) Serial.println("Network::getLocalIP()");
	return WiFi.localIP().toString();
}

String Network::getGatewayIP()
{
	if (debug) Serial.println("Network::getGatewayIP()");
	String ip = WiFi.gatewayIP().toString();
	return ip;
}

String Network::getSSID()
{
	if (debug) Serial.println("Network::getSSID()");
	return WiFi.SSID();
}

String Network::getRSSI()
{
	if (debug) Serial.println("Network::getRSSI()");
	return String(WiFi.RSSI());
}

String Network::getBSSID()
{
	if (debug) Serial.println("Network::getBSSID()");
	uint8_t* uintBSSID = WiFi.BSSID();
	String strBSSID = "";
	for (int f=0; f<6; f++) {
		if (f>0) strBSSID += ":";
		strBSSID += String(uintBSSID[f],HEX);
	}
	return strBSSID;
}

String Network::getMAC()
{
	Serial.println("Network::getMAC()");
	String strMAC = WiFi.macAddress();
	return strMAC;
}