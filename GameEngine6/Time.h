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
	Time(int setTime);
	
	//仕様
	//単位(秒)の時間セットする
	Time(float setTime);
	
	//仕様
	//単位(秒)の時間セットする
	Time(double setTime);

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

	Time operator +(const int time2);
	Time operator +(const float time2);
	Time operator +(const double time2);
	Time operator +(const Time time2);
	Time operator +(MicroTime time2);

	Time operator -(const int time2);
	Time operator -(const float time2);
	Time operator -(const double time2);
	Time operator -(const Time time2);
	Time operator -(MicroTime time2);


	void operator =(const int time2);
	void operator =(const float time2);
	void operator =(const double time2);
	void operator =(MicroTime time2);


	void operator +=(const Time &time2);
	void operator -=(const Time &time2);

	void operator *=(const Time &time2);
	void operator /=(const Time &time2);

};

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
	MicroTime(long long setTime);

	operator long long();
	operator Time();

	MicroTime operator +(const Time time2);
	MicroTime operator -(const Time time2);

	void operator +=(const MicroTime &time2);
	void operator -=(const MicroTime &time2);
						   
	void operator *=(const MicroTime &time2);
	void operator /=(const MicroTime &time2);

};
