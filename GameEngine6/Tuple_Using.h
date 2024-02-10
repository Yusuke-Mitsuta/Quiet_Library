#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
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
	//[T_Tuple]��[_Index]�Ԗڂ̌^���擾����
	template<int _Index, class T_Tuple_t>
	using U_Element_t = typename I_Element<_Index, T_Tuple_t>::type;

	//�d�l
	//[T_Base_Tuple]�̑I�𒆂̉ӏ���[T_Add_Typee...]�̗v�f��ǉ�����
	template<class T_Base_Tuple, class ...T_Add_Typee>
	using U_Insert = typename I_Insert<T_Base_Tuple, T_Add_Typee...>::type;

	//�d�l
	//[T_Base_Tuple]�̑I�𒆂̉ӏ���[t_Add_value...]�̗v�f��ǉ�����
	template<class T_Base_Tuple, auto ...t_Add_value>
	using U_Insert_v = typename I_Insert<T_Base_Tuple,
		integral_constant<t_Add_value>...>::type;

	//�d�l
	//[T_Base_Tuple]�̑I�𒆂̉ӏ���[T_Insert_Tuple]�̗v�f��ǉ�����
	//	[T_Add_type...]�̒���tuple���܂܂��ꍇ�Atuple��W�J���A�i�[����
	template<class T_Base_Tuple,class ...T_Add_Type>
	using U_Insert_tuple_expand = typename I_Insert<T_Base_Tuple, T_Add_Type...>::tuple_expand;

	//�d�l
	//[T_Base_Tuple]�̌���[T_Add_Type...]�̗v�f��ǉ�����
	template<class T_Base_Tuple, class ...T_Add_Type>
	using U_Merge = typename I_Merge<T_Base_Tuple, T_Add_Type...>::type;

	//�d�l
	//[T_Base_Tuple]�̌���[T_Add_Type...]�̗v�f��ǉ�����
	template<class T_Base_Tuple, auto ...t_Add_value>
	using U_Merge_v = typename I_Merge<T_Base_Tuple, 
		integral_constant< t_Add_value>...>::type;

	//�d�l
	//[T_Base_Tuple]�̌���[T_Add_Type...]�̗v�f��ǉ�����
	//	[T_Add_type...]�̒���tuple���܂܂��ꍇ�Atuple��W�J���A�i�[����
	template<class T_Base_Tuple,class ...T_Add_Type>
	using U_Merge_tuple_expand = typename I_Merge<T_Base_Tuple, T_Add_Type...>::tuple_expand;

	//�d�l
	//[T_Tuple]��[t_Point_1]��[t_Point_2]�̊Ԃ̗v�f���擾����
	//[t_Point2]���ݒ肳��Ȃ��ꍇ�A���݂̑I���ʒu���w�肷��
	template<class T_Tuple, size_t t_Point_1, size_t t_Point_2 = S_Parameter<T_Tuple>::head_size>
		//requires is_Element<T_Tuple, t_Point_1>&& is_Element<T_Tuple, t_Point_2>
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
	//[T_Tuple]��[t_Swap_Num_1]�Ԗڂ�[t_Swap_Num_2]�Ԗڂ̗v�f�����ւ���
	template<class T_Tuple, size_t t_Swap_Num_1, size_t t_Swap_Num_2 = S_Parameter<T_Tuple>::head_size>
		requires is_Element<T_Tuple, t_Swap_Num_1>&& is_Element<T_Tuple, t_Swap_Num_2>
	using U_Swap = typename I_Swap<T_Tuple, t_Swap_Num_1, t_Swap_Num_2>::type;


	//�d�l
	//[T_Tuple_p]��[t_Change_Point]�̒l��[T_Change]�ɕύX����
	// 
	//[t_Change_Point]::[T_Tuple_p]�̕ύX����v�f�ԍ��A�w�肵�Ȃ��ꍇ�́A���݂̑I���ʒu���d�l�����
	template<class T_Tuple_p, class T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Change = typename I_Change<T_Tuple_p, T_Change, t_Change_Point>::type;

	//�d�l
	//[T_Tuple_p]��[t_Change_Point]�̒l��[T_Change]�ɕύX����
	// 
	//[t_Change_Point]::[T_Tuple_p]�̕ύX����v�f�ԍ��A�w�肵�Ȃ��ꍇ�́A���݂̑I���ʒu���d�l�����
	template<class T_Tuple_p, auto t_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Change_v = typename I_Change<T_Tuple_p, 
		integral_constant<t_Change>, t_Change_Point>::type;


	//�d�l
	//[T_Tuple_p]��[t_Change_Point]�̒l��[T_Change]�ɕύX����
	// 
	//[t_Change_Point]::[T_Tuple_p]�̕ύX����v�f�ԍ��A�w�肵�Ȃ��ꍇ�́A���݂̑I���ʒu���d�l�����
	template<class T_Tuple_p, is_Tuple T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::head_size>
	using U_Change_tuple_expand = typename I_Change<T_Tuple_p, T_Change, t_Change_Point>::tuple_expand;

	//�d�l
	//[T_Tuple]��[_Index]�Ԗڂ̗v�f���擾����
	template<int _Index, class T_Tuple_v>
	static constexpr auto U_Element_v = I_Element<_Index, T_Tuple_v>::value;

	template<class T_Tuple_not_p>
	using U_Create_p = typename I_Create_Pointer<T_Tuple_not_p>::type;

	template<class T_Tuple_p>
	using U_Remove_p = typename I_Remove_Pointer<T_Tuple_p>::type;


	template<class T_Tuple_v, auto number>
	using U_Calculate_plus = typename I_Tuple_Calculate<T_Tuple_v, "+", number>::type;

	template<class T_Tuple_v, auto number>
	using U_Calculate_minus = typename I_Tuple_Calculate<T_Tuple_v, "-", number>::type;

	template<class T_Tuple_v, auto number>
	using U_Calculate_multiply = typename I_Tuple_Calculate<T_Tuple_v, "*", number>::type;

	//�d�l
	//[T_Tuple]����[tuple_v< ... >]�̏��ԂŌ^�����Ԃɒ��o
	template<class T_Tuple, class T_Extract_Number>
	using U_Extract = typename I_Extract<T_Tuple, T_Extract_Number>::type;


	//�d�l
	//[T_Tuple]�̒��g��[T_Outer_class]�̃e���v���[�g�ɃZ�b�g����
	//[T_Tuple]��tuple�łȂ��ꍇ���̌^�̂܂܎��s�����
	//
	//�e���v���[�g
	//[T_Tuple]::���g��W�J����Tuple
	//[T_Outer_class]::�W�J�������g�Ƃ���ɑ����^[T_Types...]���Z�b�g����
	//[T_Types...]::�W�J�������g�ɑ����Đݒ肷��^
	//
	//�⑫
	//[T_Tuple<types...>]->[T_Outer_class<types... , T_Types...>]�Ƃ���
	template<template<class...>class T_Outer_class, class T_Tuple, class ...T_Types>
	using U_Move_Template = typename I_Move_Template<T_Outer_class, T_Tuple, T_Types...>::type;

	//�d�l
	//[0 ... (N-1)]�̒l��[tuple_v]�ɓ���ĕԂ�
	//
	//�⑫
	//�܂�A[std::make_index_sequence<N>] �ŋA���Ă���^�� [std::integer_sequence<size_t,N...>]�̏����A[tupel_v<N...>]�ɕύX����
	template<size_t N>
	using U_index_sequence = typename I_index_sequence<N>::type;

	//�d�l
	//[N_1 ... N-2]�̒l��[tuple_v]�ɓ���ĕԂ�
	template<size_t N_1, size_t N_2>
	using U_range_index_sequence = typename I_range_index_sequence<N_1, N_2>::type;

	//�d�l
	//[T_Tuple]�̗v�f��������o���A[TT_Action]��[::type]�����s���A���ʂ�[tuple_t]�ɓZ�߂�
	//
	//�e���v���[�g
	//[TT_Action]::[type]���Ăяo���N���X�e���v���[�g
	//[T_Tuple]::�W�J���A�e�v�f��[TT_Action::type]���Ăяo��
	//[T_Extra...]::[TT_Action::type]���Ăяo���ہA�ǉ��ŃZ�b�g����^
	//
	//�⑫
	//[T_Tuple -> tuple_t<T...>] -> [tuple_t<TT_Action<T,T_Extra...>::type...>]�ƂȂ�
	template<template<class...>class TT_Action, class T_Tuple, class ...T_Extra>
	using U_Elements_Action = I_Elements_Action<TT_Action, T_Tuple, T_Extra...>::type;

	//�d�l
	//�v�f�Ɍ^[T]��[N]���A[tuple_t]�����
	template<class T, size_t N>
	using U_Repeat_Multiple = I_Repeat_Multiple<T, N>::type;

	//�d�l
	//�w�肵���K�w�܂Ń^�v�����̗v�f�̒�����A�^�v���ƌ݊��������^��W�J����
	//
	// �e���v���[�g
	//[T_Tuple]::�W�J����[Tuple_t]�̌^
	//[t_expand_lelve]::�W�J����K�w�̏��
	//�⑫
	//[T_Tuple]��[tuple]�ł͂Ȃ������ꍇ[T_Tuple]�^��Ԃ�
	template<class T_Tuple, size_t t_expand_lelve = 1 >
	using U_Expand = I_Expand<T_Tuple, t_expand_lelve>::type;

	//�d�l
	//�^�v�����̗v�f�̒�����A�^�v���ƌ݊��������^��S�ēW�J����
	//
	// �e���v���[�g
	//[T_Tuple]::�W�J����[Tuple_t]�̌^
	//�⑫
	//[T_Tuple]��[tuple]�ł͂Ȃ������ꍇ[T_Tuple]�^��Ԃ�
	template<class T_Tuple>
	using U_Expand_All = I_Expand<T_Tuple, static_cast<size_t>(0-1)>::type;

	//�d�l
	//�p�����[�^�p�b�N[Ts...]����A������^��{tuple_zip< T, N >}�Ɉ��k����
	template<class ...Ts>
	using U_Zip = I_Zip<Ts...>::type;

	//�d�l
	//�^�v�����̗v�f����A������^��{tuple_zip< T, N >}�Ɉ��k����
	template<class T_Tuple>
	using U_Zip_Tuple = I_Zip_Tuple<T_Tuple>::type;


}

