#pragma once

//仕様
//[T_1],[T_2]を[t_Order]によって入れ替える
//
//template
//T_1::タイプ1
//T_2::タイプ2
//t_Order::trueなら[T_1],[T_2]を入れ替える
template<class T_1, class T_2, bool t_Order>
struct IS_SwapType
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

	using Type_1 = S_SwapType<t_Order>::Type;
	using Type_2 = S_SwapType<!t_Order>::Type;
};

