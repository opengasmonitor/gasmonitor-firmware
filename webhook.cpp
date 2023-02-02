#include "webhook.h"

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

extern Network network;
extern WiFiClient wifi;
HTTPClient httpClient;

String Webhook::get(char* url)
{
	if (debug) Serial.println("FN: Webhook::get(url)");

	String response = "";

	if (httpClient.begin(wifi,url)) {

		httpClient.addHeader("Bearer", Webhook::key);
		httpClient.addHeader("X-API-Key", Webhook::key);
		int httpCode = httpClient.GET();
		if (debug) Serial.println(httpCode);
		if (httpCode > 0) {
			if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
				response = httpClient.getString();          
				if (debug) Serial.println(response);
			}
		} else {
			Serial.printf("HTTP: get failed, error: %s\n", httpClient.errorToString(httpCode).c_str());
		}
		httpClient.end();
	} else {
		Serial.println("HTTP: unable to connect");
	}

	return response;
}

String Webhook::post(char* url, String data)
{
	if (debug) Serial.println("FN: Webhook::post(url)");
	if (debug) Serial.println(url);
	if (debug) Serial.println(data);

	String response = "";

	if (httpClient.begin(wifi,url)) {
		httpClient.setReuse(false);
		httpClient.addHeader("Bearer", Webhook::key);
		httpClient.addHeader("X-API-Key", Webhook::key);
		httpClient.addHeader("Content-Type", "application/json");
		int httpCode = httpClient.POST(data);
		Serial.printf("LOG: http code %d",httpCode);
		Serial.println();
		if (httpCode > 0) {
			if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
				response = httpClient.getString();          
			}
		} else {
			Serial.printf("HTTP: post failed, error: %s\n", httpClient.errorToString(httpCode).c_str());
		}
		httpClient.end();
	} else {
		Serial.println("HTTP: unable to connect");
	}

	if (debug) Serial.println(response);

	return String(response);
}

void Webhook::sendData()
{
	if (debug) Serial.println("FN: Webhook::sendData()");

	if (monitor.value>0 && monitor.m3>0) {
		if (monitor.key!=NULL) {
			Serial.println("LOG: sending data to webhook");

			StaticJsonDocument<250> json;
			String buffer;

			json.clear();
			json["key"] = monitor.key;
			json["value"] = monitor.m3;

			serializeJson(json, buffer);

			Webhook::post(Webhook::address, buffer);
		} else {
			Serial.println("LOG: id or key is null, not sending data to webhook");
		}
	} else {
		Serial.println("LOG: values are zero, not sending data to webhook");
	}
}