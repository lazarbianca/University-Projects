#include "Duration.h"

Duration::Duration() :minutes{ 0 }, seconds{ 0 } {}

Duration::Duration(int minutes, int seconds)
{
	this->minutes = minutes;
	this->seconds = seconds;
}

int Duration::getMinutes() const
{
	return minutes;
}
// Q.1: how does it know what seconds are, and not this->seconds?
int Duration::getSeconds() const
{
	return seconds;
}

void Duration::setMinutes(int newMinutesValue)
{
	minutes = newMinutesValue;
}

void Duration::setSeconds(int newSecondsValue)
{
	seconds = newSecondsValue;
}
