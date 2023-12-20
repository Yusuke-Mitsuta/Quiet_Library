#pragma once

#include"Tuple_Declare.h"
#include"If_Type.h"



namespace N_Tuple
{

	//仕様
	//[T_Tuple]を指定した型に変形し、[T_Action]のテンプレートに変形後の型と[T_Types...]を合わせて、[T_Action<...>::type]を実行する
	//実行後の型をT_Tupleの型の条件に戻す
	//
	//テンプレート
	//[t_Action_Type_Tuple_p]::[T_Action]を実行する時に要求するTupleがポイントを所持[tuple_tp,tuple_vp]であるか？
	//[t_Action_Type_Tuple_t]::[T_Action]を実行する時に要求するTupleが型を管理[tuple_t,tuple_tp]であるか？
	//[t_Action_break]::[T_Action]を実行後、ポイント所持の状態を維持するか？
	//[T_Action]::[T_Action< ... >::type]で実行する型
	//[T_Tuple]::条件に応じて変更するTuple
	//[T_Types...]::[T_Action]で実行時、変更後のTupleの後ろに続ける型
	//
	//補足
	//[t_Action_break == true],[T_Tuple=tuple_vp],要求する型[tuple_t]の時帰ってくるTupleの型は[tuple_v]になる
	//
	//型の変化は[2つ進む or 1つ戻る]のどちらかで変化をさせる
	//[tp → t → v → vp → tp]
	//
	//注意
	//[T_Action]の要求する型に非系テンプレートは含まない事
	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
	struct S_Action_Tuple
	{
		using type = T_Action<T_Tuple>::type;
	};


	//t→v
	//vp←tp
	template<bool t_Action_Type_Tuple_p, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
		requires (same_as_tuple_t<T_Tuple>)||(same_as_tuple_tp<T_Tuple> && t_Action_Type_Tuple_p)
	struct S_Action_Tuple<t_Action_Type_Tuple_p,false,t_Action_break,T_Action,T_Tuple>
	{
		using return_type= S_Action_Tuple<t_Action_Type_Tuple_p, false, t_Action_break, T_Action, U_Tuple_t_To_v<T_Tuple>>::type;

		using type = U_Tuple_v_To_t<return_type>;
	};

	//v→vp
	//tp←t
	template<bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
		requires (same_as_tuple_v<T_Tuple>) || (same_as_tuple_t<T_Tuple> && t_Action_Type_Tuple_t)
	struct S_Action_Tuple<true, t_Action_Type_Tuple_t, t_Action_break, T_Action, T_Tuple>
	{
		using return_type = S_Action_Tuple<true,t_Action_Type_Tuple_t ,t_Action_break, T_Action,U_Create_p<T_Tuple>>::type;


		template<bool t_Action_break = t_Action_break>
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
	template<bool t_Action_Type_Tuple_p, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
		requires (same_as_tuple_vp<T_Tuple>) || (same_as_tuple_v<T_Tuple> && !t_Action_Type_Tuple_p)
	struct S_Action_Tuple<t_Action_Type_Tuple_p, true,t_Action_break, T_Action, T_Tuple>
	{
		using return_type = S_Action_Tuple<t_Action_Type_Tuple_p, true, t_Action_break, T_Action, U_Tuple_v_To_t<T_Tuple>>::type;

		using type = U_Tuple_t_To_v<return_type>;

	};

	//tp→t
	//v←vp
	template<bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
		requires (same_as_tuple_tp<T_Tuple>) || (same_as_tuple_v<T_Tuple> && !t_Action_Type_Tuple_t)
	struct S_Action_Tuple<false,t_Action_Type_Tuple_t, t_Action_break, T_Action, T_Tuple>
	{
		using return_type = S_Action_Tuple<false,t_Action_Type_Tuple_t, t_Action_break, T_Action, U_Remove_p<T_Tuple>>::type;

		template<bool t_Action_break=t_Action_break>
		struct S_action_break
		{
			using type = return_type;
		};

		template<>
		struct S_action_break<false>
		{
			static constexpr size_t prev_head_size = S_Parameter<T_Tuple>::head_size;
			using create_p = U_Create_p<return_type>;
			using type = U_if_t1<U_Select<prev_head_size,create_p>,create_p,(prev_head_size < S_Parameter<return_type>::size)>;
		};

		using type = S_action_break<>::type;

	};

	//仕様
	//[T_Tuple]を[t_Action_Type_Tuple_p,t_Action_Type_Tuple_t]の値によって変換し
	// [T_Action]の[::type]を呼び出す、
	// 結果から[T_Tuple]と同タイプのTupleに変換し返す。
	//
	//テンプレート
	//[t_Action_Type_Tuple_p]::要求するTupleが[tuple_tp,vp]なら[true]にする
	//[t_Action_Type_Tuple_t]::要求するTupleが[tuple_t,tp]なら[true]にする
	//[T_Action]::変換した型で[::type]を呼び出すクラステンプレート
	//[T_Tuple]::変数するTuple型
	//[t_Start_Point]::変換した[tuple_tp,vp]の初期選択の場所
	// 
	//using
	//[Return_not_p]::[tuple_tp,vp]から[tuple_t,v]に変換し[T_Action]を呼び出した際、
	//	選択位置を戻す処理をスキップする
	//[Return_p]::[tuple_t,v]から[tuple_tp,vp]に変換し[T_Action]を呼び出した際、
	//	選択位置を外す処理をスキップする
	// 
	//補足
	//変数に失敗した場合、未処理の[T_Tuple]がそのまま返される
	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, template<class...>class T_Action, class T_Tuple, size_t t_Start_Point>
	struct S_Action_Tuple_Helper
	{
	private:

		template<class T_Tuple,class T_Start_Point_Judge=std::bool_constant<
			((t_Start_Point < S_Parameter<T_Tuple>::size) &&
			(t_Start_Point != S_Parameter<T_Tuple>::head_size))>>
		struct I_Tuple_Start_Point_Set
		{
			using type = T_Action<T_Tuple>::type;

		};

		template<is_Tuple_p T_Tuple>
		struct I_Tuple_Start_Point_Set<T_Tuple, std::true_type>
		{
			using return_type = T_Action<U_Select<t_Start_Point, T_Tuple>>::type;

			template<bool t_not_size_change_Judge = (S_Parameter<T_Tuple>::head_size < S_Parameter<return_type>::size) > 
			struct S_Tuple_Start_Point_Set
			{
				using type = U_Select<S_Parameter<T_Tuple>::head_size, return_type>;
			};

			template<>
			struct S_Tuple_Start_Point_Set<false>
			{
				using type = return_type;
			};

			using type = typename S_Tuple_Start_Point_Set<>::type;
		};

		template<bool t_Action_break>
		using Return_Tuple =
			S_Action_Tuple<t_Action_Type_Tuple_p, t_Action_Type_Tuple_t, (t_Action_break^ is_Tuple_not_p<T_Tuple>), I_Tuple_Start_Point_Set, T_Tuple>;

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
		//[T_Tuple]を[tuple_vp]に変換し[T_Action]の[::type]を呼び出し
		//　結果を[tuple_vp]から[T_Tuple]と同タイプのTupleに変換し返す。
		using type = Return_Tuple<is_Tuple_not_p<T_Tuple>>::type;

	};



}