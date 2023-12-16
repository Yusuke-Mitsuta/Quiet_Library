#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{

	//仕様
	//[T_Tuple]の中身を[T_Outer_class]のテンプレートにセットする
	//[T_Tuple]がtupleでない場合その型のまま実行される
	//
	//テンプレート
	//[T_Tuple]::中身を展開するTuple
	//[T_Outer_class]::展開した中身とそれに続く型[T_Types...]をセットする
	//[T_Types...]::展開した中身に続いて設定する型
	//
	//補足
	//[T_Tuple<types...>]->[T_Outer_class<types... , T_Types...>]とする
	template<template<class...>class T_Outer_class,class ...T_Types>
	struct I_Expand_Set
	{
		template<class ...T_Types>
		struct S_Expand_Set
		{
			using type = T_Outer_class<T_Types...>;
		};

		template<class ...T_Tuple_types, class ...T_Types>
		struct S_Expand_Set<tuple_t<T_Tuple_types...>, T_Types...>
		{
			using type = T_Outer_class<T_Tuple_types..., T_Types...>;
		};

		template<class ...T_Head, class T, class ...T_Tail, class ...T_Types>
		struct S_Expand_Set<tuple_tp<tuple_t<T_Head...>, T, tuple_t<T_Tail...>>, T_Types...>
		{
			using type = T_Outer_class<T_Head... , T , T_Tail... ,T_Types...>;
		};

		template<class ...T_Head, class ...T_Tail, class ...T_Types>
		struct S_Expand_Set<tuple_tp<tuple_t<T_Head...>, invalid_t, tuple_t<T_Tail...>>, T_Types...>
		{
			using type = T_Outer_class<T_Head..., T_Tail..., T_Types...>;
		};

		using type =typename S_Expand_Set<T_Types...>::type;

	};
}