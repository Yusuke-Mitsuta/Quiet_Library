#pragma once

//�t�@�C����
//Timer.h
//
//�쐬��
//2022/09/01
//
//�����
//YUSUKE
//=================================================================

#include"Time.h"

//�d�l
//�^�C�}�[
//
//�⑫
// �u���v�Ő������Ԃ��Z�b�g����
//bool�ŃL���X�g�����ۂɁAtrue�Ŏw�莞�Ԃ��o��
//Time �ɃL���X�g����Όo�ߎ��Ԃ�Ԃ�
class Timer
{
private:

	//�d�l
	//�o�ߎ���
	Time sumTime = 0;

	//�d�l
	//��������
	Time limitTime = 0;

public:

	Timer();

	//�d�l
	//�������Ԃ��Z�b�g����
	//
	//����
	//setLimitTime::�Z�b�g���鐧������
	Timer(Time setLimitTime);

	~Timer();

	//�d�l
	//�������ԁA�o�ߎ��Ԃ��R�s�[����
	//
	//����
	//timer::�R�s�[���̃f�[�^
	void operator=(const Timer timer);

	//�d�l
	//�������Ԃ��Z�b�g����
	//
	//����
	//setLimitTime::�Z�b�g���鐧������
	void operator=(const Time setLimitTime);

	operator Time();

	//�d�l
	//�������ԂɒB���Ă��邩
	//
	//�Ԃ�l
	//�B���Ă���΁ATrue
	//�B���Ă��Ȃ���΁AFalse
	operator bool();

	//�d�l
	//�o�ߎ��ԂɈ�t���[���̎��Ԃ����Z����
	//
	//����
	//deletaTime::��t���[���̎���
	void AddDeletaTime(Time deletaTime);

	//�d�l
	//�o�ߎ��Ԃ�����������
	void ResetSumTime();

	//�d�l
	//�o�ߎ��Ԃ��擾����
	Time GetSumTime();

	//�d�l
	//�������Ԃ��擾����
	Time GetLimitTime();

	//�d�l
	//�c�莞�Ԃ��擾����
	//
	//�⑫
	//�c�莞�Ԃ��߂��Ă����0��Ԃ�
	Time GetTimeLeft();

};