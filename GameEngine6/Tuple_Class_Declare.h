#pragma once

#include<optional>

#include"Tuple_Concept.h"

template<auto t_Value>
struct integral_constant;

namespace N_Tuple
{

	template<class ...T_Types>
	struct S_Parameter;


	template<class ...T_Types>
	struct Tuple_t;

	template<class ..._Types>
	struct Tuple_tp;

	template<auto ..._Value>
	struct Tuple_v;

	template<class T_Head, auto _Value, class T_Tail>
	struct Tuple_vp;

	template<class T_Tuple_p>
	struct I_Remove_Pointer;

	template<class T_Tuple_p>
	struct I_Create_Pointer;

	template<class T_Tuple>
	struct _Control;

	template<class T_Tuple_t>
	struct _Control_t;

	template<class T_Tuple_v>
	struct _Control_v;

	template<class ...T_Head_Type>
	struct _Head;

	template<auto ...t_Head_Value>
	struct _Head_v;

	template<class ...T_Tail_Types>
	struct _Tail;

	template<auto ...t_Tail_Value>
	struct _Tail_v;

	template<class T_Tuple_t>
	struct I_Next;

	template<class T_Tuple_t>
	struct I_Prev;

	template<int t_Point, class T_Tuple_t>
	struct I_Select;

	template<size_t _Index, class T_Tuple>
	struct I_Element;

	template<class T_Tuple_t>
	struct I_Remove;

	template<class T_Tuple_t>
	struct I_Reverse;

	template<class T_Base_Tuple, class T_Insert_Tuple>
	struct I_Insert;

	template<class T_Base_Tuple, class T_Merge_Tuple>
	struct I_Merge;

	template<class T_Tuple_p, class T_Change>
	struct I_Change;

	template<class T_Tuple, size_t t_Swap_Num_1, size_t t_Swap_Num_2>
		requires is_Element<T_Tuple,t_Swap_Num_1>&& is_Element<T_Tuple, t_Swap_Num_2>
	struct I_Swap;

	template<class T>
	struct Tuple_v_To_t;

	template<class T>
	struct Tuple_t_To_v;

	template<template<class...>class T_Action,class ...T_Types>
	struct S_Tuple_Action;

	template<class ..._Types>
	struct _Create_Tuple_Pointer;

}