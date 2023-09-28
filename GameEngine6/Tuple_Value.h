#pragma once

#include"Tuple_Declare.h"

#include"Tuple_Control.h"

template<auto t_Value>
struct integral_constant
{
	using value_type = decltype(t_Value);
	static constexpr auto value = t_Value;

};

template<same_as_template_value<tuple_v> T_Head, auto _value, same_as_template_value<tuple_v> T_Tail>
struct tuple_vp :
	N_Tuple::Control_vp<T_Head, _value, T_Tail>
{

};

template<auto ..._Value>
struct tuple_v :
	N_Tuple::Control_vp<tuple_v<>, std::nullopt, tuple_v<>>
{

};

template<auto t_Flont_Value, auto ..._Value>
struct tuple_v<t_Flont_Value, _Value...> :
	N_Tuple::Control_vp<tuple_v<>, t_Flont_Value, tuple_v<_Value...>>
{

};

namespace std
{
	template<class T_Head,auto t_Value,class T_Tail>
	struct tuple_size<tuple_vp<T_Head,t_Value,T_Tail>> :
		integral_constant<size_t, N_Tuple::S_Parameter<tuple_vp<T_Head, t_Value, T_Tail>>::Size>
	{
		static constexpr size_t value =
			N_Tuple::S_Parameter<tuple_vp<T_Head, t_Value, T_Tail>>::Size;
	};

	template<auto ...t_Value>
	struct tuple_size<tuple_v<t_Value...>> :
		integral_constant<size_t,sizeof...(t_Value)>
	{
		static constexpr size_t value = sizeof...(t_Value);
	};
}

