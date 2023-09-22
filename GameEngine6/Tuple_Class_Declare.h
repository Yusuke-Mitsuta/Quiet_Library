#pragma once

#include<optional>

#include"Tuple_Concept.h"

template<auto t_Value>
struct integral_constant;

namespace N_Tuple
{

	template<class ...T_Types>
	struct S_Parameter;

	struct Tuple_p;

	template<class ...T_Head_Type>
	struct Head_t;

	template<auto ...t_Head_Value>
	struct Head_v;

	template<class ...T_Tail_Types>
	struct Tail_t;

	template<auto ...t_Tail_Value>
	struct Tail_v;

	template<class ...T_Types>
	struct Tuple_t;

	template<same_as_template_type<Head_t> T_Head, class T, same_as_template_type<Tail_t> T_Tail>
	struct Tuple_tp;

	template<auto ..._Value>
	struct Tuple_v;

	template<same_as_template_value<Head_v> T_Head,auto _value, same_as_template_value<Tail_v> T_Tail>
	struct Tuple_vp;

	template<class T_Tuple_p>
	struct I_Remove_Pointer;

	template<class T_Tuple_p>
	struct I_Create_Pointer;

	template<class T_Tuple>
	struct _Control_p;

	template<same_as_template_type<Head_t> T_Head, class T, same_as_template_type<Tail_t> T_Tail>
	struct Control_tp;

	template<same_as_template_value<Head_v> T_Head, auto _Value, same_as_template_value<Tail_v> T_Tail>
	struct Control_vp;

	template<class T_Tuple_t>
	struct I_Next;

	template<class T_Tuple_t>
	struct I_Prev;

	template<int t_Point, class T_Tuple_t>
	struct I_Select;

	template<size_t _Index, class ...T_Types>
	struct I_Element;

	template<class T_Tuple_t>
	struct I_Remove;

	template<class T_Tuple_t>
	struct I_Reverse;

	template<class T_Base_Tuple, class T_Insert_Tuple>
	struct I_Insert;

	template<class T_Base_Tuple, class T_Merge_Tuple>
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

	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, bool t_Action_break, template<class...>class T_Action, class T_Tuple, class ...T_Types>
	struct S_Action_Tuple;

	template<bool t_Action_Type_Tuple_p, bool t_Action_Type_Tuple_t, int Select_Point, template<class...>class T_Action, class T_Tuple, class ...T_Types>
	struct S_Action_Tuple_Helper;


	template<template<class...>class T_Action, class T_Tuple, int t_Action_Tuple_Select_Point = -1>
	using S_Action_Tuple_tp = S_Action_Tuple_Helper<true, true,t_Action_Tuple_Select_Point, T_Action, T_Tuple>;

	template<template<class...>class T_Action, class T_Tuple>
	using S_Action_Tuple_t = S_Action_Tuple_Helper<false, true, -1, T_Action, T_Tuple>;

	template<template<class...>class T_Action, class T_Tuple, int t_Action_Tuple_Select_Point = -1>
	using S_Action_Tuple_vp = S_Action_Tuple_Helper<true, false, t_Action_Tuple_Select_Point, T_Action, T_Tuple>;

	template<template<class...>class T_Action, class T_Tuple>
	using S_Action_Tuple_v = S_Action_Tuple_Helper<false, false, -1, T_Action, T_Tuple>;

}