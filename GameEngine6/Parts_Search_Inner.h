#pragma once
#include"Constexpr_String.h"
#include"Tuple.h"

template<N_Constexpr::String t_Parts_Name, size_t t_max_search_num, class ...T_Search_list>
struct I_Parts_Search;

template<N_Constexpr::String t_Parts_Name, size_t t_max_search_num, class T_Ineer_Search>
struct I_Parts_Search_InnerType
{

	template<class T_Ineer_Search = T_Ineer_Search>
	struct S_Parts_Search_InnerType
	{
		using type = typename I_Parts_Search<t_Parts_Name, t_max_search_num, T_Ineer_Search>::type;
	};

	template<template<class...>class T_Outer, class ...T_Ineer_Search>
	struct S_Parts_Search_InnerType<T_Outer<T_Ineer_Search...>>
	{
		using type = typename I_Parts_Search<t_Parts_Name, t_max_search_num, T_Ineer_Search... >::type;
	};

	using type = S_Parts_Search_InnerType<>::type;

};

template<N_Constexpr::String t_Parts_Name, class ...T_Search_list>
using U_Parts_Search_InnerType = typename I_Parts_Search_InnerType<t_Parts_Name, 1, T_Search_list...>::type;

template<N_Constexpr::String t_Parts_Name, size_t t_max_search_num, class ...T_Search_list>
using U_Parts_Search_InnerType_Multi = typename I_Parts_Search_InnerType<t_Parts_Name, t_max_search_num, T_Search_list...>::type;
