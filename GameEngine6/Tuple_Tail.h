#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	template<class ...T_Tail_Types>
	struct _Tail :
		public _Control<T_Tail_Types...>
	{

	};



}
