/*!
 * Tuple_Type_Change_Action.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Type_Change_Action_Helper.h"

#include"Template_Class_Change.h"
#include"SwapType.h"

namespace quiet::N_Tuple
{

	//�d�l
	//[T_Tuple_Data]���w�肵���^�ɕό`���A[T_Action]�̃e���v���[�g�ɕό`��̌^��[T_Leftover_Types...]�����킹�āA[T_Action<...>::type]�����s����
	//���s��̌^��T_Tuple�̌^�̏����ɖ߂�
	//
	//�e���v���[�g
	//[t_Action_Type_Tuple_p]::[T_Action]�����s���鎞�ɗv������Tuple���|�C���g������[tuple_tp,tuple_vp]�ł��邩�H
	//[t_Action_Type_Tuple_t]::[T_Action]�����s���鎞�ɗv������Tuple���^���Ǘ�[tuple_t,tuple_tp]�ł��邩�H
	//[t_Action_break]::[T_Action]�����s��A�|�C���g�����̏�Ԃ��ێ����邩�H
	//[T_Action]::[T_Action< ... >::type]�Ŏ��s����^
	//[T_Tuple_Data]::�����ɉ����ĕύX����Tuple
	//[T_Leftover_Types...]::[T_Action]�Ŏ��s���A�ύX���Tuple�̌��ɑ�����^
	//
	//�⑫
	//[t_Action_break == true],[T_Tuple_Data=tuple_vp],�v������^[tuple_t]�̎��A���Ă���Tuple�̌^��[tuple_v]�ɂȂ�
	//
	//�^�̕ω���[2�i�� or 1�߂�]�̂ǂ��炩�ŕω���������
	//[tp �� t �� v �� vp �� tp]
	//
	//����
	//[T_Action]�̗v������^�ɔ�n�e���v���[�g�͊܂܂Ȃ���
	template<template<class...>class T_Action, 
		class T_Convert_Tuple,
		bool t_is_Target_Tuple_p, 
		bool t_is_Target_Tuple_t,
		size_t t_Start_Point,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip, 
		bool t_Return_p_Back>
	struct I_Change_Tuple_Action
	{
	private:

		template<class T_Action_Tuple, class T_Start_Point = integral_constant<t_Start_Point>>
		struct S_Start_Point_Set
		{
			using type = T_Action<T_Action_Tuple>;
		};

		template<class T_Action_Tuple, class T_Start_Point>
			requires requires
		{
			requires is_Tuple_p<T_Action_Tuple>;
			requires T_Action_Tuple::size > T_Start_Point::value;
			requires T_Action_Tuple::head_size != T_Start_Point::value;
		}
		struct S_Start_Point_Set<T_Action_Tuple, T_Start_Point>
		{
			using type = S_Start_Point_Set<U_Select<T_Start_Point::value, T_Action_Tuple>>::type;
		};

		using action = S_Start_Point_Set<U_Change_Tuple<T_Convert_Tuple, t_is_Target_Tuple_p, t_is_Target_Tuple_t>>::type;


		template<class T = T_Convert_Tuple>
		struct S_Result
		{
			using result = U_Change_Tuple<action, 
				((is_Tuple_p<T_Convert_Tuple> && !t_Return_p_Convert_Skip) ||
				(t_is_Target_Tuple_p && t_Return_p_Convert_Skip)),
				((is_Tuple_t<T_Convert_Tuple> && !t_Return_tv_Convert_Skip) ||
				(t_is_Target_Tuple_t && t_Return_tv_Convert_Skip))>::type;

			template<class T_Result_Tuple = result>
			struct S_Create_p
			{
				using type = T_Result_Tuple;
			};


			template<class T_Result_Tuple>
				requires requires
			{
				requires t_Return_p_Back;
				requires (T_Convert_Tuple::head_size != t_Start_Point);
				requires (T_Convert_Tuple::head_size >= T_Result_Tuple::size);
			}
			struct S_Create_p<T_Result_Tuple>
			{
				using type = U_Select<T_Convert_Tuple::head_size, T_Result_Tuple>;
			};

			using type = S_Create_p<>::type;

		};

		template<class ...Ts,template<class...>class T_Outer>
		struct S_Result<T_Outer<Ts...>>
		{
			using type = N_Template::U_Class_Change<action, T_Outer>;
		};
		
		template<bool t_Return_p_Convert_Skip_Fg, bool t_Return_tv_Convert_Skip_Fg, bool t_Return_p_Back_Fg >
		using Return_Convert_Skip_Base = 
			I_Change_Tuple_Action<T_Action,
			T_Convert_Tuple, 
			t_is_Target_Tuple_p, 
			t_is_Target_Tuple_t,
			t_Start_Point, 
			t_Return_p_Convert_Skip_Fg, 
			t_Return_tv_Convert_Skip_Fg,
			t_Return_p_Back_Fg>::type;

	public:

		using type = S_Result<>::type;


		//�d�l
		//[T_Action<...>::type]���s���point�����̏�Ԃւ̕ϊ����X�L�b�v����
		using Return_p_Convert_Skip = Return_Convert_Skip_Base<true, false, false>;

		//�d�l
		//[T_Action<...>::type]���s��̌��̏�Ԃւ�[tuple_t��v],[tuple_v��t]�ϊ����X�L�b�v����
		using Return_tv_Convert_Skip = Return_Convert_Skip_Base<false, true, false>;

		//�d�l
		//[T_Action<...>::type]���s��̌��̏�Ԃւ̕ϊ����X�L�b�v����
		using Return_Convert_Skip = Return_Convert_Skip_Base<true, true, false>;

		//�d�l
		//[t_Start_Point]�ɂĊJ�n�|�C���g��ύX�����ہA���̈ʒu�ւ̃|�C���g�ړ����X�L�b�v����
		using Return_Point_Back = Return_Convert_Skip_Base<false, false, true>;
	};

}