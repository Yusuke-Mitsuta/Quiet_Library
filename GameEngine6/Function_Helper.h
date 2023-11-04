#pragma once

#include"Concept.h"
#include"Parameter.h"

namespace N_Function
{

	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data;

	template<class ...T_Fn_Parts>
	struct I_Function_Multiple_Helper;

	//�d�l
	//�֐��ɑ΂��āA���̊֐����̓��\�b�h���o�Ă���܂ł̊Ԃ̌^�������̌^�ƌ݊��������邩���肷��
	//���\�b�h�ɑ΂��ẮA��L�ɉ����A���\�b�h�̑O�̌^���|�C���^�[�̌^�ƌ݊��������邩���肵�A
	//	���s����΁A�e���v���[�g�̐擪�̌^���|�C���^�[�̌^�ƌ݊��������邩���肷��
	//���̑�����J��Ԃ��A�S�Đ�������΁A�֐��A���\�b�h�I�u�W�F�N�g���ɓZ�߂�ꂽ��A[tuple_t]�ɓZ�߂���B
	//
	//�e���v���[�g
	//[T_Fn_Parts...]:
	//	���\�b�h�Ɏg�p���鋤�ʂ̃|�C���^�[�̌^(�ȗ��\)
	//	�֐��A���̓��\�b�h�̌^
	//	����ɑ΂�������̌^(���т̈�Ԍ��̌^���A�֐��̈����^�̈�Ԍ��Ɣ��肳���)
	//	���̃��\�b�h�ɑ΂����p�̃|�C���^�[�̌^(���Ƀ��\�b�h���g�p����ꍇ)
	//	�֐��A���̓��\�b�h�̌^
	// �Ƒ���
	// 
	//�⑫ 
	//�֐��ɑ΂�������̌^�Ƃ��Ċ֐��̌^�����ꍇ
	//���̊Ԃ̌^�ƈ����̌^�Ɍ݊���������΁A�����Ƃ��Ď�낤�Ƃ��Ă�֐��̌^�����̊֐��Ƃ��Č��Ȃ����ׁA
	//	�P�̂̊֐��Ƃ��ď��������鎖
	template<class ...T_Fn_Parts>
	struct I_Function_Helper
	{
		using single_judge = S_Function_Single_Data<T_Fn_Parts...>;

		using multiple_judge = I_Function_Multiple_Helper<T_Fn_Parts... >;

		template<bool t_function_check_fg, bool t_method_check_fg,
				 class T_Function_Check = typename single_judge::function,
				 class T_Method_Check= typename single_judge::method>
		struct S_Function_Helper
		{
			using type = tuple_t<T_Function_Check>;
		};

		template<bool t_function_check_fg, bool t_method_check_fg,class T_Method_Check>
		struct S_Function_Helper<t_function_check_fg,t_method_check_fg,invalid_t,T_Method_Check>
		{
			using type = tuple_t<T_Method_Check>;
		};

		template<>
		struct S_Function_Helper<true,true, invalid_t, invalid_t>
		{
			using type = multiple_judge::type;
		};

		template<>
		struct S_Function_Helper<true,false, invalid_t, invalid_t>
		{
			using type = multiple_judge::function_check;
		};

		template<>
		struct S_Function_Helper<false,true, invalid_t, invalid_t>
		{
			using type = multiple_judge::method_check;
		};


		//�d�l
		//�t�@���N�V�����Ƃ��Ĕ��肵�A���s����΁A���\�b�h�Ƃ��Ĕ��肷��
		using type = S_Function_Helper<true, true>::type;

		//�d�l
		//�t�@���N�V�����Ƃ��Ĕ��肷��
		using function_check = S_Function_Helper<true, false>::type;

		//�d�l
		//���\�b�h�Ƃ��Ĕ��肷��
		using method_check = S_Function_Helper<false, true,invalid_t>::type;

	};


}