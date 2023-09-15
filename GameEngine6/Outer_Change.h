#pragma once

template<template<class...>class T_New_Outer,class T_Old>
struct S_Outer_Change;

template<template<class...>class T_New_Outer, template<class...>class T_Old_Outer, class ...T_Old_Inner>
struct S_Outer_Change<T_New_Outer,T_Old_Outer<T_Old_Inner...>>
{
	using Type = typename T_New_Outer<T_Old_Inner...>;
};

//仕様
//[T_Old < T_Old_Inner_Types... >]テンプレートクラスを[T_New_Outer  <T_Old_Inner_Types... >]に移動させる
template<template<class...>class T_New_Outer, class T_Old>
using U_Change_Outer = typename S_Outer_Change<T_New_Outer, T_Old>::Type;
