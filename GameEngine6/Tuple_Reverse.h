#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	//d—l
	//[T_Tuple_t]‚Ì•À‚Ñ‡‚ğ”½“]‚³‚¹‚é
	template<class T_Tuple_t>
	struct I_Reverse
	{
	private:
		template<class T_Tuple_t> 
		struct S_Reverse;

		template<class T_Side,class T_Result>
		struct S_Side_Reverse
		{
			using Type = T_Result;
		};

		template<template<class...>class T_Side_Outer,class T_Flont_Side_Type, class ...T_Side_Types, template<class...>class T_Result_Outer, class ...T_Result_Types >
		struct S_Side_Reverse< T_Side_Outer<T_Flont_Side_Type,T_Side_Types...>, T_Result_Outer<T_Result_Types...>>
		{
			using Type =typename S_Side_Reverse<T_Side_Outer< T_Side_Types...>, T_Result_Outer<T_Flont_Side_Type, T_Result_Types...>>::Type;
		};


		template<class ...T_Head_Types, class T, class ...T_Tail_Types>
		struct S_Reverse<Tuple_tp<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
		{
			using Head_Reverse =S_Side_Reverse<_Head<T_Head_Types...>,_Tail<>>::Type;

			using Tail_Reverse =S_Side_Reverse<_Tail<T_Tail_Types...>,_Head<>>::Type;

			using Type = Tuple_tp<Tail_Reverse, T, Head_Reverse>;
		};

		using Action = S_Tuple_Action<T_Tuple_t, S_Reverse>;

		friend struct Action;

	public:

		using Type = typename Action::Type;

	};

}