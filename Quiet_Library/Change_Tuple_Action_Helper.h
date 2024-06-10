#pragma once

#include"Tuple_Class_Declare.h"

namespace quiet::N_Tuple::N_Tuple_Convert_Action
{

	struct I_Tuple_Convert_Action_Helper
	{
	
			
		struct L_Target;

		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t>
		struct L_Option;

		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t,
			bool t_Return_p_Convert_Skip,
			bool t_Return_tv_Convert_Skip>
		struct L_StartPoint;

	};

	template<bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip>
	struct I_Tuple_Convert_Action_Helper::L_StartPoint
	{

		struct Default
		{

		};

		struct Set_StartPoint
		{

		};

	};

	template<bool t_is_Target_Tuple_p,bool t_is_Target_Tuple_t>
	struct I_Tuple_Convert_Action_Helper::L_Option
	{
	private:
		template<bool t_Return_p_Convert_Skip,
			bool t_Return_tv_Convert_Skip>
		using StartPoint = L_StartPoint<
			t_is_Target_Tuple_p, 
			t_is_Target_Tuple_t, 
			t_Return_p_Convert_Skip,
			t_Return_tv_Convert_Skip>;

	public:

		struct Default:
			StartPoint<false,false>
		{

		};

		struct Return_p_Convert_Skip:
			StartPoint<true,false>
		{

		};

		struct Return_tv_Convert_Skip:
			StartPoint<false,true>
		{

		};

		
		struct Return_Convert_Skip:
			StartPoint<true,true>
		{
		};
		
	};


	struct I_Tuple_Convert_Action_Helper::L_Target
	{
	private:

		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t>
		using Option = L_Option<t_is_Target_Tuple_p, t_is_Target_Tuple_t>;

	public:

		struct Target_Tuple_tp :
			Option<true,true>
		{

		};

		struct Target_Tuple_vp :
			Option<true,false>
		{

		};

		struct Target_Tuple_t :
			Option<false,true>
		{

		};

		struct Target_Tuple_v :
			Option<false,false>
		{

		};

	};
}

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
		size_t t_Start_Point>
	struct I_Change_Tuple_Action_Helper
	{
	private:

		template<bool t_Return_p_Convert_Skip_Fg, bool t_Return_tv_Convert_Skip_Fg, bool t_Return_p_Back_Fg >
		using Return_Convert_Skip_Base =
			I_Change_Tuple_Action<
			T_Action,
			T_Convert_Tuple,
			t_is_Target_Tuple_p,
			t_is_Target_Tuple_t,
			t_Start_Point,
			t_Return_p_Convert_Skip_Fg,
			t_Return_tv_Convert_Skip_Fg,
			t_Return_p_Back_Fg>::type;

	public:

		using type = Return_Convert_Skip_Base<false, false, false>;

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