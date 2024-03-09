/*!
 * Tuple_Change.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{
	//仕様
	//[T_Control_Tuple]の[t_Change_Point]の値を[T_Change]に変更する
	// 
	//[t_Change_Point]::[T_Control_Tuple]の変更する要素番号、指定しない場合は、現在の選択位置が仕様される
	template<class T_Control_Tuple,class T_Change,size_t t_Change_Point>
	struct I_Change
	{
	private:

		template<class T_Tuple_p>
		struct S_Change
		{
			using type = T_Tuple_p;
		};

		template<class T_Head,is_invalid_not T,class T_Tail>
		struct S_Change<tuple_tp<T_Head,T,T_Tail>>
		{
			using type = tuple_tp<T_Head, T_Change, T_Tail>;
		};

		template<class T_Base_Tuple, class T_Change_Tuple = U_Tuple_v_To_t<U_Remove_p<T_Change>>>
		struct S_Change_Tuple_Expand
		{
			using type = T_Base_Tuple;
		};

		template<class T_Base_Head,is_invalid_not T, class ...T_Tail_Types, class T_Change_Front_Type, class ...T_Change_Types>
		struct S_Change_Tuple_Expand<tuple_tp<T_Base_Head, T, tuple_t<T_Tail_Types...>>, tuple_t<T_Change_Front_Type, T_Change_Types...>>
		{
			using type = tuple_tp<T_Base_Head, T_Change_Front_Type,tuple_t<T_Change_Types..., T_Tail_Types...>>;
		};

	public:

		using tuple_expand = S_Tuple_tp_Change_Action<S_Change_Tuple_Expand, T_Control_Tuple, t_Change_Point>::type;

		using type = S_Tuple_tp_Change_Action<S_Change, T_Control_Tuple,t_Change_Point>::type;

	};

}