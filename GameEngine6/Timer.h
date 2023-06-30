#pragma once

//ファイル名
//Timer.h
//
//作成日
//2022/09/01
//
//製作者
//YUSUKE
//=================================================================

#include"Time.h"

//仕様
//タイマー
//
//補足
// 「＝」で制限時間をセットする
//boolでキャストした際に、trueで指定時間が経過
//Time にキャストすれば経過時間を返す
class Timer
{
private:

	//仕様
	//経過時間
	Time sumTime = 0;

	//仕様
	//制限時間
	Time limitTime = 0;

public:

	Timer();

	//仕様
	//制限時間をセットする
	//
	//引数
	//setLimitTime::セットする制限時間
	Timer(Time setLimitTime);

	~Timer();

	//仕様
	//制限時間、経過時間をコピーする
	//
	//引数
	//timer::コピー元のデータ
	void operator=(const Timer timer);

	//仕様
	//制限時間をセットする
	//
	//引数
	//setLimitTime::セットする制限時間
	void operator=(const Time setLimitTime);

	operator Time();

	//仕様
	//制限時間に達しているか
	//
	//返り値
	//達していれば、True
	//達していなければ、False
	operator bool();

	//仕様
	//経過時間に一フレームの時間を加算する
	//
	//引数
	//deletaTime::一フレームの時間
	void AddDeletaTime(Time deletaTime);

	//仕様
	//経過時間を初期化する
	void ResetSumTime();

	//仕様
	//経過時間を取得する
	Time GetSumTime();

	//仕様
	//制限時間を取得する
	Time GetLimitTime();

	//仕様
	//残り時間を取得する
	//
	//補足
	//残り時間を過ぎていれば0を返す
	Time GetTimeLeft();

};