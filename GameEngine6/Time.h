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
	Time(int setTime);
	
	//�d�l
	//�P��(�b)�̎��ԃZ�b�g����
	Time(float setTime);
	
	//�d�l
	//�P��(�b)�̎��ԃZ�b�g����
	Time(double setTime);

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
