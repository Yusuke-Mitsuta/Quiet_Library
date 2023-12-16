#pragma once

#include"Invalid.h"


//仕様
//[is<class>]の条件を初めて満たす値を探す
template<template<class>class is,class ...T_Chack_Ts>
struct select_type
{
	template<class ...T_Chack_Ts>
	struct S_select_type
	{
		using type = invalid_t;
	};

	template<class T_Front_Chack_T,class ...T_Chack_Ts>
		requires (is<T_Front_Chack_T>::value)
	struct S_select_type<T_Front_Chack_T, T_Chack_Ts...>
	{
		using type= T_Front_Chack_T;
	};

	template<class T_Front_Chack_T,class ...T_Chack_Ts>
		requires (!is<T_Front_Chack_T>::value)
	struct S_select_type<T_Front_Chack_T,T_Chack_Ts...>
	{
		using type = S_select_type<T_Chack_Ts...>::type;
	};

	using type = S_select_type<T_Chack_Ts...>::type;

};

//仕様
//[is<class>]の条件を初めて満たす値を探す
template<template<class>class is, class ...T_Chack_Ts>
using select_type_t = select_type<is, T_Chack_Ts...>::type;