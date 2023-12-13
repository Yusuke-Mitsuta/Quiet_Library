#pragma once

#include<optional>

#include"Tuple_Concept.h"

#include"Tuple_ID.h"

#include"Constexpr_String.h"

template<auto t_Value>
struct integral_constant;

template<class ...T_Types>
struct tuple_t;

template<N_Tuple::same_as_tuple_t T_Head, class T, N_Tuple::same_as_tuple_t T_Tail>
struct tuple_tp;

template<auto ..._Value>
struct tuple_v;

template<N_Tuple::same_as_tuple_v T_Head, auto _value, N_Tuple::same_as_tuple_v T_Tail>
struct tuple_vp;

namespace N_Tuple
{

	template<class ...T_Types>
	struct S_Parameter;

	struct Tuple_p;

	template<class T_Tuple_p>
	struct I_Remove_Pointer;

	template<class T_Tuple_p>
	struct I_Create_Pointer;

	template<class T_Tuple>
	struct _Control_p;

	template<same_as_template_type<tuple_t> T_Head, class T, same_as_template_type<tuple_t> T_Tail>
	struct Control_tp;

	template<same_as_template_value<tuple_v> T_Head, auto _Value, same_as_template_value<tuple_v> T_Tail>
	struct Control_vp;

	template<class T_Tuple_t>
	struct I_Next;

	template<class T_Tuple_t>
	struct I_Prev;

	template<int t_Point, class T_Tuple_t>
	struct I_Select;

	template<size_t _Index, class ...T_Types>
	struct I_Element;

	template<class T_Tuple_p, size_t t_Remove_Point = S_Parameter<T_Tuple_p>::Size_Head>
	struct I_Remove;

	template<class T_Tuple_t>
	struct I_Reverse;

	template<class T_Base_Tuple, class T_Insert_Tuple, size_t t_Insert_Point = S_Parameter<T_Base_Tuple>::Size_Head>
	struct I_Insert;

	template<class T_Base_Tuple, class T_Merge>
	struct I_Merge;

	template<class T_Tuple_p, class T_Change, size_t t_Change_Point = S_Parameter<T_Tuple_p>::Size_Head>
	struct I_Change;

	template<class T_Tuple, size_t t_Swap_Num_1, size_t t_Swap_Num_2 = S_Parameter<T_Tuple>::Size_Head>
		requires is_Element<T_Tuple, t_Swap_Num_1>&& is_Element<T_Tuple, t_Swap_Num_2>
	struct I_Swap;

	template<class T_Tuple, size_t t_Point_1, size_t t_Point_2>
		requires is_Element<T_Tuple, t_Point_1>&& is_Element<T_Tuple, t_Point_2>
	struct I_Range;

	template<class T_Tuple, class T_Extract_Number>
	struct I_Extract;

	template<class T>
	struct Tuple_v_To_t;

	template<class T>
	struct Tuple_t_To_v;

	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Tuple>
	struct S_Action_Tuple;

	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t,template<class...>class T_Action, class T_Tuple, size_t t_Start_Point= S_Parameter<T_Tuple>::Size_Head>
	struct S_Action_Tuple_Helper;


	template<template<class...>class T_Action, class T_Tuple, size_t t_Start_Point = S_Parameter<T_Tuple>::Size_Head>
	using S_Action_Tuple_tp = S_Action_Tuple_Helper<true, true, T_Action, T_Tuple, t_Start_Point>;

	template<template<class...>class T_Action, class T_Tuple>
	using S_Action_Tuple_t = S_Action_Tuple_Helper<false, true, T_Action, T_Tuple>;

	template<template<class...>class T_Action, class T_Tuple,size_t t_Start_Point = S_Parameter<T_Tuple>::Size_Head>
	using S_Action_Tuple_vp = S_Action_Tuple_Helper<true, false, T_Action, T_Tuple, t_Start_Point>;

	template<template<class...>class T_Action, class T_Tuple>
	using S_Action_Tuple_v = S_Action_Tuple_Helper<false, false, T_Action, T_Tuple>;

	template<class T_Tuple_v,N_Constexpr::String t_operator, auto number>
	struct I_Tuple_Calculate;

	template<template<class...>class T_Outer_class,class ...T_Types>
	struct I_Expand_Set;

	template<size_t N>
	struct I_index_sequence;

	template<size_t N_1, size_t N_2>
	struct I_range_index_sequence;

}