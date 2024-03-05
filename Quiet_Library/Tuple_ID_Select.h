/*!
 * Tuple_ID_Select.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Concept.h"

namespace quiet
{

	template<class ...T_Types>
	struct tuple_t;

	template<quiet::N_Tuple::same_as_tuple_t T_Head, class T, quiet::N_Tuple::same_as_tuple_t T_Tail>
	struct tuple_tp;

	template<auto ..._Value>
	struct tuple_v;

	template<quiet::N_Tuple::same_as_tuple_v T_Head, auto _value, quiet::N_Tuple::same_as_tuple_v T_Tail>
	struct tuple_vp;

}
namespace quiet::N_Tuple
{

	template<class T_Tuple>
	struct S_ID_Select
	{
		static constexpr E_Tuple_ID ID = E_Tuple_ID::NONE;
	};

	template<class ...T_Types>
	struct S_ID_Select<tuple_t<T_Types...>>
	{
		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_T;
	};

	template< auto ...t_value>
	struct S_ID_Select<tuple_v< t_value...>>
	{
		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_V;
	};

	template<class T_Head, class T, class T_Tail>
	struct S_ID_Select<tuple_tp<T_Head, T, T_Tail>>
	{
		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_TP;
	};

	template<class T_Head, auto t_value, class T_Tail>
	struct S_ID_Select<tuple_vp<T_Head, t_value, T_Tail>>
	{
		static constexpr E_Tuple_ID ID = E_Tuple_ID::TUPLE_VP;
	};
}