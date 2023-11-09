#pragma once

#include"Outer_Change.h"
#include"Tuple_Class_Declare.h"

namespace N_Tuple
{
	//仕様
	//[0 ... (N-1)]の値を[tuple_v]に入れて返す
	//
	//補足
	//つまり、[std::make_index_sequence<N>] で帰ってくる型が [std::integer_sequence<size_t,N...>]の所を、[tupel_v<N...>]に変更する
	template<size_t N>
	struct I_make_index_sequence
	{

		template<class T>
		struct S_make_index_sequence
		{
			using type = tuple_v<>;
		};

		template<size_t ...N>
		struct S_make_index_sequence<std::integer_sequence<size_t,N...>>
		{
			using type = tuple_v<N...>;
		};

		using type = typename S_make_index_sequence<std::make_index_sequence<N>>::type;
	};

}