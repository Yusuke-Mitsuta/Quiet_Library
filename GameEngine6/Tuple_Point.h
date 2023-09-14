#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{
	template<class ...T_Point>
		requires (sizeof...(T_Point) <= 1)
	struct _Point;

	template<class T_Point>
	struct _Point<T_Point>
	{

	};

	template<>
	struct _Point<>
	{

	};

}
