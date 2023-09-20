#pragma once

#include"Tuple_Declare.h"

#include"Tuple_Control.h"
#include"Tuple_Head.h"
#include"Tuple_Tail.h"

template<auto t_Value>
struct integral_constant
{
	using value_type = decltype(t_Value);
	static constexpr auto value = t_Value;

};

namespace N_Tuple
{

	template<same_as_template_value<Head_v> T_Head,auto _Value, same_as_template_value<Tail_v> T_Tail>
	struct Tuple_vp :
		Control_vp<T_Head, _Value, T_Tail>
	{

	};

	template<auto ..._Value>
	struct Tuple_v;

	template<auto t_Flont_Value, auto ..._Value>
	struct Tuple_v<t_Flont_Value,_Value...> :
		Control_vp<Head_v<>,t_Flont_Value, Tail_v<_Value...>>
	{

	};

	template<>
	struct Tuple_v<> :
		Control_vp<Head_v<>, std::nullopt, Tail_v<>>
	{

	};

}

namespace std
{
	template<class T_Head,auto t_Value,class T_Tail>
	struct tuple_size<N_Tuple::Tuple_vp<T_Head,t_Value,T_Tail>> :
		integral_constant<size_t, N_Tuple::S_Parameter< N_Tuple::Tuple_vp<T_Head, t_Value, T_Tail>>::Size>
	{
		static constexpr size_t value =
			N_Tuple::S_Parameter< N_Tuple::Tuple_vp<T_Head, t_Value, T_Tail>>::Size;
	};

	template<auto ...t_Value>
	struct tuple_size<N_Tuple::Tuple_v<t_Value...>> :
		integral_constant<size_t,sizeof...(t_Value)>
	{
		static constexpr size_t value = sizeof...(t_Value);
	};
}

