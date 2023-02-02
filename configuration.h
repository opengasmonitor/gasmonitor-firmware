#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// Modify this section using your credentials

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define WEBHOOK_KEY ""

// Only modify this section if you know what you are doing

#define WEBHOOK_ADDRESS "http://webhook.gasmonitor.cloud/v1"

#define MDNS_HOSTNAME "gasmonitor"

#define MQTT_ENABLED false
#define MQTT_ADDRESS ""
#define MQTT_PORT 1883
#define MQTT_ID "gasmonitor"
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_TOPIC "gasmonitor"

#define BLYNK_ENABLED false
#define BLYNK_AUTH_TOKEN ""
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""

#endif