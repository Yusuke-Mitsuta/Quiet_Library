#pragma once

#include<optional>
#include"Concept.h"
#include"If_Type.h"

//仕様
//[T_1],[T_2]を[t_Order]によって入れ替える
//
//template
//T_1::タイプ1
//T_2::タイプ2
//t_Order::trueなら[T_1],[T_2]を入れ替える
template<class T_1, class T_2,long long t_Order>
struct I_Swap_Type
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

//仕様
//[t_Order]が0なら[T_1],0以外なら[T_2]を返す
//
//template
//T_1::タイプ1
//T_2::タイプ2
//t_Order::trueなら[T_1],[T_2]を入れ替える
template<class T_1, class T_2, long long t_Order>
using U_Swap_t1 = typename I_Swap_Type<T_1, T_2, t_Order>::Type_1;

//仕様
//[t_Order]が0なら[T_2],0以外なら[T_1]を返す
//
//template
//T_1::タイプ1
//T_2::タイプ2
//t_Order::trueなら[T_1],[T_2]を入れ替える
template<class T_1, class T_2, long long t_Order>
using U_Swap_t2 = typename I_Swap_Type<T_1, T_2, t_Order>::Type_2;

//仕様
//[T],[invalid_t]で[I_Swap_Type]を作成する
//
//template
//T::タイプ
//t_Order::trueなら[Type1 = T],falseなら[Type1 = invalid_t]
template<class T, long long t_Order>
using U_Judge = I_Swap_Type<invalid_t, T, t_Order>;

//仕様
//[t_Order]が0なら[invalid_t],0以外なら[T]を返す
//
//template
//T::タイプ
//t_Order::フラグ
template<class T, long long t_Order>
using U_Judge_t = typename U_Judge<T, t_Order>::Type_1;

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

	static constexpr auto _1 = S_SwapType<static_cast<bool>(t_Order)>::Variable;
	static constexpr auto _2 = S_SwapType<!static_cast<bool>(t_Order)>::Variable;
};

template<auto t_1, auto t_2, int t_Order>
using U_Swap_v= IS_Swap_Variable<t_1, t_2, t_Order>;

template<auto t_1, auto t_2, int t_Order>
static constexpr auto U_Swap_v1 = IS_Swap_Variable<t_1, t_2, t_Order>::_1;

template<auto t_1, auto t_2, int t_Order>
static constexpr auto U_Swap_v2 = IS_Swap_Variable<t_1, t_2, t_Order>::_2;