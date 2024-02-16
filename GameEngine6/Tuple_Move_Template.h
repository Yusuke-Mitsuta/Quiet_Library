#pragma once

#include"Tuple_Class_Declare.h"
namespace N_Tuple
{

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
	template<template<class...>class T_Outer_class,class ...T_Types>
	struct I_Move_Template
	{
	private:
		template<class ...T_Types>
		struct S_Move_Template
		{
			using type = T_Outer_class<T_Types...>;
		};

		template<class ...T_Tuple_types, class ...T_Types>
		struct S_Move_Template<tuple_t<T_Tuple_types...>, T_Types...>
		{
			using type = T_Outer_class<T_Tuple_types..., T_Types...>;
		};

		template<class ...T_Head, class T, class ...T_Tail, class ...T_Types>
		struct S_Move_Template<tuple_tp<tuple_t<T_Head...>, T, tuple_t<T_Tail...>>, T_Types...>
		{
			using type = T_Outer_class<T_Head... , T , T_Tail... ,T_Types...>;
		};

		template<class ...T_Head, class ...T_Tail, class ...T_Types>
		struct S_Move_Template<tuple_tp<tuple_t<T_Head...>, invalid_t, tuple_t<T_Tail...>>, T_Types...>
		{
			using type = T_Outer_class<T_Head..., T_Tail..., T_Types...>;
		};
	public:
		using type =typename S_Move_Template<T_Types...>::type;

	};
}