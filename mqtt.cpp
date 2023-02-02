#include "mqtt.h"

MQTT::MQTT()
{
	if (debug) Serial.println("FN: MQTT:MQTT()");
	MQTT::ip = monitor.ipv4;
	Serial.println("LOG: mqtt constructor completed");
}

void MQTT::setup()
{
	if (debug) Serial.println("FN: MQTT::setup()");

	if(MQTT::enabled)
	{
		Serial.println("LOG: initialising MQTT client");
		mqttc.begin(mqttBroker, mqttPort, wifi);
		if (mqttc.connect(MQTT::id.c_str()))
		{
			Serial.println("LOG: connected to broker");
			delay(100);
		}
		else
		{
			Serial.println("ERROR: error connecting to broker");
		}
		Serial.println("LOG: mqtt setup complete");
	}
}

void MQTT::loop()
{
	if (debug) Serial.println("FN: MQTT::loop()");

	if(MQTT::enabled)
	{
		reconnect();
		mqttc.loop();
	}
}

void MQTT::reconnect()
{
	if (debug) Serial.println("FN: MQTT::reconnect()");
	mqttcReconnect();
}

void MQTT::mqttcReconnect() 
{
	if (debug) Serial.println("FN: MQTT::mqttcReconnect()");

	if (!mqttc.connected())
	{
		if (mqttc.connect(MQTT::id.c_str()))
		{
			Serial.println("LOG: re-connected to broker");
			delay(100);
		}
		else
		{
			Serial.println("ERROR: error connecting to broker");
		}
	}
}

void MQTT::mqttcPublishRuntimeValues() 
{
	if (debug) Serial.println("FN: MQTT::mqttcPublishRuntimeValues()");

	if(MQTT::enabled)
	{
		if (monitor.value>0&&monitor.m3>0)
		{
			Serial.println("LOG: publishing data on MQTT broker");
			mqttc.publish(String(MQTT_TOPIC)+String("/value"),String(monitor.value));
			mqttc.publish(String(MQTT_TOPIC)+String("/m3"),String(monitor.m3,1));
		}
		else
		{
			Serial.println("LOG: values are zero, not publishing data on mqtt broker");
		}
	}
}