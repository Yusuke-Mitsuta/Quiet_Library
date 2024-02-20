#pragma once

#include"Tuple.h"
#include"Function_Superficial_Data.h"

template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function;

namespace quiet::N_Function
{

	//�d�l
	//[T_Parts...]����S�ʂ��operator()���쐬����ׂɃf�[�^�𐮗�����B
	//
	//�e���v���[�g
	//[T_Parts...]::[Funcsion]�̈����̌^
	//
	//using 
	//[::type] �A���Ă���f�[�^�͊֐��P�P�ɑ΂���
	//	��������v�������ɌĂяo��[Funcsion]�̈����̔ԍ�
	//	�v������|�C���^�[�̌^
	//�@�v����������̌^
	//��[tuple_t]�œZ�߁A�P�P�̌��ʂ�[tuple_t]�œZ�߂�
	template<class ...T_Parts>
	struct I_Function_Operator_Helper
	{
		using fn_multi_data = I_Function_Helper<T_Parts...>;

		using core = Function_Core<Function<T_Parts...>>;


		//�d�l
		//[T_Parts...]�����ɑS�ʂ��operator()�ɃA�N�Z�X����ׂ̃f�[�^���쐬����B
		//
		//�e���v���[�g
		//[T_access_number]::�֐��I�u�W�F�N�g�P�P�̎g�p��������̔ԍ���Z�߂��^
		//[T_request_pointer]::�֐��I�u�W�F�N�g�P�P�̗v������|�C���^�[�̌^��Z�߂��^
		//[T_request_args]::�֐��I�u�W�F�N�g�P�P�̗v����������̌^��Z�߂��^
		// 
		//�⑫
		//�֐��I�u�W�F�N�g�P�ɑ΂��āA�����̊֐����Z�߂��Ă���ꍇ�A������W�J������������
		template<
			class T_access_number_List = typename fn_multi_data::access_number,
			class T_request_args_List = typename core::superficial::request_args,
			class T_request_pointer_List = typename core::superficial::request_pointer,
			class T_Result = tuple_t<>>
		struct S_Function_Operator_Helper
		{
			using type = T_Result;
		};

		//�d�l
		// [T_access_number],[T_request_args],[T_request_pointer]�̑S�Ă�[tuple_t]�œZ�߂��Ă��炸�A
		// �v������������L���ȏꍇ�A[T_Rusult]�Ƀf�[�^��ǉ�����B
		template<class T_access_number, class T_request_args,
			class T_request_pointer, class ...T_Result>
			requires requires
		{
			requires !N_Tuple::same_as_tuple_t<T_access_number>;
			requires !N_Tuple::same_as_tuple_t<T_request_args>;
			requires !N_Tuple::same_as_tuple_t<T_request_pointer>;
			requires is_invalid_not<T_request_args>;
		}
		struct S_Function_Operator_Helper<T_access_number,
			T_request_args, T_request_pointer,tuple_t<T_Result...>>
		{
			using operator_data = tuple_t<
				T_access_number,
				typename T_request_args::remove_p,
				T_request_pointer>;

			using type = tuple_t<T_Result...,operator_data>;
		};

		//�d�l
		//[T_access_number_List],[T_request_args_List],[T_request_pointer_List]�̂����A�����ꂩ1�ȏオ
		// [tuple_t]�œZ�߂��Ă���ꍇ�A���̒l����肤��S�p�^�[�����ċN�e���v���[�g�ɂ��擾����
		//
		//�⑫
		//[T_access_number_List],[T_request_args_List],[T_request_pointer_List]�̂����A
		// �����ꂩ�̌^��[tuple_t<>]�ƂȂ������A�ċN�������I������
		template<class T_access_number_List, class T_request_args_List,
			class T_request_pointer_List, class T_Result>
			requires requires
		{
			requires same_as_nor<tuple_t<>,T_access_number_List, T_request_args_List, T_request_pointer_List>;
		}
		struct S_Function_Operator_Helper<T_access_number_List,
			T_request_args_List, T_request_pointer_List, T_Result>
		{


			//�d�l
			//[T_Data]��[tuple_t]�œZ�߂��Ă���ꍇ�́A�擪�̗v�f�̎擾�A���������{�A
			//�Z�߂��Ă��Ȃ��ꍇ�́A���̂܂܂̒l��Ԃ�
			template<class T_Data>
			struct S_Data_Expand
			{
				using remove = T_Data;
				using type = T_Data;
			};

			template<class T_Front_Data,class ...T_Data>
			struct S_Data_Expand<tuple_t<T_Front_Data, T_Data...>>
			{
				using remove = tuple_t<T_Data...>;
				using type = T_Front_Data;
			};

			//�d�l
			//[T_access_number_List],[T_request_args_List],[T_request_pointer_List]�̂����A
			// [tuple_t]�œZ�߂��Ă���l�͐擪�̗v�f�A
			// �Z�߂��Ă��Ȃ��ꍇ�́A[S_Function_Operator_Helper]�Ɠ����^��p����A
			// ���̒l�Ŏ�肤��S�p�^�[����[T_Result]�ɒǉ�����
			using result = S_Function_Operator_Helper<
				typename S_Data_Expand<T_access_number_List>::type,
				typename S_Data_Expand<T_request_args_List>::type,
				typename S_Data_Expand<T_request_pointer_List>::type,
				T_Result>::type;



			//�d�l
			//[T_access_number_List],[T_request_args_List],[T_request_pointer_List]�̂����A�����ꂩ1�ȏオ
			// [tuple_t]�œZ�߂��Ă���ꍇ�́A�擪�̗v�f��r�����A�Z�߂��Ă��Ȃ��ꍇ�́A
			// [S_Function_Operator_Helper]�Ɠ����^��p���莟�̔�����s���B
			using type = S_Function_Operator_Helper<
				typename S_Data_Expand<T_access_number_List>::remove,
				typename S_Data_Expand<T_request_args_List>::remove,
				typename S_Data_Expand<T_request_pointer_List>::remove,
				result>::type;
		};

		using type = S_Function_Operator_Helper<>::type;

	};





}










