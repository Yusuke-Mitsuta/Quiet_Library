#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple

{	//仕様
	//[tuple_t]の選択位置をひとつ前にする
	template<class T_Tuple_t>
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
		struct S_Prev<tuple_tp<tuple_t<>, std::nullopt_t, tuple_t<T_Tail_Types...>>>
		{
			using type = tuple_tp<tuple_t<>, std::nullopt_t, tuple_t<T_Tail_Types...>>;
		};

		template<class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires (sizeof...(T_Head_Types) != 0 || not_is_nullopt<T>)
		struct S_Prev<tuple_tp<tuple_t<T_Head_Types...>, T, tuple_t<T_Tail_Types...>>>
		{
			using type = U_Select<static_cast<int>(sizeof...(T_Head_Types)) - 1, tuple_tp<tuple_t< T_Head_Types...>, T, tuple_t<T_Tail_Types...>>>;
		};

	public:

		using type = S_Action_Tuple_tp<S_Prev, T_Tuple_t>::type;

	};

}