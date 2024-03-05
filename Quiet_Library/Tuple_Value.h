/*!
 * Tuple_Value.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

#include"Tuple_Control.h"

namespace quiet
{
	template<auto t_Value>
	struct integral_constant
	{
		using value_type = decltype(t_Value);
		static constexpr auto value = t_Value;

	};

	template<quiet::N_Tuple::same_as_tuple_v T_Head, auto value, quiet::N_Tuple::same_as_tuple_v T_Tail>
	struct tuple_vp :
		quiet::N_Tuple::Control_v<tuple_vp<T_Head, value, T_Tail>>
	{
	};

	template<auto ...t_Value>
	struct tuple_v :
		quiet::N_Tuple::Control_v<tuple_v<t_Value...>>
	{

	};

}

namespace std
{

	template<class T_Head,auto t_Value,class T_Tail>
	struct tuple_size<quiet::tuple_vp<T_Head,t_Value,T_Tail>> :
		integral_constant<size_t, quiet::N_Tuple::S_Parameter<quiet::tuple_vp<T_Head, t_Value, T_Tail>>::size>
	{
		static constexpr size_t value =
			quiet::N_Tuple::S_Parameter<quiet::tuple_vp<T_Head, t_Value, T_Tail>>::size;
	};

	template<auto ...t_Value>
	struct tuple_size<quiet::tuple_v<t_Value...>> :
		integral_constant<size_t,sizeof...(t_Value)>
	{
		static constexpr size_t value = sizeof...(t_Value);
	};
}

