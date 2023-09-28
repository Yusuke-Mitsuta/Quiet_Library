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
	//[t_Action_Type_Tuple_p]::[T_Action]�����s���鎞�ɗv������Tuple���|�C���g������[tuple_tp,tuple_vp]�ł��邩�H
	//[t_Action_Type_Tuple_t]::[T_Action]�����s���鎞�ɗv������Tuple���^���Ǘ�[tuple_t,tuple_tp]�ł��邩�H
	//[t_Action_break]::[T_Action]�����s��A�|�C���g�����̏�Ԃ��ێ����邩�H
	//[T_Action]::[T_Action< ... >::type]�Ŏ��s����^
	//[T_Tuple]::�����ɉ����ĕύX����Tuple
	//[T_Types...]::[T_Action]�Ŏ��s���A�ύX���Tuple�̌��ɑ�����^
	//
	//�⑫
	//[t_Action_break == true],[T_Tuple=tuple_vp],�v������^[tuple_t]�̎��A���Ă���Tuple�̌^��[tuple_v]�ɂȂ�
	//
	//�^�̕ω���[2�i�� or 1�߂�]�̂ǂ��炩�ŕω���������
	//[tp �� t �� v �� vp �� tp]
	//
	//����
	//[T_Action]�̗v������^�ɔ�n�e���v���[�g�͊܂܂Ȃ���
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