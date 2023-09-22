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
	//[t_Action_Type_Tuple_p]::[T_Action]を実行する時に要求するTupleがポイントを所持[Tuple_tp,Tuple_vp]であるか？
	//[t_Action_Type_Tuple_t]::[T_Action]を実行する時に要求するTupleが型を管理[Tuple_t,Tuple_tp]であるか？
	//[t_Action_break]::[T_Action]を実行後、ポイント所持の状態を維持するか？
	//[T_Action]::[T_Action< ... >::type]で実行する型
	//[T_Tuple]::条件に応じて変更するTuple
	//[T_Types...]::[T_Action]で実行時、変更後のTupleの後ろに続ける型
	//
	//補足
	//[t_Action_break == true],[T_Tuple=Tuple_vp],要求する型[Tuple_t]の時帰ってくるTupleの型は[Tuple_v]になる
	//
	//注意
	//[T_Action]の要求する型に非系テンプレートは含まない事
	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Tuple, class ...T_Types>
	struct S_Action_Tuple
	{
		using type = T_Action<T_Tuple>::type;
	};

	template<bool t_Action_Type_Tuple_p, template<class...>class T_Action, is_Tuple_t T_Tuple_t, bool t_Action_break, class ...T_Types>
	struct S_Action_Tuple<t_Action_Type_Tuple_p, false, t_Action_break, T_Action, T_Tuple_t, T_Types...>
	{
		using type = U_Tuple_v_To_t<typename S_Action_Tuple<t_Action_Type_Tuple_p, false, t_Action_break, T_Action,
			U_Tuple_t_To_v<T_Tuple_t>, T_Types...>::type>;
	};

	template<bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, is_Tuple_p T_Tuple_p, class ...T_Types >
	struct S_Action_Tuple<false, t_Action_Type_Tuple_t, t_Action_break, T_Action, T_Tuple_p, T_Types...>
	{
		using action_return = typename S_Action_Tuple<false, t_Action_Type_Tuple_t, t_Action_break, T_Action, U_Remove_p<T_Tuple_p>, T_Types...>::type;

		using create_p = U_if_t1<U_Select<S_Parameter<T_Tuple_p>::Size_Head, action_return>, U_Create_p<action_return>,
			(S_Parameter<T_Tuple_p>::Size == S_Parameter<action_return>::Size)>;

		using type = U_if_t1<action_return, create_p, t_Action_break>;
	};

	template<bool t_Action_Type_Tuple_p, bool t_Action_break, template<class...>class T_Action, is_Tuple_v T_Tuple_v, class ...T_Types >
	struct S_Action_Tuple<t_Action_Type_Tuple_p, true, t_Action_break, T_Action, T_Tuple_v, T_Types... >
	{
		using type = U_Tuple_t_To_v<typename S_Action_Tuple<t_Action_Type_Tuple_p, true, t_Action_break, T_Action, U_Tuple_v_To_t<T_Tuple_v>, T_Types...>::type>;
	};

	template< bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, is_Tuple_not_p T_Tuple_not_p, class ...T_Types >
	struct S_Action_Tuple<true, t_Action_Type_Tuple_t, t_Action_break, T_Action, T_Tuple_not_p, T_Types... >
	{
		using type = U_Remove_p<typename S_Action_Tuple<true, t_Action_Type_Tuple_t, t_Action_break, T_Action, U_Create_p<T_Tuple_not_p>, T_Types...>::type>;
	};


	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t,int Select_Point,template<class...>class T_Action, class T_Tuple, class ...T_Types>
	struct S_Action_Tuple_Helper
	{
	private:

		template<class T_Tuple,class T_bool=std::bool_constant<S_Parameter<T_Tuple>::Size_Head != Select_Point>>
		struct S_Action_Tuple_Select_Point
		{
			using type = U_Select<S_Parameter<T_Tuple>::Size_Head,typename T_Action<U_Select<Select_Point, T_Tuple>, T_Types...>::type>;
		};

		template<class T_Tuple>
		struct S_Action_Tuple_Select_Point<T_Tuple,std::false_type>
		{
			using type =T_Action<T_Tuple, T_Types...>::type;
		};

		template<bool t_Action_break,template<class...>class T_Action_Fg>
		using Return_Tuple = S_Action_Tuple<t_Action_Type_Tuple_p, t_Action_Type_Tuple_t, (t_Action_break^
			is_Tuple_not_p<T_Tuple>), T_Action, T_Tuple, T_Types...>;

		template<bool t_Action_break, int Select_Point = t_Action_Type_Tuple_p ? Select_Point : -1>
		struct S_Return_Tuple 
		{
			using type = Return_Tuple<t_Action_break,S_Action_Tuple_Select_Point>::type;
		};
			
		template<bool t_Action_break>
		struct S_Return_Tuple<t_Action_break,-1>
		{
			using type = Return_Tuple<t_Action_break,T_Action>::type;
		};

	public:
		using Return_not_p = S_Return_Tuple<true>::type;

		using Return_p = S_Return_Tuple<false>::type;

		using type = S_Return_Tuple<is_Tuple_not_p<T_Tuple>>::type;
		
	};



}