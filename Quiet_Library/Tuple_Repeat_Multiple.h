/*!
 * Tuple_Repeat_Multiple.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"Tuple.h"

namespace quiet::N_Tuple
{
	//仕様
	//要素に型[T_Request_Order]を[t_array_size]個持つ、[tuple_t]を作る
	template<class T, size_t t_size>
	struct I_Repeat_Multiple
	{
	private:
		template<size_t N, class ...Ts>
		struct S_Repeat_Multiple
		{
			using type = S_Repeat_Multiple<N - 1, T, Ts...>::type;
		};

		template< class ...Ts>
		struct S_Repeat_Multiple<0, Ts...>
		{
			using type = tuple_t<Ts...>;
		};
	public:
		using type = S_Repeat_Multiple<t_size>::type;

	};

}