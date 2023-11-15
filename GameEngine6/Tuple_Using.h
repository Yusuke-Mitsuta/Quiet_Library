#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{


	//先頭の要素を選択する
	template<class T_Tuple>
	using U_Front = typename I_Select<0, T_Tuple>::type;

	//最後の要素を選択する
	template<class T_Tuple>
	using U_Back = typename I_Select<static_cast<int>(S_Parameter<T_Tuple>::Size) - 1, T_Tuple>::type;

	//次の要素を選択する
	template<class T_Tuple>
	using U_Next = typename I_Next<T_Tuple>::type;

	//前の要素を選択する
	template<class T_Tuple>
	using U_Prev = typename I_Prev<T_Tuple>::type;

	//指定した番号の要素を選択する
	template<int t_Select_Point,class T_Tuple>
	using U_Select = typename I_Select<t_Select_Point, T_Tuple>::type;

	//[Type]の並び順を反転させる
	template<class T_Tuple>
	using U_Reverse = typename I_Reverse<T_Tuple>::type;

	//仕様
	//[T_Tuple]の[_Index]番目の型を取得する
	template<int _Index, class T_Tuple_t>
	using U_Element_t = typename I_Element<_Index, T_Tuple_t>::type;

	//仕様
	//[T_Base_Tuple]の選択中の箇所に[T_Insert_Tuple]の要素を追加する
	template<class T_Base_Tuple, class T_Insert_Tuple,size_t t_Insert_Point = S_Parameter<T_Base_Tuple>::Size_Head>
	using U_Insert = typename I_Insert<T_Base_Tuple, T_Insert_Tuple, t_Insert_Point>::type;

	//仕様
	//[T_Base_Tuple]の選択中の箇所に[T_Insert_Tuple]の要素を追加する
	template<class T_Base_Tuple,is_Tuple T_Insert_Tuple, size_t t_Insert_Point = S_Parameter<T_Base_Tuple>::Size_Head>
	using U_Insert_tuple_expand = typename I_Insert<T_Base_Tuple, T_Insert_Tuple, t_Insert_Point>::tuple_expand;

	//仕様
	//[T_Base_Tuple]の後ろに[T_Merge]の要素を追加する
	template<class T_Base_Tuple, class T_Merge>
	using U_Merge = typename I_Merge<T_Base_Tuple, T_Merge>::type;

	//仕様
	//[T_Base_Tuple]の後ろに[T_Merge]の要素を追加する
	template<class T_Base_Tuple,is_Tuple T_Merge_Tuple>
	using U_Merge_tuple_expand = typename I_Merge<T_Base_Tuple, T_Merge_Tuple>::tuple_expand;

	//仕様
	//[T_Tuple]の[t_Point_1]と[t_Point_2]の間の要素を取得する
	//[t_Point2]が設定されない場合、現在の選択位置を指定する
	template<class T_Tuple, size_t t_Point_1, size_t t_Point_2 = S_Parameter<T_Tuple>::Size_Head>
		requires is_Element<T_Tuple, t_Point_1>&& is_Element<T_Tuple, t_Point_2>
	using U_Range = typename I_Range<T_Tuple, t_Point_1, t_Point_2>::type;

	//仕様
	//選択位置の値を削除する
	template<class T_Tuple_p, size_t t_Remove_Point = S_Parameter<T_Tuple_p>::Size_Head>
	using U_Remove = typename I_Remove<T_Tuple_p, t_Remove_Point>::type;

	template<class T_Tuple_v>
	using U_Tuple_t_To_v = typename Tuple_t_To_v<T_Tuple_v>::type;

	template<class T_Tuple_t>
	using U_Tuple_v_To_t = typename Tuple_v_To_t<T_Tuple_t>::type;


	//仕様
	//[T_Tuple]の[t_Swap_Num_1]番目と[t_Swap_Num_2]番目の要素を入れ替える
	template<class T_Tuple, size_t t_Swap_Num_1, size_t t_Swap_Num_2 = S_Parameter<T_Tuple>::Size_Head>
		requires is_Element<T_Tuple, t_Swap_Num_1>&& is_Element<T_Tuple, t_Swap_Num_2>
	using U_Swap = typename I_Swap<T_Tuple, t_Swap_Num_1, t_Swap_Num_2>::type;


	//仕様
	//[T_Tuple_p]の[t_Change_Point]の値を[T_Change]に変更する
	// 
	//[t_Change_Point]::[T_Tuple_p]の変更する要素番号、指定しない場合は、現在の選択位置が仕様される
	template<class T_Tuple_p, class T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::Size_Head>
	using U_Change = typename I_Change<T_Tuple_p, T_Change, t_Change_Point>::type;

	//仕様
	//[T_Tuple_p]の[t_Change_Point]の値を[T_Change]に変更する
	// 
	//[t_Change_Point]::[T_Tuple_p]の変更する要素番号、指定しない場合は、現在の選択位置が仕様される
	template<class T_Tuple_p, is_Tuple T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::Size_Head>
	using U_Change_tuple_expand = typename I_Change<T_Tuple_p, T_Change, t_Change_Point>::tuple_expand;

	//仕様
	//[T_Tuple]の[_Index]番目の要素を取得する
	template<int _Index, class T_Tuple_v>
	static constexpr auto U_Element_v = I_Element<_Index, T_Tuple_v>::value;

	template<class T_Tuple_not_p>
	using U_Create_p = typename I_Create_Pointer<T_Tuple_not_p>::type;

	template<class T_Tuple_p>
	using U_Remove_p = typename I_Remove_Pointer<T_Tuple_p>::type;


	template<class T_Tuple_v,auto number>
	using U_Calculate_plus =typename I_Tuple_Calculate<T_Tuple_v, "+", number>::type;

	//仕様
	//[T_Tuple]から[tuple_v< ... >]の順番で型を順番に抽出
	template<class T_Tuple, class T_Extract_Number>
	using U_Extract =typename I_Extract<T_Tuple, T_Extract_Number>::type;


	//仕様
	//[T_Tuple]の中身を[T_Outer_class]のテンプレートにセットする
	//[T_Tuple]がtupleでない場合その型のまま実行される
	//
	//テンプレート
	//[T_Tuple]::中身を展開するTuple
	//[T_Outer_class]::展開した中身とそれに続く型[T_Types...]をセットする
	//[T_Types...]::展開した中身に続いて設定する型
	//
	//補足
	//[T_Tuple<types...>]->[T_Outer_class<types... , T_Types...>]とする
	template<template<class...>class T_Outer_class, class T_Tuple, class ...T_Types>
	using U_Expand_Set = typename I_Expand_Set<T_Outer_class, T_Tuple, T_Types...>::type;

	//仕様
	//[0 ... (N-1)]の値を[tuple_v]に入れて返す
	//
	//補足
	//つまり、[std::make_index_sequence<N>] で帰ってくる型が [std::integer_sequence<size_t,N...>]の所を、[tupel_v<N...>]に変更する
	template<size_t N>
	using U_index_sequence =typename I_index_sequence<N>::type;

	//仕様
	//[N_1 ... N-2]の値を[tuple_v]に入れて返す
	template<size_t N_1, size_t N_2>
	using U_range_index_sequence = typename I_range_index_sequence<N_1,N_2>::type;


}

