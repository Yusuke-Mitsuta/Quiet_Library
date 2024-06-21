#pragma once

//#include"SwapType.h"
#include"Tuple_Class_Declare.h"

namespace quiet::N_Tuple::N_Tuple_Convert_Action
{
	template<template<class...>class T_Action,
		class T_Convert_Tuple,
		bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip>
	struct I_Tuple_Convert_Action_Core;

	template<template<class...>class T_Action,
		class T_Convert_Tuple,
		bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip,
		size_t t_Start_Point,
		bool t_Return_p_Back>
	struct I_Set_StartPoint
	{

		template<class T_Convert_Tuple>
		struct S_Set_StartPoint
		{
			using type = T_Action<typename I_Select<t_Start_Point, T_Convert_Tuple>::type>::type;
		};

		template<class T_Convert_Tuple>
			requires requires
		{
			requires T_Convert_Tuple::size > t_Start_Point;
		}
		struct S_Set_StartPoint<T_Convert_Tuple>
		{
			using action = T_Action<typename I_Select<t_Start_Point, T_Convert_Tuple>::type>::type;

			using p_Back = typename I_Select<T_Convert_Tuple::head_size, action>::type;

			using type = U_if_t1<p_Back, action, t_Return_p_Back>;

		};

		using type = I_Tuple_Convert_Action_Core<
			S_Set_StartPoint,
			T_Convert_Tuple,
			t_is_Target_Tuple_p,
			t_is_Target_Tuple_t,
			t_Return_p_Convert_Skip,
			t_Return_tv_Convert_Skip>::type;
	};
}