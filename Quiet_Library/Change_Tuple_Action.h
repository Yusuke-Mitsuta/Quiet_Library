/*!
 * Tuple_Type_Change_Action.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Type_Change_Action_Helper.h"

#include"Template_Class_Change.h"
#include"SwapType.h"

namespace quiet::N_Tuple
{

	//仕様
	//[T_Tuple_Data]を指定した型に変形し、[T_Action]のテンプレートに変形後の型と[T_Leftover_Types...]を合わせて、[T_Action<...>::type]を実行する
	//実行後の型をT_Tupleの型の条件に戻す
	//
	//テンプレート
	//[t_Action_Type_Tuple_p]::[T_Action]を実行する時に要求するTupleがポイントを所持[tuple_tp,tuple_vp]であるか？
	//[t_Action_Type_Tuple_t]::[T_Action]を実行する時に要求するTupleが型を管理[tuple_t,tuple_tp]であるか？
	//[t_Action_break]::[T_Action]を実行後、ポイント所持の状態を維持するか？
	//[T_Action]::[T_Action< ... >::type]で実行する型
	//[T_Tuple_Data]::条件に応じて変更するTuple
	//[T_Leftover_Types...]::[T_Action]で実行時、変更後のTupleの後ろに続ける型
	//
	//補足
	//[t_Action_break == true],[T_Tuple_Data=tuple_vp],要求する型[tuple_t]の時帰ってくるTupleの型は[tuple_v]になる
	//
	//型の変化は[2つ進む or 1つ戻る]のどちらかで変化をさせる
	//[tp → t → v → vp → tp]
	//
	//注意
	//[T_Action]の要求する型に非系テンプレートは含まない事
	template<template<class...>class T_Action, 
		class T_Convert_Tuple,
		bool t_is_Target_Tuple_p, 
		bool t_is_Target_Tuple_t,
		size_t t_Start_Point,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip, 
		bool t_Return_p_Back>
	struct I_Change_Tuple_Action
	{
	private:

		template<class T_Action_Tuple, class T_Start_Point = integral_constant<t_Start_Point>>
		struct S_Start_Point_Set
		{
			using type = T_Action<T_Action_Tuple>;
		};

		template<class T_Action_Tuple, class T_Start_Point>
			requires requires
		{
			requires is_Tuple_p<T_Action_Tuple>;
			requires T_Action_Tuple::size > T_Start_Point::value;
			requires T_Action_Tuple::head_size != T_Start_Point::value;
		}
		struct S_Start_Point_Set<T_Action_Tuple, T_Start_Point>
		{
			using type = S_Start_Point_Set<U_Select<T_Start_Point::value, T_Action_Tuple>>::type;
		};

		using action = S_Start_Point_Set<U_Change_Tuple<T_Convert_Tuple, t_is_Target_Tuple_p, t_is_Target_Tuple_t>>::type;


		template<class T = T_Convert_Tuple>
		struct S_Result
		{
			using result = U_Change_Tuple<action, 
				((is_Tuple_p<T_Convert_Tuple> && !t_Return_p_Convert_Skip) ||
				(t_is_Target_Tuple_p && t_Return_p_Convert_Skip)),
				((is_Tuple_t<T_Convert_Tuple> && !t_Return_tv_Convert_Skip) ||
				(t_is_Target_Tuple_t && t_Return_tv_Convert_Skip))>::type;

			template<class T_Result_Tuple = result>
			struct S_Create_p
			{
				using type = T_Result_Tuple;
			};


			template<class T_Result_Tuple>
				requires requires
			{
				requires t_Return_p_Back;
				requires (T_Convert_Tuple::head_size != t_Start_Point);
				requires (T_Convert_Tuple::head_size >= T_Result_Tuple::size);
			}
			struct S_Create_p<T_Result_Tuple>
			{
				using type = U_Select<T_Convert_Tuple::head_size, T_Result_Tuple>;
			};

			using type = S_Create_p<>::type;

		};

		template<class ...Ts,template<class...>class T_Outer>
		struct S_Result<T_Outer<Ts...>>
		{
			using type = N_Template::U_Class_Change<action, T_Outer>;
		};
		
		template<bool t_Return_p_Convert_Skip_Fg, bool t_Return_tv_Convert_Skip_Fg, bool t_Return_p_Back_Fg >
		using Return_Convert_Skip_Base = 
			I_Change_Tuple_Action<T_Action,
			T_Convert_Tuple, 
			t_is_Target_Tuple_p, 
			t_is_Target_Tuple_t,
			t_Start_Point, 
			t_Return_p_Convert_Skip_Fg, 
			t_Return_tv_Convert_Skip_Fg,
			t_Return_p_Back_Fg>::type;

	public:

		using type = S_Result<>::type;


		//仕様
		//[T_Action<...>::type]実行後のpointが元の状態への変換をスキップする
		using Return_p_Convert_Skip = Return_Convert_Skip_Base<true, false, false>;

		//仕様
		//[T_Action<...>::type]実行後の元の状態への[tuple_t→v],[tuple_v→t]変換をスキップする
		using Return_tv_Convert_Skip = Return_Convert_Skip_Base<false, true, false>;

		//仕様
		//[T_Action<...>::type]実行後の元の状態への変換をスキップする
		using Return_Convert_Skip = Return_Convert_Skip_Base<true, true, false>;

		//仕様
		//[t_Start_Point]にて開始ポイントを変更した際、元の位置へのポイント移動をスキップする
		using Return_Point_Back = Return_Convert_Skip_Base<false, false, true>;
	};

}