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

	template<class ..._Types>
	struct Tuple_tp;

	template<auto ..._Value>
	struct Tuple_v;

	template<class T_Head, auto _Value, class T_Tail>
	struct Tuple_vp;

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

	template<int _Index, class T_Tuple>
	struct I_Element;

	template<class T_Tuple_t>
	struct I_Remove;

	template<class T>
	struct Tuple_vp_To_tp;

	template<class T>
	struct Tuple_tp_To_vp;

	template<class T>
	struct Tuple_vp_To_tp;
	template<class T_Tuple_t, template<class...>class T_Action>
	struct S_Tuple_Action;

	template<class ..._Types>
	struct _Create_Tuple_Pointer;

}