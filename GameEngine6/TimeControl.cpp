
//ÉtÉ@ÉCÉãñº
//TimeControl.cpp
//
//çÏê¨ì˙
//2022/08/03
//
//êªçÏé“
//YUSUKE
//=================================================================

#include "TimeControl.h"

Time Time_Control::nowTime;
Time Time_Control::prevTime;
Time Time_Control::deletaTime;

void Time_Control::Start()
{
	nowTime = Link::GetNowTime();
	prevTime = nowTime;
	deletaTime = 0;
}

void Time_Control::FirstUpdate()
{
	prevTime = nowTime;
	nowTime = Link::GetNowTime();
	deletaTime = nowTime - prevTime;
}

Time Time_Control::GetNowTime()
{
	return nowTime;
}

Time Time_Control::GetPrevTime()
{
	return prevTime;
}

Time Time_Control::GetDeltaTime()
{
	return deletaTime;
}
