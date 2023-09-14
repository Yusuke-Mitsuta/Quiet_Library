#pragma once

#include<tuple>
#include<optional>

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{

	//仕様
	//[Tuple_t]の各種Size、及び型を呼び出す
	template<class ...T_Types>
	struct S_Parameter
	{
	private:

		using tuple = std::tuple<T_Types...>;

	public:
		static constexpr size_t Size = sizeof...(T_Types);

		using Flnot = std::tuple_element_t<0, tuple>;
		using Back = std::tuple_element_t<Size - 1, tuple>;

		using This = Flnot;



		static constexpr size_t Size_Head = 0;
		static constexpr size_t Size_Tail = Size - 1;

	};

	template<>
	struct S_Parameter<> :
		public S_Parameter<std::nullopt_t>
	{
		static constexpr size_t Size = 0;
	};

	template<template<class...>class T_Tuple_Outer, class ...T_Types>
	struct S_Parameter<T_Tuple_Outer<T_Types...>> :
		public S_Parameter<T_Types...> {};

	template<template<class...>class T_Tuple_Outer>
	struct S_Parameter<T_Tuple_Outer<_Head<>,_Tail<>>> :
		public S_Parameter<> {};

	template<template<class...>class T_Tuple_Outer,class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct S_Parameter<T_Tuple_Outer<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
		:public S_Parameter<T_Head_Types..., T, T_Tail_Types...>
	{
		static constexpr size_t Size_Head = sizeof...(T_Head_Types);
		static constexpr size_t Size_Tail = sizeof...(T_Tail_Types);


		using Head = _Head<T_Head_Types...>;

		using Tail = _Tail<T_Tail_Types...>;

		using This = T;

	};

}
