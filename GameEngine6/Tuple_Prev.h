#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple

{	//仕様
	//[Tuple_t]の選択位置をひとつ前にする
	template<class T_Tuple_t>
	struct I_Prev
	{
	private:
		//仕様
		//[Tuple_t]の選択位置をひとつ前にする
		template<class T_Tuple_t>
		struct S_Prev
		{
			using Type = T_Tuple_t;
		};

		template<class ...T_Tail_Types>
		struct S_Prev<Tuple_tp<Head_t<>, std::nullopt_t, Tail_t<T_Tail_Types...>>>
		{
			using Type = Tuple_tp<Head_t<>, std::nullopt_t, Tail_t<T_Tail_Types...>>;
		};

		template<class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires (sizeof...(T_Head_Types) != 0 || not_is_nullopt<T>)
		struct S_Prev<Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<T_Tail_Types...>>>
		{
			using Type = typename I_Select<static_cast<int>(sizeof...(T_Head_Types)) - 1, Tuple_tp<Head_t< T_Head_Types...>, T, Tail_t<T_Tail_Types...>>>::Type;
		};

		using Action = S_Tuple_Action<S_Prev, T_Tuple_t>;

		friend struct Action;

	public:

		using Type = typename Action::Type;

	};

}