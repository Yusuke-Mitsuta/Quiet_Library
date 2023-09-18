#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	//�d�l
	//[Tuple_t]�̑I���ʒu�����������^
	template<class ...T_Tail_Types>
	struct _Tail :
		public _Control<T_Tail_Types...>
	{

	};

	template<auto ...t_Tail_Value>
	struct _Tail_v
	{

	};

}

namespace std
{
	template<class ...T_Tail_Types>
	struct tuple_size<N_Tuple::_Tail<T_Tail_Types...>> :
		integral_constant<size_t, sizeof...(T_Tail_Types)> 
	{
		static constexpr size_t value = sizeof...(T_Tail_Types);
	};

	template<auto ...t_Tail_Value>
	struct tuple_size<N_Tuple::_Tail_v<t_Tail_Value...>> :
		integral_constant<size_t, sizeof...(t_Tail_Value)>
	{
		static constexpr size_t value = sizeof...(t_Tail_Value);
	};
}
