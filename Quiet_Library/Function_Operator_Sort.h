#pragma once

#include"Tuple.h"

namespace quiet::N_Function
{

	//�d�l
	//[Function]�ɓ��ꂽ�ہA[::operator()]��
	// �Z�b�g�������Ԓʂ�ɕ\�������悤�ɕ��ёւ���
	//
	//�e���v���[�g
	//[T_Operator_Parameters]::[I_Function_Operator_Helper]����̃f�[�^���󂯎��
	// 
	//�⑫
	//[ 0, 1 , 2 , 3 , 4 , 5]�@�Ƃ������A
	//[ 0, 2 , 4 , 5 , 3 , 1]�@�̏��ԂɂȂ�ׁA
	// 
	//[ 0, 5 , 1 , 4 , 2 , 3]�@�̏��ԂɂȂ�l�ɕ��ёւ���ƁA
	//[ 0, 1 , 2 , 3 , 4 , 5]�@�̏��ԂɂȂ�
	template<class T_Operator_Parameters>
	struct I_Function_Operator_Sort
	{

		//�d�l
		//�O�ƌ�납��^��������A[T_Result]�Ɋi�[���čs��
		//	�^�񒆂̌^�̏ꍇ�́A���̌^��[T_Result]�Ɋi�[����
		//
		//�^�񒆂𒴂����ꍇ�A�i�[�������I������B
		template<class T_Result = tuple_t<>, 
			class T_Operator_Parameters = T_Operator_Parameters,
			class T_Reverse_Operator_Parameters = typename T_Operator_Parameters::reverse>
		struct S_Function_Operator_Sort
		{
			using type = T_Result;
		};
		
		//�d�l
		//�^�񒆂̌^�̏ꍇ�́A���̌^��[T_Result]�Ɋi�[����
		template<class ...T_Result, class T_Operator_Parameters, class T_Reverse_Operator_Parameters>
			requires requires
		{
			requires T_Operator_Parameters::head_size == T_Operator_Parameters::tail_size;
			requires T_Operator_Parameters::size > 0;
		}
		struct S_Function_Operator_Sort<tuple_t<T_Result...>,T_Operator_Parameters,T_Reverse_Operator_Parameters>
		{
			using type = tuple_t<T_Result...,typename T_Operator_Parameters::type>;
			using type3 = tuple_t<T_Result...,typename T_Operator_Parameters::type>;
			using type4 = T_Operator_Parameters::type;
		};

		//�d�l
		//�O�ƌ�납��^��������A[T_Result]�Ɋi�[���čs��
		template<class ...T_Result, class T_Operator_Parameters, class T_Reverse_Operator_Parameters>
			requires requires
		{
			requires T_Operator_Parameters::head_size < T_Operator_Parameters::tail_size;
		}
		struct S_Function_Operator_Sort<tuple_t<T_Result...>, T_Operator_Parameters, T_Reverse_Operator_Parameters>
		{
			
			using merge_tuple = tuple_t<T_Result...,
				typename T_Operator_Parameters::type,
				typename T_Reverse_Operator_Parameters::type>;

			using type = S_Function_Operator_Sort<merge_tuple,
				typename T_Operator_Parameters::next,
				typename T_Reverse_Operator_Parameters::next>::type;

			using type2 = S_Function_Operator_Sort<merge_tuple,
				typename T_Operator_Parameters::next,
				typename T_Reverse_Operator_Parameters::next>;
		};
		
		using type = S_Function_Operator_Sort<>::type;
		using type1 = S_Function_Operator_Sort<>;
	};

}