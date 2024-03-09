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

	//仕様
	//[T_Tuple_Data]の中身を[T_Outer_class]のテンプレートにセットする
	//[T_Tuple_Data]がtupleでない場合その型のまま実行される
	//
	//テンプレート
	//[T_Tuple_Data]::中身を展開するTuple
	//[T_Outer_class]::展開した中身とそれに続く型[T_Leftover_Types...]をセットする
	//[T_Leftover_Types...]::展開した中身に続いて設定する型
	//
	//補足
	//[T_Tuple_Data<types...>]->[T_Outer_class<types... , T_Leftover_Types...>]とする
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