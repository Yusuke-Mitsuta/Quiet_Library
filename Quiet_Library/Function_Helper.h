#pragma once

#include"Concept.h"
#include"Function_Single_Helper.h"
#include"Function_Multiple_Helper.h"

namespace quiet::N_Function
{

	//�d�l
	// �֐��ɑ΂��āA���̊֐��I�u�W�F�N�g���o�Ă���܂ł̊Ԃ̌^�������̌^�ƌ݊��������邩���肷��
	//���\�b�h�ɑ΂��ẮA��L�ɉ����A���\�b�h�̑O�̌^���|�C���^�[�̌^�ƌ݊��������邩���肵�A
	//	���s����΁A�e���v���[�g�̐擪�̌^���|�C���^�[�̌^�ƌ݊��������邩���肷��
	//���̑�����J��Ԃ��A�S�Đ�������΁A[Function_Core]���ɓZ�߂�ꂽ��A[tuple_t]�ɓZ�߂���B
	//
	//�e���v���[�g
	//[T_Fn_Parts...]:
	//	���\�b�h�Ɏg�p���鋤�ʂ̃|�C���^�[�̌^(�ȗ��\)
	//	�֐��I�u�W�F�N�g�̌^
	//	����ɑ΂�������̌^(���т̈�Ԍ��̌^���A�֐��̈����^�̈�Ԍ��Ɣ��肳���)
	//	���̃��\�b�h�ɑ΂����p�̃|�C���^�[�̌^(���Ƀ��\�b�h���g�p����ꍇ)
	//	�֐��I�u�W�F�N�g�̌^
	// �Ƒ���
	// 
	//�⑫
	//�֐��ɑ΂�������̌^�Ƃ��Ċ֐��̌^�����ꍇ
	//���̊Ԃ̌^�ƈ����̌^�Ɍ݊���������΁A�����Ƃ��Ď�낤�Ƃ��Ă�֐��̌^�����̊֐��Ƃ��Č��Ȃ����ׁA
	//	�P�̂̊֐��Ƃ��ď��������鎖
	template<class ...T_Fn_Parts>
	struct I_Function_Helper
	{
	private:

		//�d�l
		//�P�̂̊֐��I�u�W�F�N�g�Ƃ��ď����ł��邩���肷��
		template<class T_Fn_Single = I_Function_Single_Helper<T_Fn_Parts...>,
			class T_Fn_Single_Judge =typename T_Fn_Single::judge>
		struct S_Function_Helper
		{
			using type = T_Fn_Single;
		};

		//�d�l
		//�P�̂̊֐��I�u�W�F�N�g�Ƃ��ď����ł��Ȃ��ꍇ�A�����̊֐��I�u�W�F�N�g�Ƃ��Ĕ��肷��
		template<class T_Fn_Single>
		struct S_Function_Helper<T_Fn_Single,invalid_t>
		{
			using type = I_Function_Multiple_Helper<T_Fn_Parts...>;
		};

		using function_helper =
			//I_Function_Multiple_Helper<T_Fn_Parts...>;
			S_Function_Helper<>::type;
		
	public:

		//�d�l
		//[Function_Core]���Z�߂�ꂽ[tuple_t]�A�Ⴕ����[Function_Core]
		using type = function_helper::type;

		//�d�l
		//�Z�߂�ꂽ�֐��I�u�W�F�N�g���ɑΉ������A�g�p�����^�̔ԍ������Z�߂�ꂽ[tupel_t]
		using access_number = function_helper::access_number;

		//�d�l
		//�Z�ߍ�Ƃ���������΁A[T_Fn_Parts...]�̐擪�̌^���A���s����΁A[invalid_t]��Ԃ�
		using judge = function_helper::judge;

	};


}