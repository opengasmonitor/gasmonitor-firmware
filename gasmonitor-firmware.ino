#include <Arduino.h>
#include <ArduinoOTA.h>

#include "api.h"
#include "blynkio.h"
#include "configuration.h"
#include "led.h"
#include "monitor.h"
#include "mqtt.h"
#include "network.h"
#include "webhook.h"

// INITIALIZATIONS

WiFiClient wifi;
MQTTClient mqttc;

// CLASSES

API api;
BlynkIO blynkio;
Led led;
Monitor monitor;
MQTT mqtt;
Network network;
Webhook webhook;

// TIMERS

long minuteTimer = 0;
long secondTimer = 0;

// SETUP

void setup()
{
	// NOTE: set up serial w/ esp8266 default baud rate
	Serial.begin(74880);
	Serial.println("LOG: starting setup");

	// NOTE: led signal on
	led.setup();
	led.on();

	// NOTE: initialize modules
	network.setup();
	api.setup();
	mqtt.setup();
	blynkio.setup();

	// OTA firmware upadte
	ArduinoOTA.begin();

	// NOTE: if value is zero (reset), restore from API
	monitor.restore();

	// NOTE: led signal off
	led.off();

	Serial.println("LOG: setup done");
}

// LOOP

void loop()
{
	ArduinoOTA.handle();

	// NOTE: loop functions
	monitor.loop();
	network.loop();
	api.loop();
	blynkio.loop();

	// NOTE: one second timer
	if(millis()-secondTimer>1000)
	{
		// NOTE: execute loop functions
		led.blink();
		mqtt.loop();

		// NOTE: update loop timer
		secondTimer = millis();
	}

	// NOTE: one minute timer
	if(millis()-minuteTimer>60000)
	{
		// NOTE: publish runtime values to broker
		mqtt.mqttcPublishRuntimeValues();

		// NOTE: publish runtime values to blynk
		blynkio.sendData();

		// NOTE: update loop timer
		minuteTimer = millis();
	}
}