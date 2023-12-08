#pragma once
#include"Constexpr_String.h"
#include"Parts_Search_Inner.h"
#include"Tuple.h"

template<N_Constexpr::String t_Parts_Name, class T>
struct Parts;

template<N_Constexpr::String t_Parts_Name,size_t t_max_search_num, class ...T_Search_list>
struct I_Parts_Search
{

	template<class T_Result , class ...T_Search_list>
	struct S_Parts_Search
	{
		using type = T_Result;
	};

	template<class T_Result,class T_flont_type,class ...T_Search_list>
		requires (T_Result::size < t_max_search_num)
	struct S_Parts_Search<T_Result,T_flont_type,T_Search_list...>
	{
		using type = S_Parts_Search<T_Result,T_Search_list...>::type;
	};

	template<class ...T_Result,class T, class ...T_Search_list>
		requires ((sizeof...(T_Result) < t_max_search_num) &&
				 (1 != t_max_search_num))
	struct S_Parts_Search<tuple_t<T_Result...>,Parts<t_Parts_Name,T>,T_Search_list...>
	{
		using type = S_Parts_Search<tuple_t<T_Result..., Parts<t_Parts_Name, T>>, T_Search_list...>::type;
	};

	template<class T_Result, class T, class ...T_Search_list>
		requires (1 == t_max_search_num)
	struct S_Parts_Search<T_Result, Parts<t_Parts_Name, T>, T_Search_list...>
	{
		using type = Parts<t_Parts_Name, T>;
	};

	using type = S_Parts_Search<U_Judge_t<tuple_t<>, (t_max_search_num != 1)>, T_Search_list...>::type;
};

template<N_Constexpr::String t_Parts_Name, class ...T_Search_list>
using U_Parts_Search = typename I_Parts_Search<t_Parts_Name, 1, T_Search_list...>::type;

template<N_Constexpr::String t_Parts_Name, size_t t_max_search_num, class ...T_Search_list>
using U_Parts_Search_Multi = typename I_Parts_Search<t_Parts_Name, t_max_search_num, T_Search_list...>::type;
