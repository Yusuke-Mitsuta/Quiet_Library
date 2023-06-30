
//ƒtƒ@ƒCƒ‹–¼
//TimerControlManager.cpp
//
//ì¬“ú
//2022/09/01
//
//»ìÒ
//YUSUKE
//=================================================================

#include"TimerManager.h"
#include"TimeControl.h"
#include"Timer.h"

std::list<Timer*> Timer_Manager::timerList;

void Timer_Manager::FirstUpdate()
{
	Time deletaTime = Time_Control::GetDeltaTime();

	for (auto timer : timerList) 
	{
		timer->AddDeletaTime(deletaTime);
	}
}

void Timer_Manager::AddTimeAction(Timer* timer)
{
	timerList.push_back(timer);
}

void Timer_Manager::RemoveTimeAction(Timer* timer)
{
	timerList.remove(timer);
}
