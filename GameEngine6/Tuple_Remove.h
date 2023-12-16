#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	//仕様
	//選択位置の値を削除する
	template<class T_Tuple_p, size_t t_Remove_Point>
	struct I_Remove
	{
	private:
		template<class T_Tuple_p>
		struct S_Remove;

		template<not_is_invalid T>
		struct S_Remove<tuple_tp<tuple_t<>, T, tuple_t<>>>
		{
		private:

		public:
			using type = tuple_tp<tuple_t<>, invalid_t, tuple_t<>>;
		};

		template<same_as_tuple_t T_Head, not_is_invalid T>
		struct S_Remove<tuple_tp<T_Head, T, tuple_t<>>>
		{
		private:
			using Tuple_Prev = U_Prev<tuple_tp<T_Head, T, tuple_t<>>>;

		public:
			using type = S_Remove<Tuple_Prev>::type;
		};

		template<same_as_tuple_t T_Head, not_is_invalid T, class T_Next_Type, class ...T_Tail_Types>
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
			requires (t_Remove_Point != S_Parameter<T_Tuple_p>::Size_Head)
		struct S_Remove<tuple_tp<T_Head, T,T_Tail>>
		{
		private:
			using Tuple_Remove = typename S_Remove<U_Select<t_Remove_Point, tuple_tp<T_Head, T, T_Tail>>>::type;

		public:
			using type = U_Select<(t_Remove_Point<S_Parameter<T_Tuple_p>::Size_Head) ? S_Parameter<T_Tuple_p>::Size_Head - 1 : S_Parameter<T_Tuple_p>::Size_Head, Tuple_Remove>;
		};

	public:
		
		using type =S_Action_Tuple_tp<S_Remove, T_Tuple_p>::type;

	};

}
