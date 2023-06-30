#pragma once

//�t�@�C����
//TimeControl.h
//
//�쐬��
//2022/08/03
//
//�����
//YUSUKE
//=================================================================

#include "Component.h"
#include"Time.h"
#include"Link.h"

//�d�l
//���Ԃ𐧌䂷��
class Time_Control :
	public Component
{
private:

	//�d�l
	//���̎���
 	static Time nowTime;

	//�d�l
	//1�t���[���O�̎���
	static Time prevTime;

	//�d�l
	//1�t���[���Ԃ̎���
	static Time deletaTime;

public:

	void Start();

	//�d�l
	//���݂̎��Ԃ��擾���A�f���^�^�C�������߂�
	void FirstUpdate();

	//�d�l
	//1�t���[���Ԃ̎��Ԃ��擾
	static Time GetDeltaTime();

	//�d�l
	//���̎��Ԃ��擾
	static Time GetNowTime();

	//�d�l
	//1�t���[���O�̎��Ԃ��擾����
	static Time GetPrevTime();

};
