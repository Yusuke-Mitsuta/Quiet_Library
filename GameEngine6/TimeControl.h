#pragma once

//ファイル名
//TimeControl.h
//
//作成日
//2022/08/03
//
//製作者
//YUSUKE
//=================================================================

#include "Component.h"
#include"Time.h"
#include"Link.h"

//仕様
//時間を制御する
class Time_Control :
	public Component
{
private:

	//仕様
	//今の時間
 	static Time nowTime;

	//仕様
	//1フレーム前の時間
	static Time prevTime;

	//仕様
	//1フレーム間の時間
	static Time deletaTime;

public:

	void Start();

	//仕様
	//現在の時間を取得し、デルタタイムを求める
	void FirstUpdate();

	//仕様
	//1フレーム間の時間を取得
	static Time GetDeltaTime();

	//仕様
	//今の時間を取得
	static Time GetNowTime();

	//仕様
	//1フレーム前の時間を取得する
	static Time GetPrevTime();

};
