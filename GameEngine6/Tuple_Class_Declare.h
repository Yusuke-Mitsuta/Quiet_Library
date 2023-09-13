#pragma once

#include<optional>

template<auto t_Value>
struct integral_constant;

namespace N_Tuple
{
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

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct _Control<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>;

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct _t<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>;

	template<>
	struct _Control<_Head<>, _Tail<>>;

	template<>
	struct _t<>;

	template<class T_Tuple_t>
	struct _Next;

	template<int t_Point, class T_Tuple_t>
	struct I_Pointer;

	template<class T_Tuple_t>
	struct _Prev;

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct _Prev<_t<_Head< T_Head_Types...>, T, _Tail<T_Tail_Types...>>>;

	template<class T_Tuple_t>
	struct _Remove;

	template<auto value>
	struct Tulple_v_To_Tuple_T;

	template<class Value>
	struct Tulple_V_To_Tuple_T;
}
