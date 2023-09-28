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
	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Tuple, class ...T_Types>
	struct S_Action_Tuple
	{
		using type = T_Action<T_Tuple>::type;
	};

	template<bool t_Action_Type_Tuple_p, template<class...>class T_Action, is_Tuple_t T_Tuple_t, bool t_Action_break, class ...T_Types>
		requires (is_Tuple_not_p<T_Tuple_t> || t_Action_Type_Tuple_p)
	struct S_Action_Tuple<t_Action_Type_Tuple_p, false, t_Action_break, T_Action, T_Tuple_t, T_Types...>
	{
		using type = U_Tuple_v_To_t<typename S_Action_Tuple<t_Action_Type_Tuple_p, false, t_Action_break,
			T_Action, U_Tuple_t_To_v<T_Tuple_t>, T_Types...>::type>;
	};

	template<bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, is_Tuple_p T_Tuple_p, class ...T_Types >
		requires (is_Tuple_t<T_Tuple_p> || (!t_Action_Type_Tuple_t))
	struct S_Action_Tuple<false, t_Action_Type_Tuple_t, t_Action_break, T_Action, T_Tuple_p, T_Types...>
	{
	private:
		using action_return = typename S_Action_Tuple<false, t_Action_Type_Tuple_t, t_Action_break, T_Action, U_Remove_p<T_Tuple_p>, T_Types...>::type;

		using create_p = U_if_t1<U_Select<S_Parameter<T_Tuple_p>::Size_Head, action_return>, U_Create_p<action_return>,
			(S_Parameter<T_Tuple_p>::Size == S_Parameter<action_return>::Size)>;
	public:
		using type = U_if_t1<action_return, create_p, t_Action_break>;
	};

	template<bool t_Action_Type_Tuple_p, bool t_Action_break, template<class...>class T_Action, is_Tuple_v T_Tuple_v, class ...T_Types>
		requires (is_Tuple_p<T_Tuple_v> || (!t_Action_Type_Tuple_p))
	struct S_Action_Tuple<t_Action_Type_Tuple_p, true, t_Action_break, T_Action, T_Tuple_v, T_Types... >
	{
		using type = U_Tuple_t_To_v<typename S_Action_Tuple<t_Action_Type_Tuple_p, true, t_Action_break, T_Action, U_Tuple_v_To_t<T_Tuple_v>, T_Types...>::type>;
	};

	template< bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, is_Tuple_not_p T_Tuple_not_p, class ...T_Types>
		requires (is_Tuple_v<T_Tuple_not_p> || t_Action_Type_Tuple_t)
	struct S_Action_Tuple<true, t_Action_Type_Tuple_t, t_Action_break, T_Action, T_Tuple_not_p, T_Types... >
	{
	private:
		using action_return = typename S_Action_Tuple<true, t_Action_Type_Tuple_t, t_Action_break, T_Action, U_Create_p<T_Tuple_not_p>, T_Types...>::type;

		using remove_p = U_Remove_p<action_return>;
	public:
		using type = U_if_t1< action_return, remove_p, t_Action_break>;
	};


	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, template<class...>class T_Action, class T_Tuple, size_t t_Start_Point>
	struct S_Action_Tuple_Helper
	{
	private:

		template<class T_Tuple,class T_Start_Point_Judge=std::bool_constant<(t_Start_Point != S_Parameter<T_Tuple>::Size_Head)>>
		struct I_Tuple_Start_Point_Set
		{
			using return_type = T_Action<U_Select<t_Start_Point, T_Tuple>>::type;

			template<bool t_not_size_change_Judge =(S_Parameter<return_type>::Size == S_Parameter<T_Tuple>::Size)>
			struct S_Tuple_Start_Point_Set
			{
				using type= U_Select<S_Parameter<T_Tuple>::Size_Head,return_type>::type;
			};

			template<>
			struct S_Tuple_Start_Point_Set<false>
			{
				using type = return_type;
			};

			using type =typename S_Tuple_Start_Point_Set<>::type;

		};

		template<class T_Tuple>
		struct I_Tuple_Start_Point_Set<T_Tuple, std::false_type>
		{
			using type = T_Action<T_Tuple>::type;
		};

		template<bool t_Action_break>
		using Return_Tuple = 
			S_Action_Tuple<t_Action_Type_Tuple_p, t_Action_Type_Tuple_t, (t_Action_break^ is_Tuple_not_p<T_Tuple>),I_Tuple_Start_Point_Set, T_Tuple>;

	public:

		using Return_not_p = Return_Tuple<true>::type;

		using Return_p = Return_Tuple<false>::type;

		using type = Return_Tuple<is_Tuple_not_p<T_Tuple>>::type;

	};



}