#pragma once

#include"Tuple_Control.h"
#include"Tuple_Type.h"

template<auto t_Value>
struct integral_constant
{
	using value_type = decltype(t_Value);
	static constexpr auto value = t_Value;

};

namespace N_Tuple
{
	template<class ..._Types>
	struct Tuple_tp;

	template<auto ..._Value>
	struct Tuple_v
	{

	};

	template<class T_Head,auto _Value,class T_Tail>
	struct Tuple_vp;

	template<auto ...t_Head_Value, auto _Value, auto...T_Tail_Value>
	struct Tuple_vp<_Head_v<t_Head_Value...>,_Value,
		_Tail_v<T_Tail_Value...>> :
		public _Control_v<Tuple_vp<_Head_v<t_Head_Value...>, _Value,
		_Tail_v<T_Tail_Value...>>>
	{
	};





	template<auto t_Flont_Value, auto ..._Value>
	struct Tuple_v<t_Flont_Value,_Value...> :
		public Tuple_tp<_Head<>,integral_constant<t_Flont_Value>, _Tail<integral_constant<_Value>...>>
	{
	public:

		using As_Tuple_t = Tuple_tp<_Head<>, integral_constant<t_Flont_Value>, _Tail<integral_constant<_Value>...>>;

	};

}


