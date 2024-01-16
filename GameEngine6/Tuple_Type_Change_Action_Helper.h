#pragma once

#include"Tuple_Declare.h"
#include"If_Type.h"

namespace N_Tuple
{

	//�d�l
	//[T_Tuple]��[t_Action_Type_Tuple_p,t_Action_Type_Tuple_t]�̒l�ɂ���ĕϊ���
	// [T_Action]��[::type]���Ăяo���A
	// ���ʂ���[T_Tuple]�Ɠ��^�C�v��Tuple�ɕϊ����Ԃ��B
	//
	//�e���v���[�g
	//[t_Action_Type_Tuple_p]::�v������Tuple��[tuple_tp,vp]�Ȃ�[true]�ɂ���
	//[t_Action_Type_Tuple_t]::�v������Tuple��[tuple_t,tp]�Ȃ�[true]�ɂ���
	//[T_Action]::�ϊ������^��[::type]���Ăяo���N���X�e���v���[�g
	//[T_Tuple]::�ϐ�����Tuple�^
	//[t_Start_Point]::�ϊ�����[tuple_tp,vp]�̏����I���̏ꏊ
	// 
	//using
	//[Return_not_p]::[tuple_tp,vp]����[tuple_t,v]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu��߂��������X�L�b�v����
	//[Return_p]::[tuple_t,v]����[tuple_tp,vp]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu���O���������X�L�b�v����
	// 
	//�⑫
	//�ϐ��Ɏ��s�����ꍇ�A��������[T_Tuple]�����̂܂ܕԂ����
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

		//�d�l
		//[tuple_tp,vp]����[tuple_t,v]�ɕϊ���[T_Action]���Ăяo�����ہA
		//	�I���ʒu��߂��������X�L�b�v����
		using Return_not_p = Return_Tuple<true>::type;

		//�d�l
		//[tuple_t, v] ����[tuple_tp, vp]�ɕϊ���[T_Action]���Ăяo�����ہA
		//	�I���ʒu���O���������X�L�b�v����
		using Return_p = Return_Tuple<false>::type;

		//�d�l
		//[T_Tuple]��[tuple_vp]�ɕϊ���[T_Action]��[::type]���Ăяo��
		//�@���ʂ�[tuple_vp]����[T_Tuple]�Ɠ��^�C�v��Tuple�ɕϊ����Ԃ��B
		using type = Return_Tuple<is_Tuple_not_p<T_Tuple>>::type;

	};

}