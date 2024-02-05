#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple::N_Apply
{
	template<class T,size_t number=0>
	struct S_Infinite_Args
	{
		using tuple = tuple_t<S_Infinite_Args<T,number+1>,T>;
	};

}