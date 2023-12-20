#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	//d—l
	//[type]‚Ì•À‚Ñ‡‚ğ”½“]‚³‚¹‚é
	template<class T_Tuple>
	struct I_Reverse
	{
	private:

		template<class T_Reverse,class T_Result= tuple_t<>>
		struct S_Reverse
		{
			using type = T_Result;
		};

		template<class T_Front_Type,class ...T_Types,template<class...>class T_Outer, class ...T_Result_Types>
		struct S_Reverse<tuple_t<T_Front_Type,T_Types...>,T_Outer<T_Result_Types...>>
		{
			using type = S_Reverse<tuple_t<T_Types...>, T_Outer<T_Front_Type, T_Result_Types...>>::type;
		};

		template<class ...T_Head_Types, class T, class ...T_Tail_Types,class T_Result>
		struct S_Reverse<tuple_tp<tuple_t<T_Head_Types...>, T, tuple_t<T_Tail_Types...>>, T_Result>
		{
			using Head_Reverse =typename S_Reverse<tuple_t<T_Head_Types...>>::type;

			using Tail_Reverse = typename S_Reverse<tuple_t<T_Tail_Types...>>::type;

			using type = tuple_tp<Tail_Reverse, T, Head_Reverse>;
		};

	public:

		using type = S_Action_Tuple_tp<S_Reverse, T_Tuple>::type;
	};

}