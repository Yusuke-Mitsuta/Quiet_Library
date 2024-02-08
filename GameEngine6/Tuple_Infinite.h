#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple::N_Apply
{
	template<class T,size_t N=10>
	struct S_Infinite_Args
	{
		static constexpr size_t value = N;
	};

	template<class T>
	struct is_Infinite_Args_C
	{
		static constexpr bool value = false;
	};

	template<class T, size_t N>
	struct is_Infinite_Args_C<S_Infinite_Args<T,N>>
	{
		static constexpr bool value = true;
	};

	template<class T>
	concept is_Infinite_Args = is_Infinite_Args_C<T>::value;
}
