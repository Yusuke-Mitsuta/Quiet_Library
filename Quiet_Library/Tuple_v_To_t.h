/*!
 * Tuple_v_To_t.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{
	//仕様
	//[T_Request_Order]を[tuple_v,vp]から、要素を[integral_constant]で包み、[tuple_t,tp]に変換する
	template<class T>
	struct Tuple_v_To_t
	{
		using type = T;
	};

	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
		requires is_invalid_not<decltype(_Value)>
	struct Tuple_v_To_t<tuple_vp<tuple_v<t_Head_Value...>,
		_Value, tuple_v<t_Tail_Value...>>>
	{
		using type = tuple_tp<tuple_t<integral_constant<t_Head_Value>...>,
			integral_constant<_Value>,
			tuple_t<integral_constant<t_Tail_Value>...>>;
	};

	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
		requires is_invalid<decltype(_Value)>
	struct Tuple_v_To_t<tuple_vp<tuple_v<t_Head_Value...>,
		_Value, tuple_v<t_Tail_Value...>>>
	{
		using type = tuple_tp<tuple_t<integral_constant<t_Head_Value>...>,
			invalid_t,
			tuple_t<integral_constant<t_Tail_Value>...>>;
	};

	template<auto ..._Value>
	struct Tuple_v_To_t<tuple_v<_Value...>>
	{
		using type = tuple_t<integral_constant<_Value>...>;
	};
}