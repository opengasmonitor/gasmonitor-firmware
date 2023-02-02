#include "api.h"

extern Monitor monitor;
extern MQTTClient mqttc;
ESP8266WebServer server(80);
StaticJsonDocument<250> jsonDocument;

void API::loop()
{
	server.handleClient();
}

void API::get404()
{
	Serial.println("FN: API::get404()");

	jsonDocument.clear();
	jsonDocument["status"] = 404;

	char buffer[255];
	serializeJson(jsonDocument, buffer);
	server.send(404, "application/json", "{}");
	Serial.println("LOG: response sent to client");
}

void API::getRoot()
{
	Serial.println("FN: API::getRoot()");

	jsonDocument.clear();
	jsonDocument["hostname"] = MDNS_HOSTNAME;
	jsonDocument["mac"] = WiFi.macAddress();
	jsonDocument["ipv4"] = WiFi.localIP();
	jsonDocument["key"] = monitor.key;
	jsonDocument["uptime"] = millis();
	jsonDocument["mqtt"] = mqttc.connected();
	jsonDocument["pulse"] = monitor.pulse;
	jsonDocument["value"] = monitor.value;
	jsonDocument["scale"] = monitor.scale;
	jsonDocument["m3"] = monitor.m3;

	char buffer[255];
	serializeJson(jsonDocument, buffer);
	server.send(200, "application/json", buffer);
	Serial.println("LOG: response sent to client");
}

void API::postRoot()
{
	Serial.println("FN: API::handlePost()");

	if (server.hasArg("plain")==false) 
	{
		Serial.println("ERROR: post body is missing");
		server.send(409, "application/json", "");
		Serial.println("LOG: sent 409 to client");
	}
	else
	{
		String body = server.arg("plain");
		Serial.println(body);

		// NOTE: extract variables from json document

		deserializeJson(jsonDocument, body);

		String id = jsonDocument["id"];
		String key = jsonDocument["key"];
		int value = jsonDocument["value"];
		double scale = jsonDocument["scale"];

		String ssid = jsonDocument["ssid"];
		String password = jsonDocument["password"];

		// NOTE: update runtime values

		if (key.length()==32)
		{
			Serial.println("LOG: updating key");
			monitor.key = strdup(key.c_str());
		}

		if (scale>0&&scale<=1)
		{
			monitor.scale = scale;
			monitor.m3 = double(monitor.value)*monitor.scale;
		}

		if (value>=0&&value<=9999999)
		{
			monitor.value = value;
			monitor.m3 = double(monitor.value)*monitor.scale;
		}

		// NOTE: send response

		API::getRoot();
		//server.send(200, "application/json", "{}");
		//Serial.println("LOG: sent 200 to client");
	}
}

void API::setup()
{
	//Serial.println("FN: API::setup()");
	Serial.println("LOG: initialising API");
	server.on("/", HTTP_GET, (std::function<void(void)>)API::getRoot);
	server.on("/", HTTP_POST, (std::function<void(void)>)API::postRoot);
	server.onNotFound((std::function<void(void)>)API::get404);
	server.begin();
}