
//ƒtƒ@ƒCƒ‹–¼
//Timer.cpp
//
//ì¬“ú
//2022/09/01
//
//»ìŽÒ
//YUSUKE
//=================================================================

#include "Timer.h"
#include"TimerManager.h"
Timer::Timer()
{
	Timer_Manager::AddTimeAction(this);
}

Timer::Timer(Time setLimitTime)
{
	limitTime = setLimitTime;
	Timer_Manager::AddTimeAction(this);
}

Timer::~Timer()
{
	Timer_Manager::RemoveTimeAction(this);
}

void Timer::operator=(const Timer timer)
{
	this->sumTime = timer.sumTime;
	this->limitTime = timer.limitTime;
}

void Timer::operator=(const Time setLimitTime)
{
	limitTime = setLimitTime;
}

Timer::operator Time()
{
	return sumTime;
}

Timer::operator bool()
{
	return limitTime <= sumTime;
}

void Timer::AddDeletaTime(Time deletaTime)
{
	sumTime += deletaTime;
}

void Timer::ResetSumTime()
{
	sumTime = 0;
}

Time Timer::GetSumTime()
{
	return sumTime;
}

Time Timer::GetLimitTime()
{
	return limitTime;
}

Time Timer::GetTimeLeft()
{
	Time timeLeft = limitTime - sumTime;
	if (timeLeft < 0) {
		timeLeft = 0;
	}
	return timeLeft;
}