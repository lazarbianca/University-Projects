#include "Duration.h"
#include <string>

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

std::istream& operator>>(std::istream& stream, Duration& duration)
{
    int minutes, seconds;
    char separator;

    stream >> minutes >> separator >> seconds;

    if (separator != ':' || stream.fail()) {
        stream.setstate(std::ios::failbit);
    }
    else {
        duration.setMinutes(minutes);
        duration.setSeconds(seconds);
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Duration& duration)
{
    stream << std::to_string(duration.getMinutes()) + ":" + std::to_string(duration.getSeconds()) + "\n";
    return stream;
}

