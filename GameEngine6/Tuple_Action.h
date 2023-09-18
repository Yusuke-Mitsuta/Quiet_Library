#pragma once

#include"Tuple_Class_Declare.h"




namespace N_Tuple
{

	template<template<class...>class T_Action, class ...T_Types>
	struct S_Tuple_Action
	{
		using Type = typename T_Action<T_Types...>::Type;
	};

	template<template<class...>class T_Action, class T_Head,class T,class T_Tail>
	struct S_Tuple_Action<T_Action,Tuple_tp<T_Head,T,T_Tail>>
	{
		using Type = typename T_Action<Tuple_tp<T_Head, T, T_Tail>>::Type;
	};

	template<template<class...>class T_Action, class ...T_Types>
	struct S_Tuple_Action<T_Action,Tuple_t<T_Types...>>
	{
		using Type = typename T_Action<Tuple_t<T_Types...>>::Type;
	};

	template<template<class...>class T_Action,class T_Head_v, auto value, class T_Tail_v>
	struct S_Tuple_Action<T_Action,Tuple_vp<T_Head_v,
		value, T_Tail_v>>
	{
		using Change_tp = typename Tuple_v_To_t< Tuple_vp<T_Head_v, value, T_Tail_v>>::Type;
		using Action = typename T_Action<Change_tp>::Type;
		using Change_vp = typename Tuple_t_To_v<Action>::Type;
		using Type = Change_vp;
	};

	template<template<class...>class T_Action,auto ...value>
	struct S_Tuple_Action<T_Action,Tuple_v<value...>>
	{
		using Change_tp = typename Tuple_v_To_t<Tuple_v<value...>>::Type;
		using Action = typename T_Action<Change_tp>::Type;
		using Change_vp = typename Tuple_t_To_v<Action>::Type;
		using Type = Change_vp;
	};

}