#include "SiPort.h"

SiPort::SiPort(void)
{
}


void SiPort::setOutput(uint8_t port)
{
	pinMode(port, OUTPUT);
}

void SiPort::setInput(uint8_t port)
{
	pinMode(port, INPUT);
}

void SiPort::setPuOn(uint8_t port)
{
	pinMode(port, INPUT_PULLUP);
}

bool SiPort::readDPort(uint8_t port)
{
	bool val;
  	setInput(port);
  	val = digitalRead(port);
  	return(val);
}

bool SiPort::readDPuPort(uint8_t port)
{
	bool val;
  	setPuOn(port);
  	val = digitalRead(port);
  	return(val);
}

int16_t SiPort::readAport(uint8_t port)
{
	int16_t val;
  	setInput(port);
  	val = analogRead(port);
  	return(val);
}

void SiPort::writeDport(uint8_t port,bool value)
{
	setOutput(port);
	digitalWrite(port, value);
}

void SiPort::writeAport(uint8_t port,int16_t value)
{
	analogWrite(port, value);
}