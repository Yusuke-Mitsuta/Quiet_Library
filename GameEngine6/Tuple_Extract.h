#pragma once


#include"Tuple_Declare.h"

namespace N_Tuple
{

	//d—l
	//[T_Tuple]‚©‚ç[Tuple_v< ... >]‚Ì‡”Ô‚ÅŒ^‚ğ‡”Ô‚É’Šo
	template<class T_Tuple,class T_Extract_Number>
	struct I_Extract
	{
		using Extract_Number = U_Tuple_t_To_v<U_Remove_p<T_Extract_Number>>;

		template<class T_Extract_Number = T_Extract_Number>
		struct S_Extract;

		template<auto ..._Index>
		struct S_Extract<Tuple_v<_Index...>>
		{
			using type = Tuple_t<U_Element_t<_Index,T_Tuple>...>;
		};

		using type = S_Extract<>::type;
	};
	
}
