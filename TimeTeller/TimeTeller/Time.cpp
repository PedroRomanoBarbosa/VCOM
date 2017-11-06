#include "Time.h"

Time::Time()
{
	hour = 0; minute = 0; second = 0;
}
Time::Time(float h, float m)
{
	hour = 0; minute = 0; second = 0;
	setTime(h, m);
}
Time::Time(float h, float m, float s)
{
	hour = 0; minute = 0; second = 0;
	setTime(h, m, s);
}

Time::~Time()
{}

double Time::reduceAngle(float angle)
{
	double a = fmod(angle, revolution);
	while (a < 0) {
		a += 360.0;
	}
	return a;
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
	minute = resolveAngle(angle_m, 60);
	if (minute <= 10) 
		hour = resolveAngle(angle_h + 9, 12);
	else if (minute >= 50) 
		hour = resolveAngle(angle_h - 9, 12);
	else
		hour = resolveAngle(angle_h, 12);
	return;
}
void Time::setTime(float angle_h, float angle_m, float angle_s)
{
	setTime(angle_h, angle_m);
	second = resolveAngle(angle_s, 60);
	return;
}

void Time::setTime(std::vector<float> angles) 
{
	switch (angles.size()) {
	case 2:
		setTime(angles[0], angles[1]);
		break;
	case 3:
		setTime(angles[0], angles[1], angles[2]);
		break;
	}
	return;
}

std::string Time::sayTime()
{

	std::stringstream res;
	res << std::setfill('0') << std::setw(2) << std::to_string(hour) << ":";
	res << std::setfill('0') << std::setw(2) << std::to_string(minute) << ":";
	res	<< std::setfill('0') << std::setw(2) << std::to_string(second);
	return res.str();
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
