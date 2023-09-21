#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	//d—l
	//[Type]‚Ì•À‚Ñ‡‚ğ”½“]‚³‚¹‚é
	template<class T_Tuple>
	struct I_Reverse
	{
	private:

		template<class T_Reverse,class T_Result= Tuple_t<>>
		struct S_Reverse
		{
			using Type = T_Result;
		};

		template<class T_Flont_Type,class ...T_Types,template<class...>class T_Outer, class ...T_Result_Types>
		struct S_Reverse<Tuple_t<T_Flont_Type,T_Types...>,T_Outer<T_Result_Types...>>
		{
			using Type = S_Reverse<Tuple_t<T_Types...>, T_Outer<T_Flont_Type, T_Result_Types...>>::Type;
		};

		template<class ...T_Head_Types, class T, class ...T_Tail_Types,class T_Result>
		struct S_Reverse<Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<T_Tail_Types...>>, T_Result>
		{
			using Head_Reverse =typename S_Reverse<Tuple_t<T_Head_Types...>,Tail_t<>>::Type;

			using Tail_Reverse = typename S_Reverse<Tuple_t<T_Tail_Types...>,Head_t<>>::Type;

			using Type = Tuple_tp<Tail_Reverse, T, Head_Reverse>;
		};

	public:

		using Type = typename S_Action_Tuple_tp<S_Reverse, T_Tuple>::type;
	};

}