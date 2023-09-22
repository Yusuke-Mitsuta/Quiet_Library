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
			using type = T_Result;
		};

		template<class T_Flont_Type,class ...T_Types,template<class...>class T_Outer, class ...T_Result_Types>
		struct S_Reverse<Tuple_t<T_Flont_Type,T_Types...>,T_Outer<T_Result_Types...>>
		{
			using type = S_Reverse<Tuple_t<T_Types...>, T_Outer<T_Flont_Type, T_Result_Types...>>::type;
		};

		template<class ...T_Head_Types, class T, class ...T_Tail_Types,class T_Result>
		struct S_Reverse<Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<T_Tail_Types...>>, T_Result>
		{
			using Head_Reverse =typename S_Reverse<Tuple_t<T_Head_Types...>,Tail_t<>>::type;

			using Tail_Reverse = typename S_Reverse<Tuple_t<T_Tail_Types...>,Head_t<>>::type;

			using type = Tuple_tp<Tail_Reverse, T, Head_Reverse>;
		};

	public:

		using type = S_Action_Tuple_tp<S_Reverse, T_Tuple>::type;
	};

}