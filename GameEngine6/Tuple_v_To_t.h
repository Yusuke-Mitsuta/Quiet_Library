#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	template<class T>
	struct Tuple_v_To_t
	{
		using Type = T;
	};

	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
		requires not_is_nullopt<decltype(_Value)>
	struct Tuple_v_To_t<Tuple_vp<Head_v<t_Head_Value...>,
		_Value, Tail_v<t_Tail_Value...>>>
	{
		using Type = Tuple_tp<Head_t<integral_constant<t_Head_Value>...>,
			integral_constant<_Value>,
			Tail_t<integral_constant<t_Tail_Value>...>>;
	};

	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
		requires is_nullopt<decltype(_Value)>
	struct Tuple_v_To_t<Tuple_vp<Head_v<t_Head_Value...>,
		_Value, Tail_v<t_Tail_Value...>>>
	{
		using Type = Tuple_tp<Head_t<integral_constant<t_Head_Value>...>,
			std::nullopt_t,
			Tail_t<integral_constant<t_Tail_Value>...>>;
	};

	template<auto ..._Value>
	struct Tuple_v_To_t<Tuple_v<_Value...>>
	{
		using Type = Tuple_t<integral_constant<_Value>...>;
	};
}