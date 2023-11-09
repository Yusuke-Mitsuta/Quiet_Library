#pragma once

#include"Outer_Change.h"
#include"Tuple_Class_Declare.h"

namespace N_Tuple
{
	//�d�l
	//[0 ... (N-1)]�̒l��[tuple_v]�ɓ���ĕԂ�
	//
	//�⑫
	//�܂�A[std::make_index_sequence<N>] �ŋA���Ă���^�� [std::integer_sequence<size_t,N...>]�̏����A[tupel_v<N...>]�ɕύX����
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