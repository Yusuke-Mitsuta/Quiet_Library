#pragma once

#include<optional>

#include"Tuple_Concept.h"

template<auto t_Value>
struct integral_constant;

namespace N_Tuple
{

	template<class ...T_Types>
	struct S_Parameter;

	template<class ..._Types>
	struct _t;

	template<auto ..._Value>
	struct _v;

	template<class ..._Types>
	struct _Control;

	template<class ...T_Head_Type>
	struct _Head;

	template<class ...T_Tail_Types>
	struct _Tail;

	template<class T_Tuple_t>
	struct _Next;

	template<class T_Tuple_t>
	struct _Prev;

	template<int t_Point, is_Element<t_Point> T_Tuple_t>
	struct Pointer;

	template<class T_Tuple_t>
	struct _Remove;

	template<auto value>
	struct Tulple_v_To_Tuple_T;

	template<class Value>
	struct Tulple_V_To_Tuple_T;



}