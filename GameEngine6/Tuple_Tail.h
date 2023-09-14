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

}

namespace std
{
	template<class ...T_Tail_Types>
	struct tuple_size<N_Tuple::_Tail<T_Tail_Types...>> :
		integral_constant<size_t, sizeof...(T_Tail_Types)> {};
}
