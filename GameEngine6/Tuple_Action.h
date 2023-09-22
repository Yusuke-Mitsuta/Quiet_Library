#pragma once

#include"Tuple_Declare.h"
#include"If_Type.h"



namespace N_Tuple
{

	//�d�l
	//[T_Tuple]���w�肵���^�ɕό`���A[T_Action]�̃e���v���[�g�ɕό`��̌^��[T_Types...]�����킹�āA[T_Action<...>::type]�����s����
	//���s��̌^��T_Tuple�̌^�̏����ɖ߂�
	//
	//�e���v���[�g
	//[t_Action_Type_Tuple_p]::[T_Action]�����s���鎞�ɗv������Tuple���|�C���g������[Tuple_tp,Tuple_vp]�ł��邩�H
	//[t_Action_Type_Tuple_t]::[T_Action]�����s���鎞�ɗv������Tuple���^���Ǘ�[Tuple_t,Tuple_tp]�ł��邩�H
	//[t_Action_break]::[T_Action]�����s��A�|�C���g�����̏�Ԃ��ێ����邩�H
	//[T_Action]::[T_Action< ... >::type]�Ŏ��s����^
	//[T_Tuple]::�����ɉ����ĕύX����Tuple
	//[T_Types...]::[T_Action]�Ŏ��s���A�ύX���Tuple�̌��ɑ�����^
	//
	//�⑫
	//[t_Action_break == true],[T_Tuple=Tuple_vp],�v������^[Tuple_t]�̎��A���Ă���Tuple�̌^��[Tuple_v]�ɂȂ�
	//
	//����
	//[T_Action]�̗v������^�ɔ�n�e���v���[�g�͊܂܂Ȃ���
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