#pragma once
#include<tuple>
#include"Concept.h"

template<class T_Tuple, class T_UnzipTuple>
struct S_TupleUnzip
{
	using Type = T_UnzipTuple;
};

template<class t_FlontTuple, class ...T_Tuple, class ...T_UnzipTuple>
struct S_TupleUnzip<std::tuple<t_FlontTuple, T_Tuple...>,std::tuple<T_UnzipTuple...>>
{
	using Type = S_TupleUnzip<std::tuple<T_Tuple...>, std::tuple<T_UnzipTuple..., t_FlontTuple>>::Type;
};

template<class ...t_FlontTuple, class ...T_Tuple, class ...T_UnzipTuple>
struct S_TupleUnzip<std::tuple<std::tuple<t_FlontTuple...>, T_Tuple...>, std::tuple<T_UnzipTuple...>>
{
	using Type = S_TupleUnzip<std::tuple<t_FlontTuple...,T_Tuple...>, std::tuple<T_UnzipTuple...>>::Type;
};

template<class T_Tuple>
struct I_S_TupleUnzip
{
	using Type = S_TupleUnzip<T_Tuple, std::tuple<>>::Type;
};