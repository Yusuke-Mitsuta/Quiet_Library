/*!
 * Tuple_t_To_v.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{
	//�d�l
	//[T]��[tuple_t,tp]����A�v�f��[integral_constant]�Ŏ��o���A[tuple_v,vp]�ɕϊ�����
	template<class T>
	struct Tuple_t_To_v
	{
		using type = T;
	};

	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
	struct Tuple_t_To_v<tuple_tp<tuple_t<integral_constant<t_Head_Value>...>,
		integral_constant<_Value>,
		tuple_t<integral_constant<t_Tail_Value>...>>>
	{
		using type = tuple_vp<tuple_v<t_Head_Value...>, _Value, tuple_v<t_Tail_Value...>>;
	};

	template<auto ...t_Head_Value, auto...t_Tail_Value>
	struct Tuple_t_To_v<tuple_tp<tuple_t<integral_constant<t_Head_Value>...>,
		invalid_t,
		tuple_t<integral_constant<t_Tail_Value>...>>>
	{
		using type = tuple_vp<tuple_v<t_Head_Value...>,invalid, tuple_v<t_Tail_Value...>>;
	};

	template<auto..._Value>
	struct Tuple_t_To_v<tuple_t<integral_constant<_Value>...>>
	{
		using type = tuple_v<_Value...>;
	};

}
