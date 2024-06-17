/*!
 * Tuple_Using.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Class_Declare.h"
#include"Tuple_Convert_Action.h"

namespace quiet::N_Tuple
{

	//先頭の要素を選択する
	template<class T_Tuple>
	using U_Front = typename I_Select<0, T_Tuple>::type;

	//最後の要素を選択する
	template<class T_Tuple>
	using U_Back = typename I_Select<static_cast<int>(S_Parameter<T_Tuple>::size) - 1, T_Tuple>::type;

	//次の要素を選択する
	template<class T_Tuple>
	using U_Next = typename I_Next<T_Tuple>::type;

	//前の要素を選択する
	template<class T_Tuple>
	using U_Prev = typename I_Prev<T_Tuple>::type;

	//指定した番号の要素を選択する
	template<int t_Select_Point, class T_Tuple>
	using U_Select = typename I_Select<t_Select_Point, T_Tuple>::type;

	//[type]の並び順を反転させる
	template<class T_Tuple>
	using U_Reverse = typename I_Reverse<T_Tuple>::type;

	//仕様
	//[T_Tuple_Data]の[_Index]番目の型を取得する
	template<int _Index, class ...T>
	using U_Element_t = typename I_Element<_Index, T...>::type;

	//仕様
	//[T_Insert_Base_Tuple]の選択中の箇所に[T_Add_Typee...]の要素を追加する
	template<class T_Base_Tuple, class ...T_Add_Typee>
	using U_Insert = typename I_Insert<T_Base_Tuple, T_Add_Typee...>::type;

	//仕様
	//[T_Insert_Base_Tuple]の選択中の箇所に[t_Add_value...]の要素を追加する
	template<class T_Base_Tuple, auto ...t_Add_value>
	using U_Insert_v = typename I_Insert<T_Base_Tuple,
		integral_constant<t_Add_value>...>::type;

	//仕様
	//[T_Insert_Base_Tuple]の選択中の箇所に[T_Insert_Tuple]の要素を追加する
	//	[T_Add_type...]の中にtupleが含まれる場合、tupleを展開し、格納する
	template<class T_Base_Tuple,class ...T_Add_Type>
	using U_Insert_tuple_expand = typename I_Insert<T_Base_Tuple, T_Add_Type...>::tuple_expand;

	//仕様
	//[T_Insert_Base_Tuple]の後ろに[T_Merge_Types...]の要素を追加する
	template<class T_Base_Tuple, class ...T_Add_Type>
	using U_Merge = typename I_Merge<T_Base_Tuple, T_Add_Type...>::type;

	//仕様
	//[T_Insert_Base_Tuple]の後ろに[T_Merge_Types...]の要素を追加する
	template<class T_Base_Tuple, auto ...t_Add_value>
	using U_Merge_v = typename I_Merge<T_Base_Tuple, 
		integral_constant< t_Add_value>...>::type;

	//仕様
	//[T_Insert_Base_Tuple]の後ろに[T_Merge_Types...]の要素を追加する
	//	[T_Add_type...]の中にtupleが含まれる場合、tupleを展開し、格納する
	template<class T_Base_Tuple,class ...T_Add_Type>
	using U_Merge_tuple_expand = typename I_Merge<T_Base_Tuple, T_Add_Type...>::tuple_expand;

	//仕様
	//[T_Tuple_Data]の[t_Point_1]と[t_Point_2]の間の要素を取得する
	//[t_Point2]が設定されない場合、現在の選択位置を指定する
	template<class T_Tuple, size_t t_Point_1, size_t t_Point_2 = S_Parameter<T_Tuple>::head_size>
		//requires is_Element<T_Tuple_Data, t_Point_1>&& is_Element<T_Tuple_Data, t_Point_2>
	using U_Range = typename I_Range<T_Tuple, t_Point_1, t_Point_2>::type;

	//仕様
	//選択位置の値を削除する
	template<class T_Tuple_p, size_t t_Remove_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Remove = typename I_Remove<T_Tuple_p, t_Remove_Point>::type;


	template<class T_Tuple_v>
	using U_Tuple_t_To_v = typename Tuple_t_To_v<T_Tuple_v>::type;

	template<class T_Tuple_t>
	using U_Tuple_v_To_t = typename Tuple_v_To_t<T_Tuple_t>::type;


	//仕様
	//[T_Change_Type]を任意のTupleに変換する。
	//その後、[tuple_t,tuple_tp,tuple_v,tuple_vp]のいずれかに変換する。
	//
	//テンプレート
	//[t_is_Target_Tuple_p]::要求するTupleがポイントを所持[tuple_tp,tuple_vp]であるか？
	//[t_is_Target_Tuple_t]::要求するTupleが型を管理[tuple_t,tuple_tp]であるか？
	// 
	//補足
	//互換性の無い型の場合[invalid_t]を返す
	template<class T_Change_Type, bool t_is_Target_Tuple_p, bool t_is_Target_Tuple_t>
	using U_Change_Tuple = I_Change_Tuple<T_Change_Type, t_is_Target_Tuple_p, t_is_Target_Tuple_t>::type;

	//仕様
	//{Tuple}と互換性のある型を[tuple_t]型に変換する。
	// 
	//補足
	//互換性の無い型の場合[invalid_t]を返す
	template<class T_Change_Type>
	using U_Change_Tuple_t = I_Change_Tuple<T_Change_Type, false, true>::type;
	
	//仕様
	//{Tuple}と互換性のある型を[tuple_tp]型に変換する。
	// 
	//補足
	//互換性の無い型の場合[invalid_t]を返す
	template<class T_Change_Type>
	using U_Change_Tuple_tp = I_Change_Tuple<T_Change_Type, true, true>::type;

	//仕様
	//{Tuple}と互換性のある型を[tuple_v]型に変換する。
	// 
	//補足
	//互換性の無い型の場合[invalid_t]を返す
	template<class T_Change_Type>
	using U_Change_Tuple_v = I_Change_Tuple<T_Change_Type, false, false>::type;

	//仕様
	//{Tuple}と互換性のある型を[tuple_vp]型に変換する。
	// 
	//補足
	//互換性の無い型の場合[invalid_t]を返す
	template<class T_Change_Type>
	using U_Change_Tuple_vp = I_Change_Tuple<T_Change_Type, true, false>::type;

	//仕様
	//[T_Tuple_Data]の[t_Swap_Num_1]番目と[t_Swap_Num_2]番目の要素を入れ替える
	template<class T_Tuple, size_t t_Swap_Num_1, size_t t_Swap_Num_2 = S_Parameter<T_Tuple>::head_size>
		requires is_Element<T_Tuple, t_Swap_Num_1>&& is_Element<T_Tuple, t_Swap_Num_2>
	using U_Swap = typename I_Swap<T_Tuple, t_Swap_Num_1, t_Swap_Num_2>::type;


	//仕様
	//[T_Control_Tuple]の[t_Change_Point]の値を[T_Change]に変更する
	// 
	//[t_Change_Point]::[T_Control_Tuple]の変更する要素番号、指定しない場合は、現在の選択位置が仕様される
	template<class T_Tuple_p, class T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Change = typename I_Change<T_Tuple_p, T_Change, t_Change_Point>::type;

	//仕様
	//[T_Control_Tuple]の[t_Change_Point]の値を[T_Change]に変更する
	// 
	//[t_Change_Point]::[T_Control_Tuple]の変更する要素番号、指定しない場合は、現在の選択位置が仕様される
	template<class T_Tuple_p, auto t_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Change_v = typename I_Change<T_Tuple_p, 
		integral_constant<t_Change>, t_Change_Point>::type;


	//仕様
	//[T_Control_Tuple]の[t_Change_Point]の値を[T_Change]に変更する
	// 
	//[t_Change_Point]::[T_Control_Tuple]の変更する要素番号、指定しない場合は、現在の選択位置が仕様される
	template<class T_Tuple_p, is_Tuple T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Change_tuple_expand = typename I_Change<T_Tuple_p, T_Change, t_Change_Point>::tuple_expand;

	//仕様
	//[T_Tuple_Data]の[_Index]番目の要素を取得する
	template<int _Index, class T_Tuple_v>
	static constexpr auto U_Element_v = I_Element<_Index, T_Tuple_v>::value;

	template<class T_Tuple_not_p>
	using U_Create_p = typename I_Create_Pointer<T_Tuple_not_p>::type;

	template<class T_Tuple_p>
	using U_Remove_p = typename I_Remove_Pointer<T_Tuple_p>::type;
	

	template<class T_Tuple_v, auto number>
	using U_Template_Calculate_plus = typename I_Template_Calculate<T_Tuple_v, "+", number>::type;

	template<class T_Tuple_v, auto number>
	using U_Template_Calculate_minus = typename I_Template_Calculate<T_Tuple_v, "-", number>::type;

	//仕様
	//[T_Tuple_Data]から[tuple_v< ... >]の順番で型を順番に抽出
	template<class T_Tuple, class T_Extract_Number>
	using U_Extract = typename I_Extract<T_Tuple, T_Extract_Number>::type;


	//仕様
	//[T_Tuple_Data]の中身を[T_Outer_class]のテンプレートにセットする
	//[T_Tuple_Data]がtupleでない場合その型のまま実行される
	//
	//テンプレート
	//[T_Tuple_Data]::中身を展開するTuple
	//[T_Outer_class]::展開した中身とそれに続く型[T_Leftover_Types...]をセットする
	//[T_Leftover_Types...]::展開した中身に続いて設定する型
	//
	//補足
	//[T_Tuple_Data<types...>]->[T_Outer_class<types... , T_Leftover_Types...>]とする
	template<template<class...>class T_Outer_class, class T_Tuple, class ...T_Types>
	using U_Move_Template = typename I_Move_Template<T_Outer_class, T_Tuple, T_Types...>::type;

	//仕様
	//[0 ... (t_array_size-1)]の値を[tuple_v]に入れて返す
	//
	//補足
	//つまり、[std::make_index_sequence<t_array_size>] で帰ってくる型が [std::integer_sequence<size_t,t_array_size...>]の所を、[tupel_v<t_array_size...>]に変更する
	template<size_t N>
	using U_index_sequence = typename I_index_sequence<N>::type;

	//仕様
	//[0 ... (t_array_size-1)]の値を[tuple_v]に入れて返す
	//
	//補足
	//つまり、[std::make_index_sequence<t_array_size>] で帰ってくる型が [std::integer_sequence<size_t,t_array_size...>]の所を、[tupel_v<t_array_size...>]に変更する
	template<class T>
		requires requires
	{
		requires std::tuple_size_v<T> >= 0;
	}
	using U_index_sequence_tuple = typename I_index_sequence<std::tuple_size_v<T>>::type;


	//仕様
	//[N_1 ... t_array_size-2]の値を[tuple_v]に入れて返す
	template<size_t N_1, size_t N_2>
	using U_range_index_sequence = typename I_range_index_sequence<N_1, N_2>::type;

	//仕様
	//[T_Tuple_Data]の要素を一つずつ取り出し、[TT_Action]の[::type]を実行し、結果を[tuple_t]に纏める
	//
	//テンプレート
	//[TT_Action]::[type]を呼び出すクラステンプレート
	//[T_Tuple_Data]::展開し、各要素で[TT_Action::type]を呼び出す
	//[T_Extra...]::[TT_Action::type]を呼び出す際、追加でセットする型
	//
	//補足
	//[T_Tuple_Data -> tuple_t<T_Request_Order...>] -> [tuple_t<TT_Action<T_Request_Order,T_Extra...>::type...>]となる
	template<template<class...>class TT_Action, class T_Tuple, class ...T_Extra>
	using U_Elements_Action = I_Elements_Action<TT_Action, T_Tuple, T_Extra...>::type;

	//仕様
	//要素に型[T_Request_Order]を[t_array_size]個持つ、[tuple_t]を作る
	template<class T, size_t N>
	using U_Repeat_Multiple = I_Repeat_Multiple<T, N>::type;

	//仕様
	//指定した階層までタプル内の要素の中から、タプルと互換性を持つ型を展開する
	//
	// テンプレート
	//[T_Tuple_Data]::展開する[Tuple_t]の型
	//[t_expand_lelve]::展開する階層の上限
	//補足
	//[T_Tuple_Data]が[tuple]ではなかった場合[T_Tuple_Data]型を返す
	template<class T_Tuple, size_t t_expand_lelve = 1 >
	using U_Expand = I_Expand<T_Tuple, t_expand_lelve>::type;

	//仕様
	//タプル内の要素の中から、タプルと互換性を持つ型を全て展開する
	//
	// テンプレート
	//[T_Tuple_Data]::展開する[Tuple_t]の型
	//補足
	//[T_Tuple_Data]が[tuple]ではなかった場合[T_Tuple_Data]型を返す
	template<class T_Tuple>
	using U_Expand_All = I_Expand<T_Tuple, static_cast<size_t>(0-1)>::type;

	//仕様
	//パラメータパック[Ts...]から連続する型を{tuple_zip< T_Request_Order, t_array_size >}に圧縮する
	template<class ...Ts>
	using U_Zip = I_Zip<Ts...>::type;

	//仕様
	//タプル内の要素から連続する型を{tuple_zip< T_Request_Order, t_array_size >}に圧縮する
	template<class T_Tuple>
	using U_Zip_Tuple = I_Zip_Tuple<T_Tuple>::type;


	//仕様
	//[Tuple]と互換性のある型のリストから、指定した型が何番目に含まれるか探す。
	//
	//テンプレート
	//[T_Search_Tuple]::指定した型を探す、[Tuple]と互換性のある型
	//[T_Search_Type]::[T_Search_Tuple]から探す型
	template<class T_Search_Tuple, class T_Search_Type>
	using U_Search_t = I_Search_t<T_Search_Tuple, T_Search_Type>::type;

	//仕様
	//[Tuple_v]と互換性のある型のリストから、指定した値が何番目に含まれるか探す。
	//
	//テンプレート
	//[T_Search_Tuple]::指定した値を探す、[Tuple_v]と互換性のある型
	//[T_Search_Value]::[T_Search_Tuple]から探す型
	template<class T_Search_Tuple, auto t_Search_Value>
	using U_Search_v = I_Search_v<T_Search_Tuple, t_Search_Value>::type;

}

