#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	template<class T>
	struct Tuple_t_To_v
	{
		using type = T;
	};

	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
	struct Tuple_t_To_v<Tuple_tp<Head_t<integral_constant<t_Head_Value>...>,
		integral_constant<_Value>,
		Tail_t<integral_constant<t_Tail_Value>...>>>
	{
		using type = Tuple_vp<Head_v<t_Head_Value...>, _Value, Tail_v<t_Tail_Value...>>;
	};

	template<auto ...t_Head_Value, auto...t_Tail_Value>
	struct Tuple_t_To_v<Tuple_tp<Head_t<integral_constant<t_Head_Value>...>,
		std::nullopt_t,
		Tail_t<integral_constant<t_Tail_Value>...>>>
	{
		using type = Tuple_vp<Head_v<t_Head_Value...>,std::nullopt, Tail_v<t_Tail_Value...>>;
	};

	template<auto..._Value>
	struct Tuple_t_To_v<Tuple_t<integral_constant<_Value>...>>
	{
		using type = Tuple_v<_Value...>;
	};

}
