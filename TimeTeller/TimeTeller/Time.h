#pragma once
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
class Time
{
private: 
	int hour, minute, second;
	const double revolution = 360.0;
	double reduceAngle(float angle);
	int resolveAngle(float angle, int timeSteps);

public:
	Time();
	Time(float h, float m);
	Time(float h, float m, float s);
	~Time();
	void setTime(float angle_h, float angle_m);
	void setTime(float angle_h, float angle_m, float angle_s);
	void setTime(std::vector<float> angles);
	std::string sayTime();

	int getHour();
	int getMinute();
	int getSecond();
};

