#include "led.h"

Led::Led()
{
	if (debug) Serial.println("FN: Led::Led()");
	pinMode(Led::pin, OUTPUT);
}

void Led::setup()
{
	if (debug) Serial.println("FN: Led::setup()");
	pinMode(Led::pin, OUTPUT);
}

void Led::blink()
{
	if (debug) Serial.println("FN: Led::blink()");
	Led::toggle();
	delay(5);
	Led::toggle();
}

void Led::on()
{
	if (debug) Serial.println("FN: Led::on()");
	digitalWrite(Led::pin, LOW);
}

void Led::off()
{
	if (false) Serial.println("FN: Led::off()");
	digitalWrite(Led::pin, HIGH);
}

void Led::toggle()
{
	if (debug) Serial.println("FN: Led::toggle()");
	state = digitalRead(Led::pin);
	state = !state;
	digitalWrite(Led::pin, state);
}