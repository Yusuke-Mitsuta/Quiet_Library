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

	//�d�l
	//[T_Tuple_Data]���w�肵���^�ɕό`���A[T_Action]�̃e���v���[�g�ɕό`��̌^��[T_Leftover_Types...]�����킹�āA[T_Action<...>::type]�����s����
	//���s��̌^��T_Tuple�̌^�̏����ɖ߂�
	//
	//�e���v���[�g
	//[t_Action_Type_Tuple_p]::[T_Action]�����s���鎞�ɗv������Tuple���|�C���g������[tuple_tp,tuple_vp]�ł��邩�H
	//[t_Action_Type_Tuple_t]::[T_Action]�����s���鎞�ɗv������Tuple���^���Ǘ�[tuple_t,tuple_tp]�ł��邩�H
	//[t_Action_break]::[T_Action]�����s��A�|�C���g�����̏�Ԃ��ێ����邩�H
	//[T_Action]::[T_Action< ... >::type]�Ŏ��s����^
	//[T_Tuple_Data]::�����ɉ����ĕύX����Tuple
	//[T_Leftover_Types...]::[T_Action]�Ŏ��s���A�ύX���Tuple�̌��ɑ�����^
	//
	//�⑫
	//[t_Action_break == true],[T_Tuple_Data=tuple_vp],�v������^[tuple_t]�̎��A���Ă���Tuple�̌^��[tuple_v]�ɂȂ�
	//
	//�^�̕ω���[2�i�� or 1�߂�]�̂ǂ��炩�ŕω���������
	//[tp �� t �� v �� vp �� tp]
	//
	//����
	//[T_Action]�̗v������^�ɔ�n�e���v���[�g�͊܂܂Ȃ���
	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Convert_Tuple>
	struct S_Tuple_Type_Change_Action
	{
		using type = T_Action<T_Convert_Tuple>::type;
	};

	//t��v
	//vp��tp
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

	//v��vp
	//tp��t
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

	//vp��tp
	//t��v
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

	//tp��t
	//v��vp
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