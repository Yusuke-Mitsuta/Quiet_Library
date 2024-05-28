/*!
 * Tuple_Type_Change_Action_Helper.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"SwapType.h"

namespace quiet::N_Tuple
{

	//�d�l
	//[T_Tuple_Data]��[t_Action_Type_Tuple_p,t_Action_Type_Tuple_t]�̒l�ɂ���ĕϊ���
	// [T_Action]��[::type]���Ăяo���A
	// ���ʂ���[T_Tuple_Data]�Ɠ��^�C�v��Tuple�ɕϊ����Ԃ��B
	//
	//�e���v���[�g
	//[t_Action_Type_Tuple_p]::�v������Tuple��[tuple_tp,vp]�Ȃ�[true]�ɂ���
	//[t_Action_Type_Tuple_t]::�v������Tuple��[tuple_t,tp]�Ȃ�[true]�ɂ���
	//[T_Action]::�ϊ������^��[::type]���Ăяo���N���X�e���v���[�g
	//[T_Tuple_Data]::�ϐ�����Tuple�^
	//[t_Start_Point]::�ϊ�����[tuple_tp,vp]�̏����I���̏ꏊ
	// 
	//using
	//[Return_not_p]::[tuple_tp,vp]����[tuple_t,v]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu��߂��������X�L�b�v����
	//[Return_p]::[tuple_t,v]����[tuple_tp,vp]�ɕϊ���[T_Action]���Ăяo�����ہA
	//	�I���ʒu���O���������X�L�b�v����
	// 
	//�⑫
	//�ϐ��Ɏ��s�����ꍇ�A��������[T_Tuple_Data]�����̂܂ܕԂ����
	template<template<class...>class T_Action, class T_Convert_Tuple, bool t_is_Target_Tuple_p, bool t_is_Target_Tuple_t, size_t t_Start_Point>
	struct I_Change_Tuple_Action_Helper
	{
	private:


		template<bool t_Action_break>
		using Return_Tuple =
			I_Change_Tuple_Action<T_Convert_Tuple,t_Action_Type_Tuple_p, t_Action_Type_Tuple_t,
			(t_Action_break^ is_Tuple_not_p<T_Convert_Tuple>), I_Tuple_Start_Point_Set>;

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
		//[T_Tuple_Data]��[tuple_vp]�ɕϊ���[T_Action]��[::type]���Ăяo��
		//�@���ʂ�[tuple_vp]����[T_Tuple_Data]�Ɠ��^�C�v��Tuple�ɕϊ����Ԃ��B
		using type = Return_Tuple<is_Tuple_not_p<T_Convert_Tuple>>::type;

	};


}