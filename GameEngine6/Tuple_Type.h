#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Control.h"

#include<optional>

template<template<class...>class _Ty1, class ..._Ty1_Types>
struct is_same_as_template_type<_Ty1<_Ty1_Types...>,tuple_tp> :
	std::false_type {};

template<template<class...>class _Ty1, class ..._Ty1_Types>
	requires (sizeof...(_Ty1_Types)==3)
struct is_same_as_template_type<_Ty1<_Ty1_Types...>,tuple_tp> :
	std::bool_constant< std::same_as<_Ty1<_Ty1_Types...>, tuple_tp<_Ty1_Types...>>> {};


template<same_as_template_type<tuple_t> T_Head, class T, same_as_template_type<tuple_t> T_Tail>
struct tuple_tp :
	N_Tuple::Control_tp<T_Head, T, T_Tail> {};

template<class ..._Types>
struct tuple_t :
	N_Tuple::Control_tp<tuple_t<>, std::nullopt_t, tuple_t<>> {};

template<class T_Flont_Type, class ...T_Types>
struct tuple_t<T_Flont_Type, T_Types...> :
	N_Tuple::Control_tp<tuple_t<>, T_Flont_Type, tuple_t<T_Types...>> {};


namespace std
{
	template<class ...T_Type>
	struct tuple_size<tuple_tp<T_Type...>> :
		integral_constant<size_t, N_Tuple::S_Parameter<
		tuple_tp<T_Type...>>::Size> 
	{
		static constexpr size_t value =
			N_Tuple::S_Parameter<tuple_tp<T_Type...>>::Size;
	};

	template<class ...T_Type>
	struct tuple_size<tuple_t<T_Type...>> :
		integral_constant<size_t, sizeof...(T_Type)>
	{
		static constexpr size_t value = sizeof...(T_Type);
	};
}

