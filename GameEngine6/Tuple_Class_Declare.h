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
	struct _p;

	template<auto ..._Value>
	struct _v;

	template<class T_Head, auto _Value, class T_Tail>
	struct _p_v;

	template<class ..._Types>
	struct _Control;

	template<class ...T_Head_Type>
	struct _Head;

	template<auto ...t_Head_Value>
	struct _Head_v;

	template<class ...T_Tail_Types>
	struct _Tail;

	template<auto ...t_Tail_Value>
	struct _Tail_v;

	template<class T_Tuple_t>
	struct _Next;

	template<class T_Tuple_t>
	struct _Prev;

	template<int t_Point, is_Element<t_Point> T_Tuple_t>
	struct Pointer;

	template<class T_Tuple_t>
	struct _Remove;


	template<class T>
	struct To_Tuple_p_v;

}