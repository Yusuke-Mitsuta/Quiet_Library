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
	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
	struct S_Action_Tuple
	{
		using type = T_Action<T_Tuple>::type;
	};


	//t��v
	//vp��tp
	template<bool t_Action_Type_Tuple_p, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
		requires (same_as_tuple_t<T_Tuple>)||(same_as_tuple_tp<T_Tuple> && t_Action_Type_Tuple_p)
	struct S_Action_Tuple<t_Action_Type_Tuple_p,false,t_Action_break,T_Action,T_Tuple>
	{
		using return_type= S_Action_Tuple<t_Action_Type_Tuple_p, false, t_Action_break, T_Action, U_Tuple_t_To_v<T_Tuple>>::type;

		using type = U_Tuple_v_To_t<return_type>;
	};

	//v��vp
	//tp��t
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
			using type = U_Remove_p<return_type>;
		};

		using type = S_action_break<>::type;

	};

	//vp��tp
	//t��v
	template<bool t_Action_Type_Tuple_p, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
		requires (same_as_tuple_vp<T_Tuple>) || (same_as_tuple_v<T_Tuple> && !t_Action_Type_Tuple_p)
	struct S_Action_Tuple<t_Action_Type_Tuple_p, true,t_Action_break, T_Action, T_Tuple>
	{
		using return_type = S_Action_Tuple<t_Action_Type_Tuple_p, true, t_Action_break, T_Action, U_Tuple_v_To_t<T_Tuple>>::type;

		using type = U_Tuple_t_To_v<return_type>;

	};

	//tp��t
	//v��vp
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
			static constexpr size_t prev_head_size = S_Parameter<T_Tuple>::Size_Head;
			using create_p = U_Create_p<return_type>;
			using type = U_if_t1<U_Select<prev_head_size,create_p>,create_p,(prev_head_size < S_Parameter<return_type>::Size)>;
		};

		using type = S_action_break<>::type;

	};




	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, template<class...>class T_Action, class T_Tuple, size_t t_Start_Point>
	struct S_Action_Tuple_Helper
	{
	private:

		template<class T_Tuple,class T_Start_Point_Judge=std::bool_constant<
			((t_Start_Point < S_Parameter<T_Tuple>::Size) &&
			(t_Start_Point != S_Parameter<T_Tuple>::Size_Head))>>
		struct I_Tuple_Start_Point_Set
		{
			using type = T_Action<T_Tuple>::type;

		};

		template<is_Tuple_p T_Tuple>
		struct I_Tuple_Start_Point_Set<T_Tuple, std::true_type>
		{
			using return_type = T_Action<U_Select<t_Start_Point, T_Tuple>>::type;

			template<bool t_not_size_change_Judge = (S_Parameter<T_Tuple>::Size_Head < S_Parameter<return_type>::Size) > 
			struct S_Tuple_Start_Point_Set
			{
				using type = U_Select<S_Parameter<T_Tuple>::Size_Head, return_type>;
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

		using Return_not_p = Return_Tuple<true>::type;

		using Return_p = Return_Tuple<false>::type;

		using type = Return_Tuple<is_Tuple_not_p<T_Tuple>>::type;

	};



}