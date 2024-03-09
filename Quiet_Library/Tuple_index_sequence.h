/*!
 * Tuple_index_sequence.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Move_Template.h"
#include"Tuple_Class_Declare.h"

namespace quiet::N_Tuple
{
	//仕様
	//[0 ... (t_array_size-1)]の値を[tuple_v]に入れて返す
	//
	//補足
	//つまり、[std::make_index_sequence<t_array_size>] で帰ってくる型が [std::integer_sequence<size_t,t_array_size...>]の所を、[tupel_v<t_array_size...>]に変更する
	template<size_t N>
	struct I_index_sequence
	{
	private:
		template<class T>
		struct S_index_sequence
		{
			using type = tuple_v<>;
		};

		template<size_t ...Ns>
		struct S_index_sequence<std::integer_sequence<size_t,Ns...>>
		{
			using type = tuple_v<Ns...>;
		};
	public:

		using type = typename S_index_sequence<std::make_index_sequence<N>>::type;
	};


	//仕様
	//[N_1 ... t_array_size-2]の値を[tuple_v]に入れて返す
	template<size_t N_1,size_t N_2>
	struct I_range_index_sequence
	{
	private:
		template<size_t t_N_1, size_t t_N_2>
		using start_number_change = typename I_Template_Calculate<typename
			I_index_sequence<t_N_2 - t_N_1>::type, "+", t_N_1>::type;


		template<size_t t_N_1 = N_1, size_t t_N_2 = N_2, bool t_max_judge = (t_N_1 < t_N_2)>
		struct S_range_index_sequence
		{
			using type = start_number_change<t_N_1, t_N_2>;
		};

		template<size_t t_N_1, size_t t_N_2>
		struct S_range_index_sequence<t_N_1, t_N_2,false>
		{
			using type = typename start_number_change<t_N_2, t_N_1>::reverse::remove_p;
		};

	public:

		using type = typename S_range_index_sequence<>::type;

	};


}