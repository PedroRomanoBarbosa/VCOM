#include "Time.h"
#include <cmath>

Time::Time()
{
	hour = 0; minute = 0; second = 0;
}

Time::~Time()
{}

double Time::reduceAngle(float angle)
{
	return fmod(abs(angle), revolution);
}

int Time::resolveAngle(float angle, int timeSteps)
{
	int step = (int) (revolution / timeSteps);
	int angle_resolved = (int) floor(reduceAngle(angle));

	for (int i = 0; i <= timeSteps; i++) {
		if (i*step > angle_resolved)
			return(i - 1);
	}

	return -1;
}



void Time::setTime(float angle_h, float angle_m)
{
	hour = resolveAngle(angle_h, 12);
	minute = resolveAngle(angle_h, 60);
	return;
}
void Time::setTime(float angle_h, float angle_m, float angle_s)
{
	setTime(angle_h, angle_m);
	second = resolveAngle(angle_s, 60);
	return;
}

std::string Time::sayTime()
{
	return std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
}



int Time::getHour()
{
	return hour;
}
int Time::getMinute()
{
	return minute;
}
int Time::getSecond()
{
	return second;
}
