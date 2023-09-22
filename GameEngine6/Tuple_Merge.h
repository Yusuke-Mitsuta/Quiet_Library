#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	//仕様
	//[T_Base_Tuple]の後ろに[T_Merge_Tuple]の要素を追加する
	template<class T_Base_Tuple, class T_Merge_Tuple>
	struct I_Merge
	{
	private:

		using Merge_Tuple = U_Tuple_v_To_t<U_Remove_p<T_Merge_Tuple>>;

		template<class T_Base_Tuple, class T_Merge_Tuple = Merge_Tuple>
		struct S_Merge;

		template<class T_Base_Head, class T_Base, class ...T_Base_Tail_Types,class ...T_Merge_Types>
		struct S_Merge<Tuple_tp<T_Base_Head, T_Base, Tail_t<T_Base_Tail_Types...>>,
			Tuple_t<T_Merge_Types...>>
		{
			using type = Tuple_tp<T_Base_Head, T_Base,
				Tail_t< T_Base_Tail_Types..., T_Merge_Types...>>;
		};

		template<class T_Base_Head,class T_Merge_Flont_Type, class ...T_Merge_Types>
		struct S_Merge<Tuple_tp<T_Base_Head, std::nullopt_t, Tail_t<>>,
			Tuple_t<T_Merge_Flont_Type,T_Merge_Types...>>
		{
			using type = Tuple_tp<T_Base_Head,T_Merge_Flont_Type,Tail_t<T_Merge_Types...>>;
		};

	public:

		using type = S_Action_Tuple_tp<S_Merge, T_Base_Tuple>::type;
	};
}