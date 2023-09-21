#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	template<class T_Tuple_t>
	struct I_Remove
	{
	private:
		template<class T_Tuple_t>
		struct S_Remove;

		template<not_is_nullopt T>
		struct S_Remove<Tuple_tp<Head_t<>, T, Tail_t<>>>
		{
		private:

		public:
			using Type = Tuple_tp<Head_t<>, std::nullopt_t, Tail_t<>>;
		};

		template<class ...T_Head_Types, not_is_nullopt T>
		struct S_Remove<Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<>>>
		{
		private:
			using Tuple_Prev = typename I_Prev<Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<>>>::Type;

		public:
			using Type = typename I_Remove<Tuple_Prev>::Type;
		};

		template<class ...T_Head_Types, not_is_nullopt T, class T_Next_Type, class ...T_Tail_Types>
		struct S_Remove<Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<T_Next_Type, T_Tail_Types...>>>
		{
			using Type = Tuple_tp<Head_t<T_Head_Types...>, T_Next_Type, Tail_t<T_Tail_Types...>>;
		};

		template<class ...T_Head_Types, class ...T_Tail_Types>
		struct S_Remove<Tuple_tp<Head_t<T_Head_Types...>, std::nullopt_t, Tail_t<T_Tail_Types...>>>
		{
			using Type = Tuple_tp<Head_t<T_Head_Types...>, std::nullopt_t, Tail_t<T_Tail_Types...>>;
		};

	public:
		
		using Type = typename S_Action_Tuple_tp<S_Remove, T_Tuple_t>::type;

	};

}
