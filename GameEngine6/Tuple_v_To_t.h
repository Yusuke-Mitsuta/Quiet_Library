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
	struct Tuple_v_To_t<Tuple_vp<_Head_v<t_Head_Value...>,
		_Value, _Tail_v<t_Tail_Value...>>>
	{
		using Type = Tuple_tp<_Head<integral_constant<t_Head_Value>...>,
			integral_constant<_Value>,
			_Tail<integral_constant<t_Tail_Value>...>>;
	};

	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
		requires is_nullopt<decltype(_Value)>
	struct Tuple_v_To_t<Tuple_vp<_Head_v<t_Head_Value...>,
		_Value, _Tail_v<t_Tail_Value...>>>
	{
		using Type = Tuple_tp<_Head<integral_constant<t_Head_Value>...>,
			std::nullopt_t,
			_Tail<integral_constant<t_Tail_Value>...>>;
	};

	template<auto ..._Value>
	struct Tuple_v_To_t<Tuple_v<_Value...>>
	{
		using Type = Tuple_t<integral_constant<_Value>...>;
	};
}