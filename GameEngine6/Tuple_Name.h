#pragma once

#include"Constexpr_String.h"
#include"Tuple_Declare.h"

template<N_Constexpr::String t_name, N_Tuple::is_Tuple T_Tuple>
struct tuple_name :
	T_Tuple
{
	static constexpr auto name = t_name;
	using remove_name = T_Tuple;
};

template<N_Constexpr::String t_name,auto ...t_value>
struct tuple_name_v :
	tuple_name<t_name,tuple_v<t_value...>>
{};

template<N_Constexpr::String t_name, class ...T_Types>
struct tuple_name_t :
	tuple_name<t_name, tuple_t<T_Types...>>
{};