/*!
 * Tuple_Class_Declare.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include<tuple>

#include"Tuple_Concept.h"
#include"String.h"

namespace quiet
{

	template<auto t_Value>
	struct integral_constant;

	template<class ...T_Types>
	struct tuple_t;

	template<quiet::N_Tuple::same_as_tuple_t T_Head, class T, quiet::N_Tuple::same_as_tuple_t T_Tail>
	struct tuple_tp;



	template<auto ..._Value>
	struct tuple_v;

	template<quiet::N_Tuple::same_as_tuple_v T_Head, auto _value, quiet::N_Tuple::same_as_tuple_v T_Tail>
	struct tuple_vp;

}

namespace quiet::N_Tuple
{
	template<class T_Types>
	struct S_Parameter;

	template<class T_Tuple>
	struct S_Size;

	struct Tuple_p;

	template<class T_Tuple_p>
	struct I_Remove_Pointer;

	template<class T_Tuple_p>
	struct I_Create_Pointer;

	template<class T_Tuple>
	struct Control_p;

	template<class T_Tuple_t>
	struct I_Next;

	template<class T_Tuple_t>
	struct I_Prev;

	template<int t_Point, class T_Tuple_t>
	struct I_Select;

	template<size_t _Index, class T_Tuple>
	struct I_Element;

	template<class T_Tuple_p, size_t t_Remove_Point = S_Parameter<T_Tuple_p>::head_size>
	struct I_Remove;

	template<class T_Tuple_t>
	struct I_Reverse;

	template<class T_Base_Tuple, class ...T_Add_Typee>
	struct I_Insert;

	template<class T_Base_Tuple, class ...T_Add_Type>
	struct I_Merge;

	template<class T_Tuple_p, class T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	struct I_Change;

	template<class T_Tuple, size_t t_Swap_Num_1, size_t t_Swap_Num_2 = S_Parameter<T_Tuple>::head_size>
		requires is_Element<T_Tuple, t_Swap_Num_1>&& is_Element<T_Tuple, t_Swap_Num_2>
	struct I_Swap;

	template<class T_Tuple, size_t t_Point_1, size_t t_Point_2>
	struct I_Range;

	template<class T_Tuple, class T_Extract_Number>
	struct I_Extract;

	template<class T>
	struct Tuple_v_To_t;

	template<class T>
	struct Tuple_t_To_v;

	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
	struct S_Tuple_Type_Change_Action;

	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t,template<class...>class T_Action, class T_Tuple, size_t t_Start_Point= S_Parameter<T_Tuple>::head_size>
	struct S_Tuple_Type_Change_Action_Helper;


	//�d�l
	//[T_Tuple_Data]��[tuple_tp]�ɕϊ���[T_Action]��[::type]���Ăяo��
	//�@���ʂ�[tuple_tp]����[T_Tuple_Data]�Ɠ��^�C�v��Tuple�ɕϊ����Ԃ��B
	//
	//�e���v���[�g
	//[T_Action]::�ϊ������ATuple_tp��[::type]���Ăяo���N���X�e���v���[�g
	//[T_Tuple_Data]::�ϐ�����Tuple�^
	//[t_Start_Point]::�ϊ�����Tuple_tp�̏����I���̏ꏊ
	// 
	//using
	//[Return_not_p]::[tuple_tp,vp]����[tuple_t,v]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu��߂��������X�L�b�v����
	//[Return_p]::[tuple_t,v]����[tuple_tp,vp]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu���O���������X�L�b�v����
	// 
	//�⑫
	//�ϐ��Ɏ��s�����ꍇ�A��������[T_Tuple_Data]�����̂܂ܕԂ����
	template<template<class...>class T_Action, class T_Tuple, size_t t_Start_Point = S_Parameter<T_Tuple>::head_size>
	using S_Tuple_tp_Change_Action = S_Tuple_Type_Change_Action_Helper<true, true, T_Action, T_Tuple, t_Start_Point>;

	//�d�l
	//[T_Tuple_Data]��[tuple_t]�ɕϊ���[T_Action]��[::type]���Ăяo��
	//�@���ʂ�[tuple_t]����[T_Tuple_Data]�Ɠ��^�C�v��Tuple�ɕϊ����Ԃ��B
	//
	//�e���v���[�g
	//[T_Action]::�ϊ������ATuple_t��[::type]���Ăяo���N���X�e���v���[�g
	//[T_Tuple_Data]::�ϐ�����Tuple�^
	// 
	//using
	//[Return_not_p]::[tuple_tp,vp]����[tuple_t,v]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu��߂��������X�L�b�v����
	//[Return_p]::[tuple_t,v]����[tuple_tp,vp]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu���O���������X�L�b�v����
	// 
	//�⑫
	//�ϐ��Ɏ��s�����ꍇ�A��������[T_Tuple_Data]�����̂܂ܕԂ����
	template<template<class...>class T_Action, class T_Tuple>
	using S_Tuple_t_Change_Action = S_Tuple_Type_Change_Action_Helper<false, true, T_Action, T_Tuple>;

	//�d�l
	//[T_Tuple_Data]��[tuple_vp]�ɕϊ���[T_Action]��[::type]���Ăяo��
	//�@���ʂ�[tuple_vp]����[T_Tuple_Data]�Ɠ��^�C�v��Tuple�ɕϊ����Ԃ��B
	//
	//�e���v���[�g
	//[T_Action]::�ϊ������ATuple_vp��[::type]���Ăяo���N���X�e���v���[�g
	//[T_Tuple_Data]::�ϐ�����Tuple�^
	//[t_Start_Point]::�ϊ�����Tuple_vp�̏����I���̏ꏊ
	// 
	//using
	//[Return_not_p]::[tuple_tp,vp]����[tuple_t,v]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu��߂��������X�L�b�v����
	//[Return_p]::[tuple_t,v]����[tuple_tp,vp]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu���O���������X�L�b�v����
	// 
	//�⑫
	//�ϐ��Ɏ��s�����ꍇ�A��������[T_Tuple_Data]�����̂܂ܕԂ����
	template<template<class...>class T_Action, class T_Tuple,size_t t_Start_Point = S_Parameter<T_Tuple>::head_size>
	using S_Tuple_vp_Change_Action = S_Tuple_Type_Change_Action_Helper<true, false, T_Action, T_Tuple, t_Start_Point>;

	//�d�l
	//[T_Tuple_Data]��[tuple_v]�ɕϊ���[T_Action]��[::type]���Ăяo��
	//�@���ʂ�[tuple_v]����[T_Tuple_Data]�Ɠ��^�C�v��Tuple�ɕϊ����Ԃ��B
	//
	//�e���v���[�g
	//[T_Action]::�ϊ������ATuple_v��[::type]���Ăяo���N���X�e���v���[�g
	//[T_Tuple_Data]::�ϐ�����Tuple�^
	//[t_Start_Point]::�ϊ�����Tuple_v�̏����I���̏ꏊ
	// 	
	//using
	//[Return_not_p]::[tuple_tp,vp]����[tuple_t,v]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu��߂��������X�L�b�v����
	//[Return_p]::[tuple_t,v]����[tuple_tp,vp]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu���O���������X�L�b�v����
	// 
	//�⑫
	//�ϐ��Ɏ��s�����ꍇ�A��������[T_Tuple_Data]�����̂܂ܕԂ����
	template<template<class...>class T_Action, class T_Tuple>
	using S_Tuple_v_Change_Action = S_Tuple_Type_Change_Action_Helper<false, false, T_Action, T_Tuple>;

	//�d�l
	//[T_Change_Type]��C�ӂ�Tuple�ɕϊ�����B
	//���̌�A[tuple_t,tuple_tp,tuple_v,tuple_vp]�̂����ꂩ�ɕϊ�����B
	//
	//�e���v���[�g
	//[t_is_Target_Tuple_p]::�v������Tuple���|�C���g������[tuple_tp,tuple_vp]�ł��邩�H
	//[t_is_Target_Tuple_t]::�v������Tuple���^���Ǘ�[tuple_t,tuple_tp]�ł��邩�H
	//
	//�^�̕ω���[2�i�� or 1�߂�]�̂ǂ��炩�ŕω���������
	//[tp �� t �� v �� vp �� tp]
	template<class T_Change_Type, class T_Target_Type>
	struct I_Change_Tuple;

	template<class T_Tuple_v, String t_operator, auto number>
	struct I_Template_Calculate;

	template<template<class...>class T_Outer_class, class ...T_Types>
	struct I_Move_Template;

	template<size_t N>
	struct I_index_sequence;

	template<size_t N_1, size_t N_2>
	struct I_range_index_sequence;

	template<template<class...>class TT_Action, class T_Tuple, class ...T_Extra>
	struct I_Elements_Action;

	template<class T_Fn, class ...T_Set_Types>
	struct I_Apply_Action;

	//�d�l
	//�v�f�Ɍ^[T_Request_Order]��[t_array_size]���A[tuple_t]�����
	template<class T, size_t N>
	struct I_Repeat_Multiple;

	//�d�l
	//�w�肵���񐔂܂Ń^�v�����̗v�f��W�J����
	//
	// �e���v���[�g
	//[T_Tuple_Data]::�W�J����[Tuple_t]�̌^
	//[t_expand_lelve]::�W�J����K�w�̏��
	template<class T_Tuple, size_t t_expand_lelve = 1>
	struct I_Expand;

	//�d�l
	//���k����Ă���Tuple������
	template<class _Ty1, size_t N>
	struct tuple_zip;

	//�d�l
	//�p�����[�^�p�b�N[Ts...]����A������^��{tuple_zip< T_Request_Order, t_array_size >}�Ɉ��k����
	template<class ...Ts>
	struct I_Zip;

	//�d�l
	//�^�v�����̗v�f����A������^��{tuple_zip< T_Request_Order, t_array_size >}�Ɉ��k����
	template<class T_Tuple>
	struct I_Zip_Tuple;

	//�d�l
	//[Tuple]�ƌ݊����̂���^�̃��X�g����A�w�肵���^�����ԖڂɊ܂܂�邩�T���B
	//
	//�e���v���[�g
	//[T_Search_Tuple]::�w�肵���^��T���A[Tuple]�ƌ݊����̂���^
	//[T_Search_Type]::[T_Search_Tuple]����T���^
	template<class T_Search_Tuple, class T_Search_Type>
	struct I_Search_t;

	//�d�l
	//[Tuple_v]�ƌ݊����̂���^�̃��X�g����A�w�肵���l�����ԖڂɊ܂܂�邩�T���B
	//
	//�e���v���[�g
	//[T_Search_Tuple]::�w�肵���l��T���A[Tuple_v]�ƌ݊����̂���^
	//[T_Search_Value]::[T_Search_Tuple]����T���^
	template<class T_Search_Tuple, auto t_Search_Value>
	struct I_Search_v;
}