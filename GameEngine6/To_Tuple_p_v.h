#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	template<class T>
	struct Tuple_tp_To_vp
	{
		using Type = T;
	};

	template<class T>
	struct Tuple_vp_To_tp
	{
		using Type = T;
	};

	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
	struct Tuple_tp_To_vp<Tuple_tp<_Head<integral_constant<t_Head_Value>...>,
		integral_constant<_Value>,
		_Tail<integral_constant<t_Tail_Value>...>>>
	{
		using Type = Tuple_vp<_Head_v<t_Head_Value...>, _Value, _Tail_v<t_Tail_Value...>>;
	};

	template<auto ...t_Head_Value, auto...t_Tail_Value>
	struct Tuple_tp_To_vp<Tuple_tp<_Head<integral_constant<t_Head_Value>...>,
		std::nullopt_t,
		_Tail<integral_constant<t_Tail_Value>...>>>
	{
		using Type = Tuple_vp<_Head_v<t_Head_Value...>,std::nullopt, _Tail_v<t_Tail_Value...>>;
	};


	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
		requires not_is_nullopt<decltype(_Value)>
	struct Tuple_vp_To_tp<Tuple_vp<_Head_v<t_Head_Value...>,
		_Value, _Tail_v<t_Tail_Value...>>>
	{
		using Type = Tuple_tp<_Head<integral_constant<t_Head_Value>...>,
			integral_constant<_Value>,
			_Tail<integral_constant<t_Tail_Value>...>>;
	};

	template<auto ...t_Head_Value, auto _Value, auto...t_Tail_Value>
		requires is_nullopt<decltype(_Value)>
	struct Tuple_vp_To_tp<Tuple_vp<_Head_v<t_Head_Value...>,
		_Value, _Tail_v<t_Tail_Value...>>>
	{
		using Type = Tuple_tp<_Head<integral_constant<t_Head_Value>...>,
			std::nullopt_t,
			_Tail<integral_constant<t_Tail_Value>...>>;
	};


}
