#pragma once


//仕様
//[T_Action::type]の結果を判定し、条件を満たすなら、
// [T_Action]のテンプレートを[T_Action::type]結果と入れ替え、再度判定を実施する。
// 条件を満たさない場合は、結果を出力する
//
//テンプレート
//[T_Action]::条件が[false]になるまで繰り返すアクション
//[T_is<...>]::繰り返すか判定する条件
//[T_is_Add_Types...]::[T_is<...>]の判定に追加で設定する型
//
//補足
//[T_Action=T_Action_Outer< ... >]
// [T_is< T_Action::type , T_is_Add_Types...>::value]が[true]であれば、
// [T_Action::type] → [T_Action_Outer< T_Action::type >::type]に変更し、再度判定を行い[falseになるまで続ける]
template<class T_Action, template<class...>class T_is, class ...T_is_Add_Types>
	requires requires
{
	typename T_is<typename T_Action::type, T_is_Add_Types...>::value;
}
struct while_type
{

	//仕様
	//繰り返しの終了
	template<class T_Action=T_Action,
		class T_Action_Type= typename T_Action::type,
		bool is_break_chack = T_is<T_Action_Type, T_Set_is_Types...>::value>
	struct S_While
	{
		using type = T_Action_Type;
	};

	//仕様
	// [T_Action<T_Template_Types...>::type]→ [T_Action< T_Action<T_Template_Types...>::type >::type]に変更し繰り返す
	template<template<class...>class T_Action,
		class ...T_Template_Types,
		class T_Action_Type>
	struct S_While<T_Action<T_Template_Types...>,T_Action_Type,true>
	{
		using type = S_While<T_Action<T_Action_Type>>::type;
	};

	using type = S_While<>::type;

};


//仕様
//[T_Action::type]の結果を判定し、条件を満たすなら、
// [T_Action]のテンプレートを[T_Action::type]結果と入れ替え、再度判定を実施する。
// 条件を満たさない場合は、結果を出力する
//
//テンプレート
//[T_Action]::条件が[false]になるまで繰り返すアクション
//[T_is<...>]::繰り返すか判定する条件
//[T_is_Add_Types...]::[T_is<...>]の判定に追加で設定する型
//
//補足
//[T_Action=T_Action_Outer< ... >]
// [T_is< T_Action::type , T_is_Add_Types...>::value]が[true]であれば、
// [T_Action::type] → [T_Action_Outer< T_Action::type >::type]に変更し、再度判定を行い[falseになるまで続ける]
template<class T_Action, template<class...>class T_is, class ...T_is_Add_Types>
	requires requires
{
	typename T_is<typename T_Action::type, T_is_Add_Types...>::value;
}
using while_type_t = typename while_type<T_Action, T_is, T_is_Add_Types...>::type;
