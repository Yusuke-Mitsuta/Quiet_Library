/*!
 * Tuple_Move_Template.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Class_Declare.h"
namespace quiet::N_Tuple
{

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
	template<template<class...>class T_Outer_class,class ...T_Types>
	struct I_Move_Template
	{
	private:
		template<class ...T_Leftover_Types>
		struct S_Move_Template
		{
			using type = T_Outer_class<T_Leftover_Types...>;
		};

		template<class ...T_Tuple_types, class ...T_Leftover_Types>
		struct S_Move_Template<tuple_t<T_Tuple_types...>, T_Leftover_Types...>
		{
			using type = T_Outer_class<T_Tuple_types..., T_Leftover_Types...>;
		};

		template<class ...T_Head, class T, class ...T_Tail, class ...T_Leftover_Types>
		struct S_Move_Template<tuple_tp<tuple_t<T_Head...>, T, tuple_t<T_Tail...>>, T_Leftover_Types...>
		{
			using type = T_Outer_class<T_Head... , T , T_Tail... , T_Leftover_Types...>;
		};

		template<class ...T_Head, class ...T_Tail, class ...T_Leftover_Types>
		struct S_Move_Template<tuple_tp<tuple_t<T_Head...>, invalid_t, tuple_t<T_Tail...>>, T_Leftover_Types...>
		{
			using type = T_Outer_class<T_Head..., T_Tail..., T_Leftover_Types...>;
		};
	public:

		using type =typename S_Move_Template<T_Types...>::type;

	};
}