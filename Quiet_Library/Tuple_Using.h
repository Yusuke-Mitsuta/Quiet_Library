/*!
 * Tuple_Using.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Class_Declare.h"
#include"Tuple_Convert_Action.h"

namespace quiet::N_Tuple
{

	//�擪�̗v�f��I������
	template<class T_Tuple>
	using U_Front = typename I_Select<0, T_Tuple>::type;

	//�Ō�̗v�f��I������
	template<class T_Tuple>
	using U_Back = typename I_Select<static_cast<int>(S_Parameter<T_Tuple>::size) - 1, T_Tuple>::type;

	//���̗v�f��I������
	template<class T_Tuple>
	using U_Next = typename I_Next<T_Tuple>::type;

	//�O�̗v�f��I������
	template<class T_Tuple>
	using U_Prev = typename I_Prev<T_Tuple>::type;

	//�w�肵���ԍ��̗v�f��I������
	template<int t_Select_Point, class T_Tuple>
	using U_Select = typename I_Select<t_Select_Point, T_Tuple>::type;

	//[type]�̕��я��𔽓]������
	template<class T_Tuple>
	using U_Reverse = typename I_Reverse<T_Tuple>::type;

	//�d�l
	//[T_Tuple_Data]��[_Index]�Ԗڂ̌^���擾����
	template<int _Index, class ...T>
	using U_Element_t = typename I_Element<_Index, T...>::type;

	//�d�l
	//[T_Insert_Base_Tuple]�̑I�𒆂̉ӏ���[T_Add_Typee...]�̗v�f��ǉ�����
	template<class T_Base_Tuple, class ...T_Add_Typee>
	using U_Insert = typename I_Insert<T_Base_Tuple, T_Add_Typee...>::type;

	//�d�l
	//[T_Insert_Base_Tuple]�̑I�𒆂̉ӏ���[t_Add_value...]�̗v�f��ǉ�����
	template<class T_Base_Tuple, auto ...t_Add_value>
	using U_Insert_v = typename I_Insert<T_Base_Tuple,
		integral_constant<t_Add_value>...>::type;

	//�d�l
	//[T_Insert_Base_Tuple]�̑I�𒆂̉ӏ���[T_Insert_Tuple]�̗v�f��ǉ�����
	//	[T_Add_type...]�̒���tuple���܂܂��ꍇ�Atuple��W�J���A�i�[����
	template<class T_Base_Tuple,class ...T_Add_Type>
	using U_Insert_tuple_expand = typename I_Insert<T_Base_Tuple, T_Add_Type...>::tuple_expand;

	//�d�l
	//[T_Insert_Base_Tuple]�̌���[T_Merge_Types...]�̗v�f��ǉ�����
	template<class T_Base_Tuple, class ...T_Add_Type>
	using U_Merge = typename I_Merge<T_Base_Tuple, T_Add_Type...>::type;

	//�d�l
	//[T_Insert_Base_Tuple]�̌���[T_Merge_Types...]�̗v�f��ǉ�����
	template<class T_Base_Tuple, auto ...t_Add_value>
	using U_Merge_v = typename I_Merge<T_Base_Tuple, 
		integral_constant< t_Add_value>...>::type;

	//�d�l
	//[T_Insert_Base_Tuple]�̌���[T_Merge_Types...]�̗v�f��ǉ�����
	//	[T_Add_type...]�̒���tuple���܂܂��ꍇ�Atuple��W�J���A�i�[����
	template<class T_Base_Tuple,class ...T_Add_Type>
	using U_Merge_tuple_expand = typename I_Merge<T_Base_Tuple, T_Add_Type...>::tuple_expand;

	//�d�l
	//[T_Tuple_Data]��[t_Point_1]��[t_Point_2]�̊Ԃ̗v�f���擾����
	//[t_Point2]���ݒ肳��Ȃ��ꍇ�A���݂̑I���ʒu���w�肷��
	template<class T_Tuple, size_t t_Point_1, size_t t_Point_2 = S_Parameter<T_Tuple>::head_size>
		//requires is_Element<T_Tuple_Data, t_Point_1>&& is_Element<T_Tuple_Data, t_Point_2>
	using U_Range = typename I_Range<T_Tuple, t_Point_1, t_Point_2>::type;

	//�d�l
	//�I���ʒu�̒l���폜����
	template<class T_Tuple_p, size_t t_Remove_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Remove = typename I_Remove<T_Tuple_p, t_Remove_Point>::type;


	template<class T_Tuple_v>
	using U_Tuple_t_To_v = typename Tuple_t_To_v<T_Tuple_v>::type;

	template<class T_Tuple_t>
	using U_Tuple_v_To_t = typename Tuple_v_To_t<T_Tuple_t>::type;


	//�d�l
	//[T_Change_Type]��C�ӂ�Tuple�ɕϊ�����B
	//���̌�A[tuple_t,tuple_tp,tuple_v,tuple_vp]�̂����ꂩ�ɕϊ�����B
	//
	//�e���v���[�g
	//[t_is_Target_Tuple_p]::�v������Tuple���|�C���g������[tuple_tp,tuple_vp]�ł��邩�H
	//[t_is_Target_Tuple_t]::�v������Tuple���^���Ǘ�[tuple_t,tuple_tp]�ł��邩�H
	// 
	//�⑫
	//�݊����̖����^�̏ꍇ[invalid_t]��Ԃ�
	template<class T_Change_Type, bool t_is_Target_Tuple_p, bool t_is_Target_Tuple_t>
	using U_Change_Tuple = I_Change_Tuple<T_Change_Type, t_is_Target_Tuple_p, t_is_Target_Tuple_t>::type;

	//�d�l
	//{Tuple}�ƌ݊����̂���^��[tuple_t]�^�ɕϊ�����B
	// 
	//�⑫
	//�݊����̖����^�̏ꍇ[invalid_t]��Ԃ�
	template<class T_Change_Type>
	using U_Change_Tuple_t = I_Change_Tuple<T_Change_Type, false, true>::type;
	
	//�d�l
	//{Tuple}�ƌ݊����̂���^��[tuple_tp]�^�ɕϊ�����B
	// 
	//�⑫
	//�݊����̖����^�̏ꍇ[invalid_t]��Ԃ�
	template<class T_Change_Type>
	using U_Change_Tuple_tp = I_Change_Tuple<T_Change_Type, true, true>::type;

	//�d�l
	//{Tuple}�ƌ݊����̂���^��[tuple_v]�^�ɕϊ�����B
	// 
	//�⑫
	//�݊����̖����^�̏ꍇ[invalid_t]��Ԃ�
	template<class T_Change_Type>
	using U_Change_Tuple_v = I_Change_Tuple<T_Change_Type, false, false>::type;

	//�d�l
	//{Tuple}�ƌ݊����̂���^��[tuple_vp]�^�ɕϊ�����B
	// 
	//�⑫
	//�݊����̖����^�̏ꍇ[invalid_t]��Ԃ�
	template<class T_Change_Type>
	using U_Change_Tuple_vp = I_Change_Tuple<T_Change_Type, true, false>::type;

	//�d�l
	//[T_Tuple_Data]��[t_Swap_Num_1]�Ԗڂ�[t_Swap_Num_2]�Ԗڂ̗v�f�����ւ���
	template<class T_Tuple, size_t t_Swap_Num_1, size_t t_Swap_Num_2 = S_Parameter<T_Tuple>::head_size>
		requires is_Element<T_Tuple, t_Swap_Num_1>&& is_Element<T_Tuple, t_Swap_Num_2>
	using U_Swap = typename I_Swap<T_Tuple, t_Swap_Num_1, t_Swap_Num_2>::type;


	//�d�l
	//[T_Control_Tuple]��[t_Change_Point]�̒l��[T_Change]�ɕύX����
	// 
	//[t_Change_Point]::[T_Control_Tuple]�̕ύX����v�f�ԍ��A�w�肵�Ȃ��ꍇ�́A���݂̑I���ʒu���d�l�����
	template<class T_Tuple_p, class T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Change = typename I_Change<T_Tuple_p, T_Change, t_Change_Point>::type;

	//�d�l
	//[T_Control_Tuple]��[t_Change_Point]�̒l��[T_Change]�ɕύX����
	// 
	//[t_Change_Point]::[T_Control_Tuple]�̕ύX����v�f�ԍ��A�w�肵�Ȃ��ꍇ�́A���݂̑I���ʒu���d�l�����
	template<class T_Tuple_p, auto t_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Change_v = typename I_Change<T_Tuple_p, 
		integral_constant<t_Change>, t_Change_Point>::type;


	//�d�l
	//[T_Control_Tuple]��[t_Change_Point]�̒l��[T_Change]�ɕύX����
	// 
	//[t_Change_Point]::[T_Control_Tuple]�̕ύX����v�f�ԍ��A�w�肵�Ȃ��ꍇ�́A���݂̑I���ʒu���d�l�����
	template<class T_Tuple_p, is_Tuple T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Change_tuple_expand = typename I_Change<T_Tuple_p, T_Change, t_Change_Point>::tuple_expand;

	//�d�l
	//[T_Tuple_Data]��[_Index]�Ԗڂ̗v�f���擾����
	template<int _Index, class T_Tuple_v>
	static constexpr auto U_Element_v = I_Element<_Index, T_Tuple_v>::value;

	template<class T_Tuple_not_p>
	using U_Create_p = typename I_Create_Pointer<T_Tuple_not_p>::type;

	template<class T_Tuple_p>
	using U_Remove_p = typename I_Remove_Pointer<T_Tuple_p>::type;
	

	template<class T_Tuple_v, auto number>
	using U_Template_Calculate_plus = typename I_Template_Calculate<T_Tuple_v, "+", number>::type;

	template<class T_Tuple_v, auto number>
	using U_Template_Calculate_minus = typename I_Template_Calculate<T_Tuple_v, "-", number>::type;

	//�d�l
	//[T_Tuple_Data]����[tuple_v< ... >]�̏��ԂŌ^�����Ԃɒ��o
	template<class T_Tuple, class T_Extract_Number>
	using U_Extract = typename I_Extract<T_Tuple, T_Extract_Number>::type;


	//�d�l
	//[T_Tuple_Data]�̒��g��[T_Outer_class]�̃e���v���[�g�ɃZ�b�g����
	//[T_Tuple_Data]��tuple�łȂ��ꍇ���̌^�̂܂܎��s�����
	//
	//�e���v���[�g
	//[T_Tuple_Data]::���g��W�J����Tuple
	//[T_Outer_class]::�W�J�������g�Ƃ���ɑ����^[T_Leftover_Types...]���Z�b�g����
	//[T_Leftover_Types...]::�W�J�������g�ɑ����Đݒ肷��^
	//
	//�⑫
	//[T_Tuple_Data<types...>]->[T_Outer_class<types... , T_Leftover_Types...>]�Ƃ���
	template<template<class...>class T_Outer_class, class T_Tuple, class ...T_Types>
	using U_Move_Template = typename I_Move_Template<T_Outer_class, T_Tuple, T_Types...>::type;

	//�d�l
	//[0 ... (t_array_size-1)]�̒l��[tuple_v]�ɓ���ĕԂ�
	//
	//�⑫
	//�܂�A[std::make_index_sequence<t_array_size>] �ŋA���Ă���^�� [std::integer_sequence<size_t,t_array_size...>]�̏����A[tupel_v<t_array_size...>]�ɕύX����
	template<size_t N>
	using U_index_sequence = typename I_index_sequence<N>::type;

	//�d�l
	//[0 ... (t_array_size-1)]�̒l��[tuple_v]�ɓ���ĕԂ�
	//
	//�⑫
	//�܂�A[std::make_index_sequence<t_array_size>] �ŋA���Ă���^�� [std::integer_sequence<size_t,t_array_size...>]�̏����A[tupel_v<t_array_size...>]�ɕύX����
	template<class T>
		requires requires
	{
		requires std::tuple_size_v<T> >= 0;
	}
	using U_index_sequence_tuple = typename I_index_sequence<std::tuple_size_v<T>>::type;


	//�d�l
	//[N_1 ... t_array_size-2]�̒l��[tuple_v]�ɓ���ĕԂ�
	template<size_t N_1, size_t N_2>
	using U_range_index_sequence = typename I_range_index_sequence<N_1, N_2>::type;

	//�d�l
	//[T_Tuple_Data]�̗v�f��������o���A[TT_Action]��[::type]�����s���A���ʂ�[tuple_t]�ɓZ�߂�
	//
	//�e���v���[�g
	//[TT_Action]::[type]���Ăяo���N���X�e���v���[�g
	//[T_Tuple_Data]::�W�J���A�e�v�f��[TT_Action::type]���Ăяo��
	//[T_Extra...]::[TT_Action::type]���Ăяo���ہA�ǉ��ŃZ�b�g����^
	//
	//�⑫
	//[T_Tuple_Data -> tuple_t<T_Request_Order...>] -> [tuple_t<TT_Action<T_Request_Order,T_Extra...>::type...>]�ƂȂ�
	template<template<class...>class TT_Action, class T_Tuple, class ...T_Extra>
	using U_Elements_Action = I_Elements_Action<TT_Action, T_Tuple, T_Extra...>::type;

	//�d�l
	//�v�f�Ɍ^[T_Request_Order]��[t_array_size]���A[tuple_t]�����
	template<class T, size_t N>
	using U_Repeat_Multiple = I_Repeat_Multiple<T, N>::type;

	//�d�l
	//�w�肵���K�w�܂Ń^�v�����̗v�f�̒�����A�^�v���ƌ݊��������^��W�J����
	//
	// �e���v���[�g
	//[T_Tuple_Data]::�W�J����[Tuple_t]�̌^
	//[t_expand_lelve]::�W�J����K�w�̏��
	//�⑫
	//[T_Tuple_Data]��[tuple]�ł͂Ȃ������ꍇ[T_Tuple_Data]�^��Ԃ�
	template<class T_Tuple, size_t t_expand_lelve = 1 >
	using U_Expand = I_Expand<T_Tuple, t_expand_lelve>::type;

	//�d�l
	//�^�v�����̗v�f�̒�����A�^�v���ƌ݊��������^��S�ēW�J����
	//
	// �e���v���[�g
	//[T_Tuple_Data]::�W�J����[Tuple_t]�̌^
	//�⑫
	//[T_Tuple_Data]��[tuple]�ł͂Ȃ������ꍇ[T_Tuple_Data]�^��Ԃ�
	template<class T_Tuple>
	using U_Expand_All = I_Expand<T_Tuple, static_cast<size_t>(0-1)>::type;

	//�d�l
	//�p�����[�^�p�b�N[Ts...]����A������^��{tuple_zip< T_Request_Order, t_array_size >}�Ɉ��k����
	template<class ...Ts>
	using U_Zip = I_Zip<Ts...>::type;

	//�d�l
	//�^�v�����̗v�f����A������^��{tuple_zip< T_Request_Order, t_array_size >}�Ɉ��k����
	template<class T_Tuple>
	using U_Zip_Tuple = I_Zip_Tuple<T_Tuple>::type;


	//�d�l
	//[Tuple]�ƌ݊����̂���^�̃��X�g����A�w�肵���^�����ԖڂɊ܂܂�邩�T���B
	//
	//�e���v���[�g
	//[T_Search_Tuple]::�w�肵���^��T���A[Tuple]�ƌ݊����̂���^
	//[T_Search_Type]::[T_Search_Tuple]����T���^
	template<class T_Search_Tuple, class T_Search_Type>
	using U_Search_t = I_Search_t<T_Search_Tuple, T_Search_Type>::type;

	//�d�l
	//[Tuple_v]�ƌ݊����̂���^�̃��X�g����A�w�肵���l�����ԖڂɊ܂܂�邩�T���B
	//
	//�e���v���[�g
	//[T_Search_Tuple]::�w�肵���l��T���A[Tuple_v]�ƌ݊����̂���^
	//[T_Search_Value]::[T_Search_Tuple]����T���^
	template<class T_Search_Tuple, auto t_Search_Value>
	using U_Search_v = I_Search_v<T_Search_Tuple, t_Search_Value>::type;

}

