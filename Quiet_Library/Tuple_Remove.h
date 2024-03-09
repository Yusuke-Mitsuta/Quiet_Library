/*!
 * Tuple_Remove.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{
	//仕様
	//選択位置の値を削除する
	template<class T_Remove_Tuple, size_t t_Remove_Point>
	struct I_Remove
	{
	private:
		template<class T_Tuple_p>
		struct S_Remove;

		template<is_invalid_not T>
		struct S_Remove<tuple_tp<tuple_t<>, T, tuple_t<>>>
		{
		private:

		public:
			using type = tuple_tp<tuple_t<>, invalid_t, tuple_t<>>;
		};

		template<same_as_tuple_t T_Head, is_invalid_not T>
		struct S_Remove<tuple_tp<T_Head, T, tuple_t<>>>
		{
			using type = tuple_tp<T_Head,invalid_t, tuple_t<>>;
		};

		template<same_as_tuple_t T_Head, is_invalid_not T, class T_Next_Type, class ...T_Tail_Types>
		struct S_Remove<tuple_tp<T_Head, T, tuple_t<T_Next_Type, T_Tail_Types...>>>
		{
			using type = tuple_tp<T_Head, T_Next_Type, tuple_t<T_Tail_Types...>>;
		};

		template<same_as_tuple_t T_Head, same_as_tuple_t T_Tail>
		struct S_Remove<tuple_tp<T_Head, invalid_t, T_Tail>>
		{
			using type = tuple_tp<T_Head, invalid_t, T_Tail>;
		};

		template<same_as_tuple_t T_Head,class T, same_as_tuple_t T_Tail>
			requires (t_Remove_Point != S_Parameter<T_Remove_Tuple>::head_size)
		struct S_Remove<tuple_tp<T_Head, T,T_Tail>>
		{
		private:
			using Tuple_Remove = typename S_Remove<U_Select<t_Remove_Point, tuple_tp<T_Head, T, T_Tail>>>::type;

		public:
			using type = U_Select<(t_Remove_Point<S_Parameter<T_Remove_Tuple>::head_size) ? S_Parameter<T_Remove_Tuple>::head_size - 1 : S_Parameter<T_Remove_Tuple>::head_size, Tuple_Remove>;
		};

	public:
		
		using type =S_Tuple_tp_Change_Action<S_Remove, T_Remove_Tuple>::type;

	};

}
