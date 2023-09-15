#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{
	//先頭の要素を選択する
	template<class T_Tuple>
	using U_Flnot = typename I_Select<0, T_Tuple>::Type;

	//最後の要素を選択する
	template<class T_Tuple>
	using U_Back = typename I_Select<S_Parameter<T_Tuple>::Size - 1, T_Tuple>::Type;

	//次の要素を選択する
	template<class T_Tuple>
	using U_Next = typename I_Next<T_Tuple>::Type;

	//前の要素を選択する
	template<class T_Tuple>
	using U_Prev = typename I_Prev<T_Tuple>::Type;

	//指定した番号の要素を選択する
	template<int t_Select_Point,class T_Tuple>
	using U_Select = typename I_Select<t_Select_Point, T_Tuple>::Type;


}