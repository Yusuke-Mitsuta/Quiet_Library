#pragma once

#include"Move_Template.h"
#include"Tuple_Class_Declare.h"

namespace quiet::N_Tuple
{
	//�d�l
	//[0 ... (N-1)]�̒l��[tuple_v]�ɓ���ĕԂ�
	//
	//�⑫
	//�܂�A[std::make_index_sequence<N>] �ŋA���Ă���^�� [std::integer_sequence<size_t,N...>]�̏����A[tupel_v<N...>]�ɕύX����
	template<size_t N>
	struct I_index_sequence
	{
	private:
		template<class T>
		struct S_index_sequence
		{
			using type = tuple_v<>;
		};

		template<size_t ...N>
		struct S_index_sequence<std::integer_sequence<size_t,N...>>
		{
			using type = tuple_v<N...>;
		};
	public:

		using type = typename S_index_sequence<std::make_index_sequence<N>>::type;
	};


	//�d�l
	//[N_1 ... N-2]�̒l��[tuple_v]�ɓ���ĕԂ�
	template<size_t N_1,size_t N_2>
	struct I_range_index_sequence
	{
	private:
		template<size_t N_1, size_t N_2>
		using start_number_change = typename I_Template_Calculate<typename
			I_index_sequence<N_2 - N_1>::type, "+", N_1>::type;


		template<size_t N_1 = N_1, size_t N_2 = N_2, bool t_max_judge = (N_1 < N_2)>
		struct S_range_index_sequence
		{
			using type = start_number_change<N_1, N_2>;
		};

		template<size_t N_1, size_t N_2>
		struct S_range_index_sequence<N_1,N_2,false>
		{
			using type = typename start_number_change<N_2, N_1>::reverse::remove_p;
		};

	public:

		using type = typename S_range_index_sequence<>::type;

	};


}