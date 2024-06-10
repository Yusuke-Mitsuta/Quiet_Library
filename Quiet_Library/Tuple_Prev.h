/*!
 * Tuple_Prev.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple

{	//仕様
	//[tuple_t]の選択位置をひとつ前にする
	template<class T_Control_Tuple>
	struct I_Prev
	{
	private:
		//仕様
		//[tuple_t]の選択位置をひとつ前にする
		template<class T_Tuple_t>
		struct S_Prev
		{
			using type = T_Tuple_t;
		};

		template<class ...T_Tail_Types>
		struct S_Prev<tuple_tp<tuple_t<>, invalid_t, tuple_t<T_Tail_Types...>>>
		{
			using type = tuple_tp<tuple_t<>, invalid_t, tuple_t<T_Tail_Types...>>;
		};

		template<class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires (sizeof...(T_Head_Types) != 0 || is_invalid_not<T>)
		struct S_Prev<tuple_tp<tuple_t<T_Head_Types...>, T, tuple_t<T_Tail_Types...>>>
		{
			using type = U_Select<static_cast<int>(sizeof...(T_Head_Types)) - 1, tuple_tp<tuple_t< T_Head_Types...>, T, tuple_t<T_Tail_Types...>>>;
		};

	public:

		using type = I_Change_Tuple_tp_Action<S_Prev, T_Control_Tuple>::Return_p_Convert_Skip;

	};

}