#include "monitor.h"

#include "led.h"
#include "webhook.h"

extern Led led;
extern Webhook webhook;

Monitor::Monitor()
{
	if (debug) Serial.println("FN: Monitor::Monitor()");
	pinMode(pin, INPUT_PULLUP);
	Serial.println("LOG: monitor pins initialised");
}

void Monitor::setup()
{
	if (debug) Serial.println("FN: Monitor::setup()");
	if (!debug) Serial.println("LOG: monitor setup complete");
}

void Monitor::loop()
{
	if(digitalRead(pin)==LOW)
	{
		led.on();

		if (pulse==false)
		{
			pulse = true;
			start = millis();		
			Serial.println("LOG: pulse started");
		}
	}
	else
	{
		led.off();

		if(pulse==true)
		{
			end = millis();
			Serial.println("LOG: pulse ended");
			length = end-start;
			if (length>trigger)
			{
				Serial.println("LOG: incrementing runtime value");
				value++;
				m3 = double(value)*scale;
				webhook.sendData();
			}
			pulse = false;
		}
	}
}

void Monitor::restore()
{
	if (debug) Serial.println("FN: Monitor::restore()");
	if (!debug) Serial.println("LOG: restoring runtime values");

	String response = webhook.get(webhook.address);

	Serial.println(response);

	StaticJsonDocument<250> json;
	DeserializationError error = deserializeJson(json, response);

	if (error) {
		if (debug) Serial.println(error.f_str());
		if (!debug) Serial.println("LOG: restoring failed");
	} else {
		m3 = json["value"];
		scale = json["scale"];
		value = int(double(json["value"])/double(json["scale"]));
		Serial.println("LOG: restored runtime value");
	}
}