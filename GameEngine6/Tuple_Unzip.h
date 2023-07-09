#pragma once
#include<tuple>
#include"Concept.h"

template<class ...T_Tuple>
struct IS_TupleUnzip
{
	using Type = IS_TupleUnzip<std::tuple<T_Tuple...>>::Type;

	static constexpr auto I_TupleUnzip(T_Tuple&... tuple)
	{
		return IS_TupleUnzip<std::tuple<T_Tuple...>>::TupleUnzip(tuple...);
	}
};

template<template<class...>class Base, class ...T_Tuple>
struct IS_TupleUnzip<Base<T_Tuple...>>
{
private:
	template<class T_Flont_Type,class ...T_Tuple>
	struct S_TupleUnzip
	{
		using Type = S_TupleUnzip<T_Tuple..., T_Flont_Type>::Type;

		static constexpr auto TupleUnzip(T_Flont_Type& flont, T_Tuple&... tuple)
		{
			return S_TupleUnzip<T_Tuple..., T_Flont_Type>::
				TupleUnzip(tuple...,flont);
		}
	};

	template<class ...T_TupleInside,class ...T_Tuple>
	struct S_TupleUnzip<std::tuple<T_TupleInside...>,T_Tuple...>
	{
		using Type = S_TupleUnzip<T_TupleInside...,T_Tuple...>::Type;

		static constexpr auto TupleUnzip(T_TupleInside&... flont_Tuple, T_Tuple&... tuple)
		{
			return S_TupleUnzip<T_TupleInside..., T_Tuple...>::
				TupleUnzip(flont_Tuple...,tuple...);
		}
	};

	template<class ...T_Tuple>
	struct S_TupleUnzip<End, T_Tuple...>
	{
		using Type = Base<T_Tuple...>;

		static constexpr Type TupleUnzip(End& nullopt, T_Tuple&... tuple)
		{
			return Type{tuple... };
		}
	};
	static constexpr auto TupleUnzip(T_Tuple&... tuple)
	{
		End a;
		return S_TupleUnzip<T_Tuple...,End>::TupleUnzip(tuple...,a);
	
	}

public:

	static constexpr auto I_TupleUnzip(Base<T_Tuple...>& tuple)
	{
		return std::apply(&IS_TupleUnzip::TupleUnzip, tuple);
	}

	using Type = S_TupleUnzip<T_Tuple..., End>::Type;
};