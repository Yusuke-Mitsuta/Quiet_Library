#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	template<class ...T_Head_Type>
	struct _Head :
		public _Control<T_Head_Type...>
	{

	};



}
