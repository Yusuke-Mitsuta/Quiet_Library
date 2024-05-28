/*!
 * Tuple_Type_Change_Action_Helper.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"SwapType.h"

namespace quiet::N_Tuple
{

	//仕様
	//[T_Tuple_Data]を[t_Action_Type_Tuple_p,t_Action_Type_Tuple_t]の値によって変換し
	// [T_Action]の[::type]を呼び出す、
	// 結果から[T_Tuple_Data]と同タイプのTupleに変換し返す。
	//
	//テンプレート
	//[t_Action_Type_Tuple_p]::要求するTupleが[tuple_tp,vp]なら[true]にする
	//[t_Action_Type_Tuple_t]::要求するTupleが[tuple_t,tp]なら[true]にする
	//[T_Action]::変換した型で[::type]を呼び出すクラステンプレート
	//[T_Tuple_Data]::変数するTuple型
	//[t_Start_Point]::変換した[tuple_tp,vp]の初期選択の場所
	// 
	//using
	//[Return_not_p]::[tuple_tp,vp]から[tuple_t,v]に変換し[T_Action]を呼び出した際、
	//	選択位置を戻す処理をスキップする
	//[Return_p]::[tuple_t,v]から[tuple_tp,vp]に変換し[T_Action]を呼び出した際、
	//	選択位置を外す処理をスキップする
	// 
	//補足
	//変数に失敗した場合、未処理の[T_Tuple_Data]がそのまま返される
	template<template<class...>class T_Action, class T_Convert_Tuple, bool t_is_Target_Tuple_p, bool t_is_Target_Tuple_t, size_t t_Start_Point>
	struct I_Change_Tuple_Action_Helper
	{
	private:


		template<bool t_Action_break>
		using Return_Tuple =
			I_Change_Tuple_Action<T_Convert_Tuple,t_Action_Type_Tuple_p, t_Action_Type_Tuple_t,
			(t_Action_break^ is_Tuple_not_p<T_Convert_Tuple>), I_Tuple_Start_Point_Set>;

	public:

		//仕様
		//[tuple_tp,vp]から[tuple_t,v]に変換し[T_Action]を呼び出した際、
		//	選択位置を戻す処理をスキップする
		using Return_not_p = Return_Tuple<true>::type;

		//仕様
		//[tuple_t, v] から[tuple_tp, vp]に変換し[T_Action]を呼び出した際、
		//	選択位置を外す処理をスキップする
		using Return_p = Return_Tuple<false>::type;

		//仕様
		//[T_Tuple_Data]を[tuple_vp]に変換し[T_Action]の[::type]を呼び出し
		//　結果を[tuple_vp]から[T_Tuple_Data]と同タイプのTupleに変換し返す。
		using type = Return_Tuple<is_Tuple_not_p<T_Convert_Tuple>>::type;

	};


}