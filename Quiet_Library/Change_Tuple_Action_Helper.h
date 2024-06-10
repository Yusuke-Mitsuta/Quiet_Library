#pragma once

#include"Tuple_Class_Declare.h"

namespace quiet::N_Tuple::N_Tuple_Convert_Action
{

	struct I_Tuple_Convert_Action_Helper
	{
	
			
		struct L_Target;

		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t>
		struct L_Option;

		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t,
			bool t_Return_p_Convert_Skip,
			bool t_Return_tv_Convert_Skip>
		struct L_StartPoint;

	};

	template<bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip>
	struct I_Tuple_Convert_Action_Helper::L_StartPoint
	{

		struct Default
		{

		};

		struct Set_StartPoint
		{

		};

	};

	template<bool t_is_Target_Tuple_p,bool t_is_Target_Tuple_t>
	struct I_Tuple_Convert_Action_Helper::L_Option
	{
	private:
		template<bool t_Return_p_Convert_Skip,
			bool t_Return_tv_Convert_Skip>
		using StartPoint = L_StartPoint<
			t_is_Target_Tuple_p, 
			t_is_Target_Tuple_t, 
			t_Return_p_Convert_Skip,
			t_Return_tv_Convert_Skip>;

	public:

		struct Default:
			StartPoint<false,false>
		{

		};

		struct Return_p_Convert_Skip:
			StartPoint<true,false>
		{

		};

		struct Return_tv_Convert_Skip:
			StartPoint<false,true>
		{

		};

		
		struct Return_Convert_Skip:
			StartPoint<true,true>
		{
		};
		
	};


	struct I_Tuple_Convert_Action_Helper::L_Target
	{
	private:

		template<bool t_is_Target_Tuple_p,
			bool t_is_Target_Tuple_t>
		using Option = L_Option<t_is_Target_Tuple_p, t_is_Target_Tuple_t>;

	public:

		struct Target_Tuple_tp :
			Option<true,true>
		{

		};

		struct Target_Tuple_vp :
			Option<true,false>
		{

		};

		struct Target_Tuple_t :
			Option<false,true>
		{

		};

		struct Target_Tuple_v :
			Option<false,false>
		{

		};

	};
}

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
		size_t t_Start_Point>
	struct I_Change_Tuple_Action_Helper
	{
	private:

		template<bool t_Return_p_Convert_Skip_Fg, bool t_Return_tv_Convert_Skip_Fg, bool t_Return_p_Back_Fg >
		using Return_Convert_Skip_Base =
			I_Change_Tuple_Action<
			T_Action,
			T_Convert_Tuple,
			t_is_Target_Tuple_p,
			t_is_Target_Tuple_t,
			t_Start_Point,
			t_Return_p_Convert_Skip_Fg,
			t_Return_tv_Convert_Skip_Fg,
			t_Return_p_Back_Fg>::type;

	public:

		using type = Return_Convert_Skip_Base<false, false, false>;

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