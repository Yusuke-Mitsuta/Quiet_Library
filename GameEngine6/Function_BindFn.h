#pragma once
#include<tuple>
#include<functional>
#include<optional>
#include"Concept.h"
#include"main.h"
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"


//template<class T_Fn, class ...T_Args>
//class Function;

namespace N_Function
{
	template<class ...T_Args>
	struct IS_BindFn
	{
		template<class ...T_Args>
		struct S_BindFn
		{
			using Type = S_BindFn;
			using FnType = std::tuple<T_Args...>;
			using Judge = std::false_type;
		};

		template<class T_Fn,class ...T_Args>
		struct S_BindFn<std::tuple<T_Fn,T_Args...>>
		{
			using Type = S_BindFn<T_Fn,T_Args...>::Type;
		};

		template<class T_CName, class T_RType, class ...T_Args, class ...T_SetArgs>
			requires tuple_back_part_convertible_to<std::tuple<T_SetArgs...>, std::tuple<T_Args...>>
		struct S_BindFn<T_RType(T_CName::*)(T_Args...), T_SetArgs...>
		{
			using Type = S_BindFn;
			using FnType =std::tuple<T_RType(T_CName::*)(T_Args...), T_SetArgs...>;
			using Judge = std::true_type;
		};

		template<template<class...> class T_Function ,class T_CName, class T_RType, class ...T_Args, class ...T_DefaultSetArgs, class ...T_SetArgs>
			requires tuple_back_part_convertible_to<std::tuple<T_SetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>
		struct S_BindFn<T_Function<T_RType(T_CName::*)(T_Args...), T_DefaultSetArgs...>, T_SetArgs...>
		{
			using Type = S_BindFn;
			using FnType= std::tuple<T_RType(T_CName::*)(T_Args...), T_SetArgs..., T_DefaultSetArgs...>;
			using Judge = std::true_type;

		};

		using Type = S_BindFn<typename IS_TupleUnzip<T_Args...>::Type>::Type;

	};

};

