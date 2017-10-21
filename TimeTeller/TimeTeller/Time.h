#pragma once
class Time
{
private: 
	int hour, minute, second;
	const double revolution = 360.0;
	double reduceAngle(float angle);
	int resolveAngle(float angle, int timeSteps);

public:
	Time();
	~Time();
	void setTime(float angle_h, float angle_m);
	void setTime(float angle_h, float angle_m, float angle_s);

	int getHour();
	int getMinute();
	int getSecond();
};

