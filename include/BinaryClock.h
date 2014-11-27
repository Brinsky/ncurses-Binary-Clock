#ifndef BINARYCLOCK_H
#define BINARYCLOCK_H

#include <ctime>
#include <string>

class BinaryClock
{
public:
	BinaryClock();
	void updateTime();

	std::string getSecond();
	std::string getMinute();
	std::string getHour();
	std::string getWeekday();
	std::string getMonthDay();
	std::string getMonth();
	std::string getYear();
private:
	std::time_t rawTime;
	std::tm* currentTime;
	std::string makeBinary(int number);
};

#endif
