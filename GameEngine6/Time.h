#pragma once

//ファイル名
//Time.h
//
//作成日
//2022/08/03
//
//製作者
//YUSUKE
//=================================================================

#include"Concept.h"

class MicroTime;

//仕様
//時間を秒単位で管理する
//
//補足
//int,float,double型は 単位(秒) として扱い、クラス内でμ秒に変換し、計算する
//MicroTime型はμ秒として扱い、計算する
class Time
{
private:

	//仕様
	//μ秒で扱うクラス
	friend MicroTime;

	//仕様
	//単位(μ秒)の時間
	long long time = 0;

public:

	Time(){}
	
	//仕様
	//単位(秒)の時間セットする
	Time(std::integral auto setTime);


	//仕様
	//単位(μ秒)の時間セットする
	Time(MicroTime setTime);

	//仕様
	//単位(秒)の時間を出力する
	//
	//返り値
	//単位(秒)の時間
	operator double();

	//仕様
	//単位(μ秒)の時間を出力する
	//
	//返り値
	//単位(μ秒)の時間:
	operator MicroTime();

	Time operator +(const std::integral auto  time2);
	Time operator +(const Time time2);
	Time operator +(MicroTime time2);

	Time operator -(const std::integral auto time2);
	Time operator -(const Time time2);
	Time operator -(MicroTime time2);


	void operator =(const std::integral auto time2);
	void operator =(MicroTime time2);


	void operator +=(const Time &time2);
	void operator -=(const Time &time2);

	void operator *=(const Time &time2);
	void operator /=(const Time &time2);

};

inline Time Time::operator+(const std::integral auto time2)
{
	Time sumTime;
	sumTime.time = time + static_cast<long long>(time2) * 1000000;
	return  sumTime;
}

inline Time Time::operator-(const std::integral auto time2)
{
	Time differenceTime;
	differenceTime.time = time - static_cast<long long>(time2) * 1000000;
	return  differenceTime;
}

inline void Time::operator=(const std::integral auto time2)
{
	time = static_cast<long long>(time2) * 1000000;
}

inline Time::Time(std::integral auto setTime)
{
	time = static_cast<long long>(setTime) * 1000000;
}


//仕様
//μ秒で計算する
//
//補足
//Time型はμ秒に換算し計算する
class MicroTime 
{
private:
	
	//仕様
	//単位(μ秒)の時間
	long long time = 0;

public:
	
	MicroTime(){}
	//仕様
	//単位(μ秒)で時間をセットする
	MicroTime(std::integral auto setTime);

	operator long long();
	operator Time();

	MicroTime operator +(const Time time2);
	MicroTime operator -(const Time time2);

	void operator +=(const MicroTime &time2);
	void operator -=(const MicroTime &time2);
						   
	void operator *=(const MicroTime &time2);
	void operator /=(const MicroTime &time2);

};

MicroTime::MicroTime(std::integral auto setTime)
{
	time = static_cast<long long>(setTime);
}
