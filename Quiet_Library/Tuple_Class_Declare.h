/*!
 * Tuple_Class_Declare.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include<tuple>

#include"Tuple_Concept.h"

#include"String.h"

namespace quiet
{

	template<auto t_Value>
	struct integral_constant;

	template<class ...T_Types>
	struct tuple_t;

	template<quiet::N_Tuple::same_as_tuple_t T_Head, class T, quiet::N_Tuple::same_as_tuple_t T_Tail>
	struct tuple_tp;

	template<auto ..._Value>
	struct tuple_v;

	template<quiet::N_Tuple::same_as_tuple_v T_Head, auto _value, quiet::N_Tuple::same_as_tuple_v T_Tail>
	struct tuple_vp;

}

namespace quiet::N_Tuple
{
	template<class T_Types>
	struct S_Parameter;

	template<class T_Tuple>
	struct S_Size;

	struct Tuple_p;

	template<class T_Tuple_p>
	struct I_Remove_Pointer;

	template<class T_Tuple_p>
	struct I_Create_Pointer;

	template<class T_Tuple>
	struct Control_p;

	template<class T_Tuple_t>
	struct I_Next;

	template<class T_Tuple_t>
	struct I_Prev;

	template<int t_Point, class T_Tuple_t>
	struct I_Select;

	template<size_t _Index, class T_Tuple>
	struct I_Element;

	template<class T_Tuple_p, size_t t_Remove_Point = S_Parameter<T_Tuple_p>::head_size>
	struct I_Remove;

	template<class T_Tuple_t>
	struct I_Reverse;

	template<class T_Base_Tuple, class ...T_Add_Typee>
	struct I_Insert;

	template<class T_Base_Tuple, class ...T_Add_Type>
	struct I_Merge;

	template<class T_Tuple_p, class T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	struct I_Change;

	template<class T_Tuple, size_t t_Swap_Num_1, size_t t_Swap_Num_2 = S_Parameter<T_Tuple>::head_size>
		requires is_Element<T_Tuple, t_Swap_Num_1>&& is_Element<T_Tuple, t_Swap_Num_2>
	struct I_Swap;

	template<class T_Tuple, size_t t_Point_1, size_t t_Point_2>
	struct I_Range;

	template<class T_Tuple, class T_Extract_Number>
	struct I_Extract;

	template<class T>
	struct Tuple_v_To_t;

	template<class T>
	struct Tuple_t_To_v;

	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
	struct S_Tuple_Type_Change_Action;

	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t,template<class...>class T_Action, class T_Tuple, size_t t_Start_Point= S_Parameter<T_Tuple>::head_size>
	struct S_Tuple_Type_Change_Action_Helper;


	//仕様
	//[T_Tuple]を[tuple_tp]に変換し[T_Action]の[::type]を呼び出し
	//　結果を[tuple_tp]から[T_Tuple]と同タイプのTupleに変換し返す。
	//
	//テンプレート
	//[T_Action]::変換した、Tuple_tpで[::type]を呼び出すクラステンプレート
	//[T_Tuple]::変数するTuple型
	//[t_Start_Point]::変換したTuple_tpの初期選択の場所
	// 
	//using
	//[Return_not_p]::[tuple_tp,vp]から[tuple_t,v]に変換し[T_Action]を呼び出した際、
	//	選択位置を戻す処理をスキップする
	//[Return_p]::[tuple_t,v]から[tuple_tp,vp]に変換し[T_Action]を呼び出した際、
	//	選択位置を外す処理をスキップする
	// 
	//補足
	//変数に失敗した場合、未処理の[T_Tuple]がそのまま返される
	template<template<class...>class T_Action, class T_Tuple, size_t t_Start_Point = S_Parameter<T_Tuple>::head_size>
	using S_Tuple_tp_Change_Action = S_Tuple_Type_Change_Action_Helper<true, true, T_Action, T_Tuple, t_Start_Point>;

	//仕様
	//[T_Tuple]を[tuple_t]に変換し[T_Action]の[::type]を呼び出し
	//　結果を[tuple_t]から[T_Tuple]と同タイプのTupleに変換し返す。
	//
	//テンプレート
	//[T_Action]::変換した、Tuple_tで[::type]を呼び出すクラステンプレート
	//[T_Tuple]::変数するTuple型
	// 
	//using
	//[Return_not_p]::[tuple_tp,vp]から[tuple_t,v]に変換し[T_Action]を呼び出した際、
	//	選択位置を戻す処理をスキップする
	//[Return_p]::[tuple_t,v]から[tuple_tp,vp]に変換し[T_Action]を呼び出した際、
	//	選択位置を外す処理をスキップする
	// 
	//補足
	//変数に失敗した場合、未処理の[T_Tuple]がそのまま返される
	template<template<class...>class T_Action, class T_Tuple>
	using S_Tuple_t_Change_Action = S_Tuple_Type_Change_Action_Helper<false, true, T_Action, T_Tuple>;

	//仕様
	//[T_Tuple]を[tuple_vp]に変換し[T_Action]の[::type]を呼び出し
	//　結果を[tuple_vp]から[T_Tuple]と同タイプのTupleに変換し返す。
	//
	//テンプレート
	//[T_Action]::変換した、Tuple_vpで[::type]を呼び出すクラステンプレート
	//[T_Tuple]::変数するTuple型
	//[t_Start_Point]::変換したTuple_vpの初期選択の場所
	// 
	//using
	//[Return_not_p]::[tuple_tp,vp]から[tuple_t,v]に変換し[T_Action]を呼び出した際、
	//	選択位置を戻す処理をスキップする
	//[Return_p]::[tuple_t,v]から[tuple_tp,vp]に変換し[T_Action]を呼び出した際、
	//	選択位置を外す処理をスキップする
	// 
	//補足
	//変数に失敗した場合、未処理の[T_Tuple]がそのまま返される
	template<template<class...>class T_Action, class T_Tuple,size_t t_Start_Point = S_Parameter<T_Tuple>::head_size>
	using S_Tuple_vp_Change_Action = S_Tuple_Type_Change_Action_Helper<true, false, T_Action, T_Tuple, t_Start_Point>;

	//仕様
	//[T_Tuple]を[tuple_v]に変換し[T_Action]の[::type]を呼び出し
	//　結果を[tuple_v]から[T_Tuple]と同タイプのTupleに変換し返す。
	//
	//テンプレート
	//[T_Action]::変換した、Tuple_vで[::type]を呼び出すクラステンプレート
	//[T_Tuple]::変数するTuple型
	//[t_Start_Point]::変換したTuple_vの初期選択の場所
	// 	
	//using
	//[Return_not_p]::[tuple_tp,vp]から[tuple_t,v]に変換し[T_Action]を呼び出した際、
	//	選択位置を戻す処理をスキップする
	//[Return_p]::[tuple_t,v]から[tuple_tp,vp]に変換し[T_Action]を呼び出した際、
	//	選択位置を外す処理をスキップする
	// 
	//補足
	//変数に失敗した場合、未処理の[T_Tuple]がそのまま返される
	template<template<class...>class T_Action, class T_Tuple>
	using S_Tuple_v_Change_Action = S_Tuple_Type_Change_Action_Helper<false, false, T_Action, T_Tuple>;

	template<class T_Tuple_v, String t_operator, auto number>
	struct I_Template_Calculate;

	template<template<class...>class T_Outer_class, class ...T_Types>
	struct I_Move_Template;

	template<size_t N>
	struct I_index_sequence;

	template<size_t N_1, size_t N_2>
	struct I_range_index_sequence;

	template<template<class...>class TT_Action, class T_Tuple, class ...T_Extra>
	struct I_Elements_Action;

	template<class T_Fn, class ...T_Set_Types>
	struct I_Apply_Action;

	//仕様
	//要素に型[T]を[N]個持つ、[tuple_t]を作る
	template<class T, size_t N>
	struct I_Repeat_Multiple;

	//仕様
	//指定した回数までタプル内の要素を展開する
	//
	// テンプレート
	//[T_Tuple]::展開する[Tuple_t]の型
	//[t_expand_lelve]::展開する階層の上限
	template<class T_Tuple, size_t t_expand_lelve = 1>
	struct I_Expand;

	//仕様
	//圧縮されているTupleを示す
	template<class _Ty1, size_t N>
	struct tuple_zip;

	//仕様
	//パラメータパック[Ts...]から連続する型を{tuple_zip< T, N >}に圧縮する
	template<class ...Ts>
	struct I_Zip;

	//仕様
	//タプル内の要素から連続する型を{tuple_zip< T, N >}に圧縮する
	template<class T_Tuple>
	struct I_Zip_Tuple;

}