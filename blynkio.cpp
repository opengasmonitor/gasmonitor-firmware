#include "blynkio.h"

#include <BlynkSimpleEsp8266.h>

void BlynkIO::setup()
{
	if(BlynkIO::enabled)
	{
		Serial.println("LOG: initialising Blynk");
		Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
	}
}

void BlynkIO::loop()
{
	if (BlynkIO::enabled) Blynk.run();
}

void BlynkIO::sendData()
{
	if(BlynkIO::enabled)
	{
		if(monitor.m3>0)
		{
			Serial.println("LOG: sending data to Blynk");
			Blynk.virtualWrite(V0, monitor.ipv4);
			Blynk.virtualWrite(V1, monitor.m3);
		}
		else
		{
			Serial.println("LOG: value is zero, not sending data to Blynk");
		}
	}
}