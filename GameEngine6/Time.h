#pragma once

//�t�@�C����
//Time.h
//
//�쐬��
//2022/08/03
//
//�����
//YUSUKE
//=================================================================

#include"Concept.h"

class MicroTime;

//�d�l
//���Ԃ�b�P�ʂŊǗ�����
//
//�⑫
//int,float,double�^�� �P��(�b) �Ƃ��Ĉ����A�N���X���Ńʕb�ɕϊ����A�v�Z����
//MicroTime�^�̓ʕb�Ƃ��Ĉ����A�v�Z����
class Time
{
private:

	//�d�l
	//�ʕb�ň����N���X
	friend MicroTime;

	//�d�l
	//�P��(�ʕb)�̎���
	long long time = 0;

public:

	Time(){}
	
	//�d�l
	//�P��(�b)�̎��ԃZ�b�g����
	Time(std::integral auto setTime);


	//�d�l
	//�P��(�ʕb)�̎��ԃZ�b�g����
	Time(MicroTime setTime);

	//�d�l
	//�P��(�b)�̎��Ԃ��o�͂���
	//
	//�Ԃ�l
	//�P��(�b)�̎���
	operator double();

	//�d�l
	//�P��(�ʕb)�̎��Ԃ��o�͂���
	//
	//�Ԃ�l
	//�P��(�ʕb)�̎���:
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


//�d�l
//�ʕb�Ōv�Z����
//
//�⑫
//Time�^�̓ʕb�Ɋ��Z���v�Z����
class MicroTime 
{
private:
	
	//�d�l
	//�P��(�ʕb)�̎���
	long long time = 0;

public:
	
	MicroTime(){}
	//�d�l
	//�P��(�ʕb)�Ŏ��Ԃ��Z�b�g����
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
