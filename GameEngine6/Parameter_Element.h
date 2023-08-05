#pragma once

#include"SwapType.h"

template<class ...T_Parameters>
struct S_Parameter;


//仕様
//パラメータパック[T_Parameters...]から[_Index]番目の型を取り出す
//
//template
//_Index::パラメータパックから取り出す型の番号
//T_Parameters...::型のパラメータパック
template<size_t _Index,class ...T_Parameters>
struct IS_Parameter_Element_Type
{
	friend struct S_Parameter<T_Parameters...>;

	template<size_t _Index, class T_FlontParameter, class ...T_Parameters>
	struct S_Parameter_Element_Type :
		public S_Parameter_Element_Type<_Index - 1, T_Parameters...>
	{
		using Next = S_Parameter_Element_Type<_Index-1,T_Parameters...>;


		using Type = Next::Type;

		T_FlontParameter parameter;

		template<class MT_Flont,class ...TP>
		constexpr S_Parameter_Element_Type(MT_Flont flont, TP... set_Parameters) :
			parameter(flont), Next(set_Parameters...) {}

		constexpr auto Get(int& number, auto regression)
		{
			if (number)
			{
				number -= 1;
				return Next::Get(number,regression);
			}
			return parameter;
		}


	};

	template<size_t _Index,template<class...>class T_Parameter, class ...T_Lapping_Parameter, class ...T_Parameters>
		//requires same_as_template_class<T_Parameter<T_Lapping_Parameter...>, S_Parameter>
	struct S_Parameter_Element_Type<_Index, T_Parameter<T_Lapping_Parameter...>,
		T_Parameters...> :
		public S_Parameter_Element_Type<_Index - 1, T_Parameters...>
	{
		using Next = S_Parameter_Element_Type<_Index - 1, T_Parameters...>;

		using Type =  S_Parameter_Element_Type<_Index, T_Lapping_Parameter..., T_Parameters...>::Type;

		T_Parameter<T_Lapping_Parameter...> parameters;

		template<class MT_Flont, class ...TP>
		constexpr S_Parameter_Element_Type(MT_Flont set_lapping_Parameters, TP... set_Parameters) :
			parameters(set_lapping_Parameters), Next(set_Parameters...) {}

		template<class ...TP>
		constexpr S_Parameter_Element_Type(T_Lapping_Parameter... set_lapping_Parameters, TP... set_Parameters) :
			parameters(set_lapping_Parameters...), Next(set_Parameters...) {}

		constexpr auto Get(int& number,auto regression)
		{
			
		}

	};

	template<template<class...>class T_Parameter, class ...T_Lapping_Parameter, class ...T_Parameters>
		//requires same_as_template_class<T_Parameter<T_Lapping_Parameter...>, S_Parameter>
	struct S_Parameter_Element_Type<0,T_Parameter<T_Lapping_Parameter...>,
		T_Parameters...>
	{

		using Type = S_Parameter_Element_Type<0, T_Lapping_Parameter...,T_Parameters...>::Type;

		T_Parameter<T_Lapping_Parameter...> parameters;

		constexpr S_Parameter_Element_Type(T_Parameter<T_Lapping_Parameter...> set_lapping_Parameters) :
			parameters(set_lapping_Parameters) {}

		constexpr S_Parameter_Element_Type(T_Lapping_Parameter... set_lapping_Parameters) :
			parameters(set_lapping_Parameters...) {}

		constexpr auto Get(int& number, auto* regression)
		{

		}

	};

	template<class T_FlontParameter, class ...T_Parameters>
		requires (!same_as_template_class<T_FlontParameter,S_Parameter>)
	struct S_Parameter_Element_Type<0,T_FlontParameter,T_Parameters...>
	{
		using Type = T_FlontParameter;

		Type parameter;

		S_Parameter_Element_Type(T_FlontParameter set_Parameter) :
			parameter(set_Parameter) {}

		constexpr auto Get(int& number, same_as<std::nullptr_t> auto regression)
		{

			if (number)//(number!=0 && _Index!=0)
			{
				return nullptr;
			}

			return parameter;
		}

		constexpr auto Get(int& number,not_same_as<std::nullptr_t> auto regression)
		{

			if (number)//(number!=0 && _Index!=0)
			{
				number -= 1;
				return regression->Get(number,nullptr);
			}

			return parameter;
		}

	};
	using Next= S_Parameter_Element_Type<_Index, T_Parameters...>;
public:

	using Type = S_Parameter_Element_Type<_Index, T_Parameters...>::Type;

};

template<size_t _Index, class ...T_Parameters>
	//requires (_Index <= sizeof...(T_Parameters))
using S_Parameter_Element_t = IS_Parameter_Element_Type<_Index, T_Parameters...>::Type;

template<class ...T_Parameters>
struct S_Parameter
{
public:

	IS_Parameter_Element_Type<sizeof...(T_Parameters) - 1, T_Parameters...>::Next parameters;

	static constexpr size_t Size = sizeof...(T_Parameters);

	template<class ...MT_Parameters>
	constexpr S_Parameter(MT_Parameters... set_Parameters) :
		parameters(set_Parameters...) {}

	constexpr auto operator[](int number)
	{
		return parameters.Get(number, nullptr);

	}
};

template<class ...MT_Parameters>
S_Parameter(MT_Parameters... set_Parameters) -> S_Parameter<MT_Parameters...>;

template<auto t_Variable>
struct S_Variablea
{
	static constexpr auto Variable = t_Variable;
};

//仕様
//パラメータパック[t_Parameters...]から[_Index]番目の変数を取り出す
//
//template
//_Index::パラメータパックから取り出す型の番号
//t_Parameters...::変数のパラメータパック
template<size_t _Index, auto t_FlontParameter, auto ...t_Parameters>
	requires (_Index <= sizeof...(t_Parameters))
struct S_Parameter_Element_Variable
{
	using Type = S_Parameter_Element_Variable<_Index - 1, t_Parameters...>;

	static constexpr auto Variable = Type::Variable;
};

template<auto t_FlontParameter, auto ...t_Parameters>
struct S_Parameter_Element_Variable<0,t_FlontParameter,t_Parameters...>
{
	static constexpr auto Variable = t_FlontParameter;
};
template<size_t _Index, auto ...t_Parameters>
	requires (_Index <= sizeof...(t_Parameters))
static constexpr auto S_Parameter_Element_v = S_Parameter_Element_Variable<_Index, t_Parameters...>::Variable;
