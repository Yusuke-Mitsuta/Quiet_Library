/*!
 * Tuple_Type_Change_Action.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"Template_Class_Change.h"
#include"SwapType.h"

namespace quiet::N_Tuple
{

	//�d�l
	//[T_Convert_Tuple]���w�肵���^�ɕό`���A[T_Action]�̃e���v���[�g�ɕό`��̌^���e���v���[�g�N���X�����ɖ߂�
	//
	//�e���v���[�g
	//[T_Action]::[T_Action< ... >::type]�Ŏ��s����^
	//[T_Convert_Tuple]::�����ɉ����ĕύX����Tuple
	//[t_is_Target_Tuple_p]::[T_Action]�����s���鎞�ɗv������Tuple���|�C���g������[tuple_tp,tuple_vp]�ł��邩�H
	//[t_is_Target_Tuple_t]::[T_Action]�����s���鎞�ɗv������Tuple���^���Ǘ�[tuple_t,tuple_tp]�ł��邩�H
	//
	//�⑫
	//�^�̕ω���[2�i�� or 1�߂�]�̂ǂ��炩�ŕω���������
	//[tp �� t �� v �� vp �� tp]
	//
	//����
	//[T_Action]�̗v������^�ɔ�n�e���v���[�g�͊܂܂Ȃ���
	template<template<class...>class T_Action,
		class T_Convert_Tuple,
		bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip>
	struct I_Tuple_Convert_Action
	{
		
		using action = T_Action<U_Change_Tuple<T_Convert_Tuple, t_is_Target_Tuple_p, t_is_Target_Tuple_t>>::type;

		template<class T = T_Convert_Tuple>
		struct S_Result
		{
			using result = U_Change_Tuple<action,
				((is_Tuple_p<T_Convert_Tuple> && !t_Return_p_Convert_Skip) ||
					(t_is_Target_Tuple_p && t_Return_p_Convert_Skip)),
				((is_Tuple_t<T_Convert_Tuple> && !t_Return_tv_Convert_Skip) ||
					(t_is_Target_Tuple_t && t_Return_tv_Convert_Skip))>;

			using type = result;

		};

		template<class ...Ts, template<class...>class T_Outer>
			requires requires
		{
			requires (E_Tuple_ID::NONE == S_ID_Select<T_Outer<Ts...>>::ID);
		}
		struct S_Result<T_Outer<Ts...>>
		{
			using type = N_Template::U_Class_Change<action, T_Outer>;
		};

	public:

		using type = S_Result<>::type;

	};


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

		using action = T_Action<U_Change_Tuple<T_Convert_Tuple, t_is_Target_Tuple_p, t_is_Target_Tuple_t>>::type;
		
		template<class T = T_Convert_Tuple>
		struct S_Result
		{
			using result = U_Change_Tuple<action, 
				((is_Tuple_p<T_Convert_Tuple> && !t_Return_p_Convert_Skip) ||
				(t_is_Target_Tuple_p && t_Return_p_Convert_Skip)),
				((is_Tuple_t<T_Convert_Tuple> && !t_Return_tv_Convert_Skip) ||
				(t_is_Target_Tuple_t && t_Return_tv_Convert_Skip))>;
		
			using type = result;
		
		};
		
		template<class ...Ts,template<class...>class T_Outer>
			requires requires
		{
			requires (E_Tuple_ID::NONE == S_ID_Select<T_Outer<Ts...>>::ID);
		}
		struct S_Result<T_Outer<Ts...>>
		{
			using type = N_Template::U_Class_Change<action, T_Outer>;
		};
		


	public:

		using type = S_Result<>::type;
	};

}