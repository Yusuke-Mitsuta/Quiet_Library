/*!
 * Move_Template.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once
namespace quiet
{
	template<template<class...>class T_New_Outer, class T_Old>
	static constexpr auto Move_Template();

	template<template<class...>class T_New_Outer, class T_Old>
	struct S_Move_Template;

	template<template<class...>class T_New_Outer, template<class...>class T_Old_Outer, class ...T_Old_Inner>
	struct S_Move_Template<T_New_Outer, T_Old_Outer<T_Old_Inner...>>
	{
		using Type = T_New_Outer<T_Old_Inner...>;
	};

	//仕様
	//[T_Old < T_Old_Inner_Types... >]テンプレートの型をを[T_New_Outer  <T_Old_Inner_Types... >]に移動させる
	template<template<class...>class T_New_Outer, class T_Old>
	using U_Move_Template = typename S_Move_Template<T_New_Outer, T_Old>::Type;

	template<template<class...>class T_New_Outer, class T_Old>
	constexpr auto Move_Template()
	{

	}

}