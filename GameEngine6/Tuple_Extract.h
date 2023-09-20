#pragma once


#include"Tuple_Declare.h"

namespace N_Tuple
{

	//仕様
	//[T_Tuple]から[Tuple_v< ... >]の順番で型を順番に抽出
	template<class T_Tuple,class T_Extract_Number>
	struct I_Extract
	{
		using Extract_Number =typename Tuple_t_To_v<typename I_Remove_Pointer<T_Extract_Number>::Type>::Type;

		template<class T_Extract_Number = T_Extract_Number>
		struct S_Extract;

		template<auto ..._Index>
		struct S_Extract<Tuple_v<_Index...>>
		{
			using Type = Tuple_t<U_Element_t<_Index,T_Tuple>...>;
		};

		using Type =typename S_Extract<>::Type;
	};
	
}
