#pragma once
#include <iostream>
class Duration
{
private:
	int minutes;
	int seconds;

public:
	Duration();
	Duration(int minutes, int seconds);

	int getMinutes() const;
	int getSeconds() const;
	void setMinutes(int newMinutesValue);
	void setSeconds(int newSecondsValue);

	friend std::istream& operator>>(std::istream& stream, Duration& duration);
	friend std::ostream& operator<<(std::ostream& stream, const Duration& duration);
};
