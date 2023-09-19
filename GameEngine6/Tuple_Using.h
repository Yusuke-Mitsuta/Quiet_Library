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

	//[T_Tuple_t]の並び順を反転させる
	template<class T_Tuple>
	using U_Reverse = typename I_Reverse<T_Tuple>::Type;

	//仕様
	//[T_Tuple]の[_Index]番目の型を取得する
	template<int _Index, class T_Tuple_t>
	using U_Element_t = typename I_Element<_Index, T_Tuple_t>::Type;


	template< class T_Tuple_t, int _Index>
	using U_Element_tau = typename I_Element<_Index, T_Tuple_t>::Type;

	//仕様
	//[T_Tuple]の[_Index]番目の要素を取得する
	template<int _Index, class T_Tuple_v>
	static constexpr auto U_Element_v = I_Element<_Index, T_Tuple_v>::value;

}