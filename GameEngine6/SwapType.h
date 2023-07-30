#pragma once

#include"Concept.h"

//仕様
//[T_1],[T_2]を[t_Order]によって入れ替える
//
//template
//T_1::タイプ1
//T_2::タイプ2
//t_Order::trueなら[T_1],[T_2]を入れ替える
template<class T_1, class T_2,int t_Order>
struct IS_Swap_Type
{
	template<bool t_Order>
	struct S_SwapType
	{
		using Type = T_1;
	};

	template<>
	struct S_SwapType<true>
	{
		using Type = T_2;
	};

	using Type_1 = S_SwapType<static_cast<bool>(t_Order)>::Type;
	using Type_2 = S_SwapType<!static_cast<bool>(t_Order)>::Type;
};

template<class T_1, class T_2, int t_Order>
using IS_Swap_t1 = typename IS_Swap_Type<T_1, T_2, t_Order>::Type_1;

template<class T_1, class T_2, int t_Order>
using IS_Swap_t2 = typename IS_Swap_Type<T_1, T_2, t_Order>::Type_2;

template<class T, int t_Order >
using IS_Judge = IS_Swap_Type<std::nullopt_t, T, t_Order>;

template<class T, int t_Order>
using IS_JudgeType_t = typename IS_Judge<T, t_Order>::Type_1;

//仕様
//[t_1],[t_2]を[t_Order]によって入れ替える
//
//template
//T_1::変数１
//T_2::変数１
//t_Order::trueなら[T_1],[T_2]を入れ替える
template<auto t_1, auto t_2, int t_Order>
struct IS_Swap_Variable
{
	template<bool t_Order>
	struct S_SwapType
	{
		static constexpr auto Variable = t_1;
	};

	template<>
	struct S_SwapType<true>
	{
		static constexpr auto Variable = t_2;
	};

	static constexpr auto Variable_1 = S_SwapType<static_cast<bool>(t_Order)>::Variable;
	static constexpr auto Variable_2 = S_SwapType<!static_cast<bool>(t_Order)>::Variable;
};

template<auto t_1, auto t_2, int t_Order>
static constexpr auto IS_Swap_v1 = IS_Swap_Variable<t_1, t_2, t_Order>::Variable_1;

template<auto t_1, auto t_2, int t_Order>
static constexpr auto IS_Swap_v2 = IS_Swap_Variable<t_1, t_2, t_Order>::Variable_2;