/*!
 * Tuple_Type_Change_Action.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

//#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Type_Change_Action_Helper.h"
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
	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Convert_Tuple>
	struct S_Tuple_Type_Change_Action
	{
		using type = T_Action<T_Convert_Tuple>::type;
	};

	//t→v
	//vp←tp
	template<bool t_Action_Type_Tuple_p, bool t_Action_break, template<class...>class T_Action, class T_Convert_Tuple>
		requires requires
	{
		requires (same_as_tuple_t<T_Convert_Tuple>) || (same_as_tuple_tp<T_Convert_Tuple> && t_Action_Type_Tuple_p);
		//requires T_Tuple_Data::name == N_Constexpr::String{ "" };
	}
	struct S_Tuple_Type_Change_Action<t_Action_Type_Tuple_p,false,t_Action_break,T_Action,T_Convert_Tuple>
	{
		using return_type= S_Tuple_Type_Change_Action<t_Action_Type_Tuple_p, false, t_Action_break, T_Action, U_Tuple_t_To_v<T_Convert_Tuple>>::type;

		using type = U_Tuple_v_To_t<return_type>;
	};

	//v→vp
	//tp←t
	template<bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Convert_Tuple>
		requires requires
	{
		requires (same_as_tuple_v<T_Convert_Tuple>) || (same_as_tuple_t<T_Convert_Tuple> && t_Action_Type_Tuple_t);
		//requires T_Tuple_Data::name == N_Constexpr::String{ "" };
	}
	struct S_Tuple_Type_Change_Action<true, t_Action_Type_Tuple_t, t_Action_break, T_Action, T_Convert_Tuple>
	{
		using return_type = S_Tuple_Type_Change_Action<true,t_Action_Type_Tuple_t ,t_Action_break, T_Action,U_Create_p<T_Convert_Tuple>>::type;


		template<bool t_Action_break_fg = t_Action_break>
		struct S_action_break
		{
			using type = return_type;
		};
		
		template<>
		struct S_action_break<false>
		{
			using type =U_Remove_p<return_type>;
		};

		using type = S_action_break<>::type;

	};

	//vp→tp
	//t←v
	template<bool t_Action_Type_Tuple_p, bool t_Action_break, template<class...>class T_Action, class T_Convert_Tuple>
		requires requires
	{
		requires (same_as_tuple_vp<T_Convert_Tuple>) || (same_as_tuple_v<T_Convert_Tuple> && !t_Action_Type_Tuple_p);
		//requires T_Tuple_Data::name == N_Constexpr::String{ "" };
	}
	struct S_Tuple_Type_Change_Action<t_Action_Type_Tuple_p, true,t_Action_break, T_Action, T_Convert_Tuple>
	{
		using return_type = S_Tuple_Type_Change_Action<t_Action_Type_Tuple_p, true, t_Action_break, T_Action, U_Tuple_v_To_t<T_Convert_Tuple>>::type;

		using type = U_Tuple_t_To_v<return_type>;

	};

	//tp→t
	//v←vp
	template<bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Convert_Tuple>
		requires requires
	{
		requires (same_as_tuple_tp<T_Convert_Tuple>) || (same_as_tuple_v<T_Convert_Tuple> && !t_Action_Type_Tuple_t);
		//requires T_Tuple_Data::name == N_Constexpr::String{""};
	}
	struct S_Tuple_Type_Change_Action<false,t_Action_Type_Tuple_t, t_Action_break, T_Action, T_Convert_Tuple>
	{
		using return_type = S_Tuple_Type_Change_Action<false,t_Action_Type_Tuple_t, t_Action_break, T_Action, U_Remove_p<T_Convert_Tuple>>::type;

		template<bool t_Action_break_fg=t_Action_break>
		struct S_action_break
		{
			using type = return_type;
		};

		template<>
		struct S_action_break<false>
		{
			static constexpr size_t prev_head_size = S_Parameter<T_Convert_Tuple>::head_size;
			using create_p = U_Create_p<return_type>;
			using type = U_if_t1<U_Select<prev_head_size,create_p>,create_p,(prev_head_size < S_Parameter<return_type>::size)>;
		};

		using type = S_action_break<>::type;

	};


}