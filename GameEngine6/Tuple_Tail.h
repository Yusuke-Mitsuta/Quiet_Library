#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	template<class ...T_Tail_Types>
	struct Tail_t
	{

	};

	template<auto ...t_Tail_Value>
	struct Tail_v
	{

	};

}

namespace std
{
	template<class ...T_Tail_Types>
	struct tuple_size<N_Tuple::Tail_t<T_Tail_Types...>> :
		integral_constant<size_t, sizeof...(T_Tail_Types)> 
	{
		static constexpr size_t value = sizeof...(T_Tail_Types);
	};

	template<auto ...t_Tail_Value>
	struct tuple_size<N_Tuple::Tail_v<t_Tail_Value...>> :
		integral_constant<size_t, sizeof...(t_Tail_Value)>
	{
		static constexpr size_t value = sizeof...(t_Tail_Value);
	};
}
