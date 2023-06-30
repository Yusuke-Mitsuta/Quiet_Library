#pragma once

//�t�@�C����
//TimerControlManager.h
//
//�쐬��
//2022/09/01
//
//�����
//YUSUKE
//=================================================================

#include "Component.h"
#include"Time.h"

#include<list>
#include<functional>

class Timer;

//�d�l
//�S�Ă�timer���Ǘ�����
class Timer_Manager :
	public Component
{
private:

	//�d�l
	//timer�̃��X�g
	static std::list<Timer*> timerList;

public:

	void FirstUpdate();

	//�d�l
	//���X�g�Ƀ^�C�}�[��ǉ�����
	//
	//����
	//timer::�ǉ�����timer
	static void AddTimeAction(Timer* timer);

	//�d�l
	//���X�g�Ƀ^�C�}�[����^�C�}�[���O��
	//
	//����
	//timer::���X�g����O��timer
	static void RemoveTimeAction(Timer* timer);

};