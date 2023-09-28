#pragma once

#include"Tuple_Class_Declare.h"
#include"SwapType.h"

namespace N_Tuple
{
	//仕様
	//[T_Base_Tuple]の選択中の箇所に[T_Insert]の要素を追加する
	template<class T_Base_Tuple, class T_Insert, size_t t_Insert_Point>
	struct I_Insert
	{
	private:

		template<class T_Base_Tuple>
		struct S_Insert;

		template<class T_Base_Head,class T,class ...T_Tail_Types>
		struct S_Insert<tuple_tp<T_Base_Head, T,tuple_t<T_Tail_Types...>>>
		{
			using type = tuple_tp<T_Base_Head, T_Insert, 
				U_if_t1<tuple_t<T, T_Tail_Types...>, tuple_t< T_Tail_Types...>, not_is_nullopt<T>>>;
		};

		template<class T_Base_Tuple,class T_Insert_Tuple= U_Tuple_v_To_t<U_Remove_p<T_Insert>>>
		struct S_Insert_Tuple_Expand;

		template<class T_Base_Head, class T, class ...T_Tail_Types,class T_Insert_Flont_Type, class ...T_Insert_Types>
		struct S_Insert_Tuple_Expand<tuple_tp<T_Base_Head, T, tuple_t<T_Tail_Types...>>,tuple_t<T_Insert_Flont_Type,T_Insert_Types...>>
		{
			using type = tuple_tp<T_Base_Head, T_Insert_Flont_Type,
				U_if_t1<tuple_t<T_Insert_Types...,T, T_Tail_Types...>, tuple_t<T_Insert_Types...,T_Tail_Types...>, not_is_nullopt<T>>>;
		};

	public:

		using tuple_expand = S_Action_Tuple_tp<S_Insert_Tuple_Expand, T_Base_Tuple, t_Insert_Point>::type;

		using type = S_Action_Tuple_tp<S_Insert, T_Base_Tuple, t_Insert_Point>::type;


	};
}
