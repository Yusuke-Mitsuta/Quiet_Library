#pragma once
#include<tuple>
#include<optional>
template<int _Index, class _Tuple, bool overflowFg = 
	(_Index >= std::tuple_size_v<_Tuple>) ||(_Index<0)>
struct tuple_element_overflow
{
	using type = std::tuple_element_t<_Index, _Tuple>;
};

template<int _Index, class _Tuple>
struct tuple_element_overflow<_Index, _Tuple, true>
{
	using type = std::nullopt_t;
};
template<int _Index, class _Tuple>
using tuple_element_t_overflow = tuple_element_overflow<_Index, _Tuple>::type;

template<template<class...>class _To,class ..._Flom>
struct IS_Move_Template_Type
{
	template<class _ToInnerType,class ..._Flom>
	struct S_Move_Template_Type;

	template<class ..._ToInnerType,class ..._FlomInnerType, class ..._Flom>
	struct S_Move_Template_Type<std::tuple<_ToInnerType...>,std::tuple<_FlomInnerType...>,_Flom...>
	{
		using Type = S_Move_Template_Type<std::tuple<_ToInnerType..., _FlomInnerType...>, _Flom...>::Type;
	};

	template<class ..._ToInnerType, class ..._FlomInnerType>
	struct S_Move_Template_Type<std::tuple<_ToInnerType...>, std::tuple<_FlomInnerType...>>
	{
		using Type = _To<_ToInnerType...,_FlomInnerType...>;
	};

	using Type = S_Move_Template_Type<std::tuple<>, _Flom...>::Type;
};

