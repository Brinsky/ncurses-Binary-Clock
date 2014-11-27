#include "BinaryClock.h"

BinaryClock::BinaryClock()
{
	updateTime();
}

void BinaryClock::updateTime()
{
	std::time(&rawTime);
	this->currentTime = std::localtime(&rawTime);
}

std::string BinaryClock::getSecond()
{
	return makeBinary(currentTime->tm_sec);
}

std::string BinaryClock::getMinute()
{
	return makeBinary(currentTime->tm_min);
}

std::string BinaryClock::getHour()
{
	return makeBinary(currentTime->tm_hour);
}

std::string BinaryClock::getWeekday()
{
	return makeBinary(currentTime->tm_wday);
}

std::string BinaryClock::getMonthDay()
{
	return makeBinary(currentTime->tm_mday);
}

std::string BinaryClock::getMonth()
{
	return makeBinary(currentTime->tm_mon + 1);
}

std::string BinaryClock::getYear()
{
	return makeBinary(currentTime->tm_year + 1900);
}

std::string BinaryClock::makeBinary(int number)
{
	if( number <= 0 )
		return "0";

	// Detect how long the binary number is (find the MSB's index)
	int power = 0;
	int value = 1;
	while( number >= value * 2 )
	{
		power++;
		value *= 2;
	}

	std::string binaryNumber = "";

	// "Shift out" all ones and zeros
	for( int i = 0; i < power + 1; ++i )
	{
		if( (number >> i) & 1 )
			binaryNumber = '1' + binaryNumber;
		else
			binaryNumber = '0' + binaryNumber;
	}

	return binaryNumber;
}
