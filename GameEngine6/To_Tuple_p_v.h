#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	template<class T>
	struct To_Tuple_p_v
	{
		using Type = T;
	};

	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
	struct To_Tuple_p_v<_p<_Head<integral_constant<t_Head_Value>...>,
		integral_constant<_Value>,
		_Tail<integral_constant<t_Tail_Value>...>>>
	{
		using Type = _p_v<_Head_v<t_Head_Value...>, _Value, _Tail_v<t_Tail_Value...>>;
	};

}
