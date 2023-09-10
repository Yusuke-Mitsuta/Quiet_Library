#pragma once

#include<type_traits>
#include"SwapType.h"


template<class ...T_Parameters>
struct S_Parameter;

template<auto ...t_Parameters>
struct S_Parameter_Value;

template<class T_Parameter>
struct IS_Parameter_Class_Change_Value;

template<auto t_Value>
struct integral_constant;

//仕様
//パラメータパック[T_Parameters...]から[_Index]番目の型を取り出す
//
//template
//_Index::パラメータパックから取り出す型の番号
//T_Parameters...::型のパラメータパック
//
//補足
//範囲外の場合[std::nullopt_t]が返る
template<int _Index,class ...T_Parameters>
struct IS_Parameter_Element
{
	friend struct S_Parameter<T_Parameters...>;

	template<int _Index, class T_FlontParameter, class ...T_Parameters>
	struct S_Parameter_Element
	{
		using Type = S_Parameter_Element<_Index - 1, T_Parameters...>::Type;
	};

	template<class T_FlontParameter, class ...T_Parameters>
	struct S_Parameter_Element<0,T_FlontParameter,T_Parameters...>
	{
		using Type = T_FlontParameter;
	};

	template<int _Index>
	struct S_Parameter_Element<_Index,std::nullopt_t>
	{
		using Type = std::nullopt_t;
	};
	
	template<class ...T_Parameters>
	struct S_Parameter_Expand
	{
		using Type= S_Parameter_Element<_Index, T_Parameters..., std::nullopt_t>::Type;
	};

	//template<class ...T_Parameters>
	//struct S_Parameter_Expand<S_Parameter<T_Parameters...>>
	//{
	//	using Type = S_Parameter_Element<_Index, T_Parameters..., std::nullopt_t>::Type;
	//};

public:

	using Type = S_Parameter_Expand<T_Parameters...>::Type;
};

template<int _Index, class ...T_Parameters>
using U_Element_t = IS_Parameter_Element<_Index, T_Parameters...>::Type;

//仕様
//パラメータパック[t_Parameters...]から[_Index]番目の変数を取り出す
//
//template
//_Index::パラメータパックから取り出す型の番号
//t_Parameters...::変数のパラメータパック
//補足
//範囲外の場合[std::nullopt]が返る
template<size_t _Index, same_as_template_value<S_Parameter_Value> T_Parameter_Value>
struct S_Parameter_Element_Variable;

template<size_t _Index, auto ...t_Parameter_Value>
struct S_Parameter_Element_Variable<_Index,S_Parameter_Value<t_Parameter_Value...>>
{
	using Type = U_Element_t<_Index,typename S_Parameter_Value<t_Parameter_Value...>::Parameter_Type>;

	template<class T>
	struct S_OverFlow_Check
	{
		using Type = T;
	};

	template<>
	struct S_OverFlow_Check<std::nullopt_t>
	{
		using Type = integral_constant<0>;
	};

	static constexpr auto value = S_OverFlow_Check<Type>::Type::value;

};

template<size_t _Index, auto ...t_Parameters>
static constexpr auto Element_v()
{
	return S_Parameter_Element_Variable<_Index, S_Parameter_Value<t_Parameters...>>::value;
}

template<size_t _Index, same_as_template_value<S_Parameter_Value> T_Parameters>
static constexpr auto Element_v()
{
	return S_Parameter_Element_Variable<_Index, T_Parameters>::value;
}

template<size_t _Index, auto ...t_Parameters>
static constexpr auto U_Element_v = Element_v<_Index, t_Parameters...>();

template<size_t _Index, same_as_template_value<S_Parameter_Value> T_Parameters>
static constexpr auto U_Element_vp = Element_v<_Index, T_Parameters>();