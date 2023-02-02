#ifndef MQTTW_H
#define MQTTW_H

#include <MQTT.h>

#include "monitor.h"
#include "network.h"
#include "configuration.h"

extern WiFiClient wifi;
extern MQTTClient mqttc;
extern Network network;
extern Monitor monitor;

class MQTT
{
	public:
		const bool debug = false;
		const bool enabled = MQTT_ENABLED;
		const char* mqttBroker = MQTT_ADDRESS;
		const int mqttPort = MQTT_PORT;
		const char* mqttTopic =  MQTT_TOPIC;
		String id = MQTT_ID;
		String ip;

		MQTT();
		void setup();
		void loop();
		void reconnect();
		void mqttcReconnect();
		void mqttcPublishRuntimeValues();
		static void mqttcCallback(String&, String&);
};

#endif