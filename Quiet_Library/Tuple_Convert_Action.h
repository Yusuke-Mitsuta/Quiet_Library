/*!
 * Tuple_Type_Change_Action.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

#include"Tuple_Convert_Action_Helper.h"

namespace quiet::N_Tuple
{
	//�d�l
	//[T_Convert_Tuple]���w�肵��Tuple�ɕό`����B
	//	�e���v���[�g�e���v���[�g�p�����[�^[T_Action<...>]�̃p�����[�^�Ƃ��ăZ�b�g����B
	//	���̌チ���o�[�錾��[type]���Ăяo���B
	//���s��̌^�ɑ΂��āATuple�ɕό`���Ƌt�̓�����s���B
	struct I_Tuple_Convert_Action
	{
	public:

		using Target_Tuple_tp = N_Tuple_Convert_Action::I_Helper<true, true>::type;

		using Target_Tuple_vp = N_Tuple_Convert_Action::I_Helper<true,false>::type;

		using Target_Tuple_t = N_Tuple_Convert_Action::I_Helper<false, true>::type;

		using Target_Tuple_v = N_Tuple_Convert_Action::I_Helper<false,false>::type;
	};

}