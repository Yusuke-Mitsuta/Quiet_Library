#pragma once

#include"Tuple_Declare.h"
#include"If_Type.h"

namespace N_Tuple
{

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
	struct S_Tuple_Type_Change_Action_Helper
	{
	private:

		template<class T_Tuple, class T_Start_Point_Judge = std::bool_constant<
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
			S_Tuple_Type_Change_Action<t_Action_Type_Tuple_p, t_Action_Type_Tuple_t, (t_Action_break^ is_Tuple_not_p<T_Tuple>), I_Tuple_Start_Point_Set, T_Tuple>;


		

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