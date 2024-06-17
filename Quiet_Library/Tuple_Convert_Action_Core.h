#pragma once

#include"Tuple_Declare.h"
#include"Template_Class_Change.h"
#include"SwapType.h"

namespace quiet::N_Tuple::N_Tuple_Convert_Action
{

	template<template<class...>class T_Action,
		class T_Convert_Tuple,
		bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip>
	struct I_Tuple_Convert_Action_Core
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


}