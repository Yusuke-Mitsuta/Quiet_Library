
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

Time::Time(MicroTime setTime)
{
	time = setTime;
}

Time::operator double()
{
	double douleTime = static_cast<double>(time);
	return douleTime/= 1000000;
}

Time::operator MicroTime()
{
	return MicroTime(time);
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
	double product = static_cast<double>(time) * time2.time;
	time = static_cast<long long>(product) / 1000000;
}

void Time::operator/=(const Time &time2)
{
	double quotient = static_cast<double>(time) / time2.time;
	time = static_cast<long long>(quotient) * 1000000;

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
