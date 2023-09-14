#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	//仕様
	//[Tuple_t]の選択位置より後ろを示す型
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
		integral_constant<size_t, sizeof...(T_Tail_Types)> {};
}
