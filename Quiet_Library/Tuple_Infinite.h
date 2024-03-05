/*!
 * Tuple_Infinite.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"


namespace quiet::N_Tuple::N_Apply
{


	template<class T,size_t N=10>
	struct S_Infinite_Args
	{
		using type = T;
		using constructor_args = tuple_t<T>;
		static constexpr size_t value = N;
	};

	template<class T, size_t N >
		requires requires
	{
		requires is_invalid_not<typename S_Parameter<T>::tuple>;
	}
	struct S_Infinite_Args<T,N>
	{
		using type = T;
		using constructor_args = S_Parameter<T>::tuple;
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
