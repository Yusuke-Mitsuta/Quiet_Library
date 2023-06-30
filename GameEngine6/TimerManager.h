#pragma once

//ファイル名
//TimerControlManager.h
//
//作成日
//2022/09/01
//
//製作者
//YUSUKE
//=================================================================

#include "Component.h"
#include"Time.h"

#include<list>
#include<functional>

class Timer;

//仕様
//全てのtimerを管理する
class Timer_Manager :
	public Component
{
private:

	//仕様
	//timerのリスト
	static std::list<Timer*> timerList;

public:

	void FirstUpdate();

	//仕様
	//リストにタイマーを追加する
	//
	//引数
	//timer::追加するtimer
	static void AddTimeAction(Timer* timer);

	//仕様
	//リストにタイマーからタイマーを外す
	//
	//引数
	//timer::リストから外すtimer
	static void RemoveTimeAction(Timer* timer);

};