#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{

	//仕様
	//[tuple_t]の各種Size、及び型を呼び出す
	template<class ...T_Types>
	struct S_Parameter
	{
		using T = std::tuple<T_Types...>;
		static constexpr size_t Size = sizeof...(T_Types);

	};

	template<template<class...>class T_Outer, class ...T_Types>
	struct S_Parameter<T_Outer<T_Types...>>
	{
		static constexpr size_t Size_Head = 0;
		static constexpr size_t Size_Tail = 0;
		static constexpr size_t Size = sizeof...(T_Types);
	};

	template<template<auto...>class T_Outer,auto ...t_Value>
	struct S_Parameter<T_Outer<t_Value...>>
	{
		static constexpr size_t Size_Head = 0;
		static constexpr size_t Size_Tail = 0;
		static constexpr size_t Size = sizeof...(t_Value);
	};

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct S_Parameter<tuple_tp<tuple_t<T_Head_Types...>,T , tuple_t<T_Tail_Types...>>>
	{
		static constexpr size_t Size_Head = sizeof...(T_Head_Types);
		static constexpr size_t Size_Tail = sizeof...(T_Tail_Types);
		static constexpr size_t Size = Size_Head + Size_Tail + not_is_nullopt<T>;
		using Type = T;
	};

	template<auto ...t_Head_Value, auto _Value, auto ...t_Tail_Value>
	struct S_Parameter<tuple_vp<tuple_v<t_Head_Value...>, _Value, tuple_v<t_Tail_Value...>>>
	{
		static constexpr size_t Size_Head = sizeof...(t_Head_Value);
		static constexpr size_t Size_Tail = sizeof...(t_Tail_Value);
		static constexpr size_t Size = Size_Head + Size_Tail + not_is_nullopt<decltype(_Value)>;
		static constexpr auto value = _Value;
	};



}
