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

		template<class ...T_Head_Types, not_is_nullopt T>
		struct S_Remove<Tuple_tp<_Head<T_Head_Types...>, T, _Tail<>>>
		{
		private:
			using Tuple_Prev = typename I_Prev<Tuple_tp<_Head<T_Head_Types...>, T, _Tail<>>>::Type;

		public:
			using Type = typename I_Remove<Tuple_Prev>::Type;
		};

		template<class ...T_Head_Types, not_is_nullopt T, class T_Next_Type, class ...T_Tail_Types>
		struct S_Remove<Tuple_tp<_Head<T_Head_Types...>, T, _Tail<T_Next_Type, T_Tail_Types...>>>
		{
			using Type = Tuple_tp<_Head<T_Head_Types...>, T_Next_Type, _Tail<T_Tail_Types...>>;
		};

		template<class ...T_Head_Types, class ...T_Tail_Types>
		struct S_Remove<Tuple_tp<_Head<T_Head_Types...>, std::nullopt_t, _Tail<T_Tail_Types...>>>
		{
			using Type = Tuple_tp<_Head<T_Head_Types...>, std::nullopt_t, _Tail<T_Tail_Types...>>;
		};

		using Action = S_Tuple_Action<T_Tuple_t, S_Remove>;

		friend struct Action;

	public:
		
		using Type = typename Action::Type;

	};

}
