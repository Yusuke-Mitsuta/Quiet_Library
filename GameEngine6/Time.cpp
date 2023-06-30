
//ÉtÉ@ÉCÉãñº
//Time.cpp
//
//çÏê¨ì˙
//2022/08/03
//
//êªçÏé“
//YUSUKE
//=================================================================

#include "Time.h"

Time::Time(int setTime)
{
	time = setTime * 1000000;
}

Time::Time(float setTime)
{
	time = setTime * 1000000;
}

Time::Time(double setTime)
{
	time = setTime * 1000000;
}

Time::Time(MicroTime setTime)
{
	time = setTime;
}

Time::operator double()
{
	double douleTime = time;
	return douleTime/= 1000000;
}

Time::operator MicroTime()
{
	return MicroTime(time);
}


Time Time::operator+(const int time2)
{
	return operator+((double)time2);
}

Time Time::operator+(const float time2)
{
	return operator+((double)time2);
}

Time Time::operator+(const double time2)
{
	Time sumTime;
	sumTime.time = time + time2 * 1000000;
	return  sumTime;
}

Time Time::operator+(const Time time2)
{
	Time sumTime;
	sumTime.time = time + time2.time;
	return  sumTime;
}

Time Time::operator+(MicroTime time2)
{
	Time sumTime;
	sumTime.time = time + time2;
	return  sumTime;
}


Time Time::operator-(const int time2)
{

	return operator-((double)time2);
}

Time Time::operator-(const float time2)
{
	return operator-((double)time2);
}

Time Time::operator-(const double time2)
{
	Time differenceTime;
	differenceTime.time = time - time2 * 1000000;
	return  differenceTime;

}

Time Time::operator-(const Time time2)
{
	Time differenceTime;
	differenceTime.time = time - time2.time;
	return  differenceTime;
}

Time Time::operator-(MicroTime time2)
{
	Time differenceTime;
	differenceTime.time = time - time2;
	return  differenceTime;
}


void Time::operator=(const int time2)
{
	time = time2 * 1000000;
}

void Time::operator=(const float time2)
{
	time = time2 * 1000000;
}

void Time::operator=(const double time2)
{
	time = time2 * 1000000;
}

void Time::operator=(MicroTime time2)
{
	time = time2;
}


void Time::operator+=(const Time &time2)
{
	time += time2.time;
}

void Time::operator-=(const Time &time2)
{
	time -= time2.time;
}


void Time::operator*=(const Time &time2)
{
	double product = time * time2.time;
	time = product / 1000000;
}

void Time::operator/=(const Time &time2)
{
	double quotient = time / time2.time;
	time = quotient * 1000000;

}

MicroTime::MicroTime(long long setTime)
{
	time = setTime;
}

MicroTime::operator long long()
{
	return time;
}

MicroTime::operator Time()
{
	return Time(*this);
}

MicroTime MicroTime::operator+(const Time time2)
{
	return time + time2.time;
}
MicroTime MicroTime::operator-(const Time time2)
{
	return time - time2.time;
}

void MicroTime::operator+=(const MicroTime & time2)
{
	time += time2.time;
}

void MicroTime::operator-=(const MicroTime & time2)
{
	time -= time2.time;
}

void MicroTime::operator*=(const MicroTime & time2)
{
	time *= time2.time;
}

void MicroTime::operator/=(const MicroTime & time2)
{
	time /= time2.time;
}
