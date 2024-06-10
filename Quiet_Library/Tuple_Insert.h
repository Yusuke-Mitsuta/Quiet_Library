/*!
 * Tuple_Insert.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"SwapType.h"

namespace quiet::N_Tuple
{
	//仕様
	//[T_Insert_Base_Tuple]の選択位置に[T_Merge_Types...]の要素を追加する
	//
	//using
	//[tuple_expand]::[T_Add_type...]の中にtupleが含まれる場合、tupleを展開し、格納する
	template<class T_Insert_Base_Tuple, class ...T_Insert_Type>
	struct I_Insert
	{
	private:


		template<class T_Base_Tuple,
			class T_Add_Types_Tuple = tuple_t<T_Insert_Type...>>
		struct S_Insert
		{
			using type = T_Base_Tuple;
		};

		template<class T_Base_Head, class T, class ...T_Tail_Types,
			class T_Front_Add_Type,class ...T_Add_Type>
		struct S_Insert<tuple_tp<T_Base_Head, T, tuple_t<T_Tail_Types...>>,
			tuple_t<T_Front_Add_Type,T_Add_Type...>>
		{
			using type = tuple_tp < T_Base_Head, T_Front_Add_Type,
				tuple_t<T_Add_Type..., T, T_Tail_Types...>>;
		};

		template<class T_Base_Head, class ...T_Tail_Types,
			class T_Front_Add_Type, class ...T_Add_Type>
		struct S_Insert<tuple_tp<T_Base_Head, invalid_t, tuple_t<T_Tail_Types...>>,
			tuple_t<T_Front_Add_Type, T_Add_Type...>>
		{
			using type = tuple_tp<T_Base_Head, T_Front_Add_Type,
				tuple_t<T_Add_Type..., T_Tail_Types...>>;
		};


		template<class T_Base_Tuple,
			class T_Add_Types_Tuple = tuple_t<T_Insert_Type...>,
			class T_Insert_Tuple = U_Tuple_v_To_t<U_Remove_p<typename T_Add_Types_Tuple::type>>>
		struct S_Insert_Tuple_Expand
		{
			using type = S_Insert_Tuple_Expand<
				typename S_Insert<T_Base_Tuple, T_Insert_Tuple>::type,
				U_Next<T_Add_Types_Tuple>>::type;
		};

		template<class T_Base_Tuple,class T_Add_Types_Tuple>
		struct S_Insert_Tuple_Expand<T_Base_Tuple,T_Add_Types_Tuple,invalid_t>
		{
			using type = T_Base_Tuple;
		};

	public:

		using tuple_expand = I_Change_Tuple_tp_Action<S_Insert_Tuple_Expand, T_Insert_Base_Tuple>::type;

		using type = I_Change_Tuple_tp_Action<S_Insert, T_Insert_Base_Tuple>::type;

	};
}
