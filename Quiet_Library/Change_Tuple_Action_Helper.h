#pragma once

#include"Tuple_Class_Declare.h"

namespace quiet::N_Tuple::N_Tuple_Convert_Action
{

	template<template<class...>class T_Action, size_t t_Start_Point, bool t_Return_p_Back>
	struct I_Set_StartPoint;

	struct I_Tuple_Convert_Action_Helper
	{

		struct L_Target;

		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t,
			bool t_Return_p_Convert_Skip,
			bool t_Return_tv_Convert_Skip,
			bool t_Return_p_Back,
			bool t_is_Set_StartPoint>
		struct L_Action;


		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t>
		struct L_Option;

		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t,
			bool t_Return_p_Convert_Skip,
			bool t_Return_tv_Convert_Skip>
		struct L_StartPoint;

		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t,
			bool t_Return_p_Convert_Skip,
			bool t_Return_tv_Convert_Skip>
		struct L_ReturnPoint;

	};

	template<bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip,
		bool t_Return_p_Back,
		bool t_is_Set_StartPoint>
	struct I_Tuple_Convert_Action_Helper::L_Action
	{
		template<bool t_is_Set_StartPoint_Fg>
		struct L_Is_Set_StartPoint
		{
			template<template<class...>class T_Action, class T_Convert_Tuple>
			using type = I_Tuple_Convert_Action<
				T_Action,
				T_Convert_Tuple,
				t_is_Target_Tuple_p,
				t_is_Target_Tuple_t,
				t_Return_p_Convert_Skip,
				t_Return_tv_Convert_Skip>::type;
		};

		template<>
		struct L_Is_Set_StartPoint<true>
		{

			template<template<class...>class T_Action, class T_Convert_Tuple, size_t t_StartPoint>
			using type = L_Is_Set_StartPoint<false>::type<
				I_Set_StartPoint<T_Action, t_StartPoint, t_Return_p_Back>::S_Set_StartPoint,
				T_Convert_Tuple>;
		};

		using type = L_Is_Set_StartPoint<t_is_Set_StartPoint>;
	};
	

	template<bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip>
	struct I_Tuple_Convert_Action_Helper::L_ReturnPoint
	{
		using Default = L_Action<t_is_Target_Tuple_p, t_is_Target_Tuple_t, t_Return_p_Convert_Skip, t_Return_tv_Convert_Skip, true, false>::type;

		using Reset_ReturnPoint = L_Action<t_is_Target_Tuple_p, t_is_Target_Tuple_t, t_Return_p_Convert_Skip, t_Return_tv_Convert_Skip, true, true>::type;

	};



	template<bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip>
	struct I_Tuple_Convert_Action_Helper::L_StartPoint
	{
		using type = L_Action<t_is_Target_Tuple_p,t_is_Target_Tuple_t,t_Return_p_Convert_Skip,t_Return_tv_Convert_Skip,false,false>::type;

	};


	template<
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip>
	struct I_Tuple_Convert_Action_Helper::L_StartPoint<true,t_is_Target_Tuple_t,t_Return_p_Convert_Skip,t_Return_tv_Convert_Skip>
	{
		struct S_Is_Target_p
		{
			using Default = L_Action<true, t_is_Target_Tuple_t, t_Return_p_Convert_Skip, t_Return_tv_Convert_Skip, false, false>::type;

			using Set_StartPoint = L_ReturnPoint<true, t_is_Target_Tuple_t, t_Return_p_Convert_Skip, t_Return_tv_Convert_Skip>;
		};

		using type = S_Is_Target_p;

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
			t_Return_tv_Convert_Skip>::type;

	public:

		using Default = StartPoint<false, false>;

		using Return_p_Convert_Skip = StartPoint<true, false>;

		using Return_tv_Convert_Skip = StartPoint<false, true>;

		using Return_Convert_Skip = StartPoint<true, true>;
		
	};

	struct I_Tuple_Convert_Action_Helper::L_Target
	{
	private:

		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t>
		using Option = L_Option<t_is_Target_Tuple_p, t_is_Target_Tuple_t>;

	public:

		using Target_Tuple_tp = Option<true, true>;

		using Target_Tuple_vp = Option<true, false>;

		using Target_Tuple_t = Option<false, true>;

		using Target_Tuple_v = Option<false, false>;
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