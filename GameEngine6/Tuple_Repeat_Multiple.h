#pragma once

#include"Tuple_Declare.h"
#include"Tuple.h"

namespace N_Tuple
{
	//仕様
	//要素に型[T]を[N]個持つ、[tuple_t]を作る
	template<class T,size_t N>
	struct I_Repeat_Multiple
	{
	private:
		template<size_t N,class ...Ts>
		struct S_Repeat_Multiple
		{
			using type = S_Repeat_Multiple<N - 1, T, Ts...>::type;
		};

		template< class ...Ts>
		struct S_Repeat_Multiple<0,Ts...>
		{
			using type = tuple_t<Ts...>;
		};
	public:
		using type = S_Repeat_Multiple<N>::type;

	};

}