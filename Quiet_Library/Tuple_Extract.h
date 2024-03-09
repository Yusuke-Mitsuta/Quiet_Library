/*!
 * Tuple_Extract.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once


#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{

	//d—l
	//[T_Tuple_Data]‚©‚ç[tuple_v< ... >]‚Ì‡”Ô‚ÅŒ^‚ğ‡”Ô‚É’Šo
	template<class T_Tuple,class T_Set_Extract_Number>
	struct I_Extract
	{
	private:

		template<class T_Extract_Number = T_Set_Extract_Number>
		struct S_Extract;

		template<auto ..._Index>
		struct S_Extract<tuple_v<_Index...>>
		{
			using type = tuple_t<std::tuple_element_t<_Index,T_Tuple>...>;
		};
	public:
		using type = S_Extract<>::type;

	};
	
}
