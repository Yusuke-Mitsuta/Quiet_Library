#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	//Žd—l
	//[T_Base_Tuple]‚ÌŒã‚ë‚É[T_Merge]‚Ì—v‘f‚ð’Ç‰Á‚·‚é
	template<class T_Base_Tuple, class T_Merge>
	struct I_Merge
	{
	private:

		template<class T_Base_Tuple, class T_Merge_Tuple = U_Tuple_v_To_t<U_Remove_p<T_Merge>>>
		struct S_Merge_Tuple_Expand;


		template<class T_Base_Head, class T_Base, class ...T_Base_Tail_Types,class ...T_Merge_Types>
		struct S_Merge_Tuple_Expand<tuple_tp<T_Base_Head, T_Base, tuple_t<T_Base_Tail_Types...>>,
			tuple_t<T_Merge_Types...>>
		{
			using type = tuple_tp<T_Base_Head, T_Base,
				tuple_t< T_Base_Tail_Types..., T_Merge_Types...>>;
		};

		template<class T_Base_Head,class T_Merge_Front_Type, class ...T_Merge_Types>
		struct S_Merge_Tuple_Expand<tuple_tp<T_Base_Head, invalid_t, tuple_t<>>,
			tuple_t<T_Merge_Front_Type,T_Merge_Types...>>
		{
			using type = tuple_tp<T_Base_Head,T_Merge_Front_Type,tuple_t<T_Merge_Types...>>;
		};

		template<class T_Base_Tuple>
		struct S_Merge;

		template<class T_Base_Head, class T, class ...T_Tail_Types>
		struct S_Merge<tuple_tp<T_Base_Head, T, tuple_t<T_Tail_Types...>>>
		{
			using type = tuple_tp<T_Base_Head, 
				U_if_t1<T,T_Merge,not_is_invalid<T> + sizeof...(T_Tail_Types)>,
				U_if_t1<tuple_t<T_Tail_Types...,T_Merge>, tuple_t<>, not_is_invalid<T> +sizeof...(T_Tail_Types)>>;
		};

	public:

		using tuple_expand= S_Action_Tuple_tp<S_Merge_Tuple_Expand, T_Base_Tuple>::type;

		using type = S_Action_Tuple_tp<S_Merge, T_Base_Tuple>::type;
	};
}