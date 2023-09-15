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
	struct _p;

	template<auto ..._Value>
	struct _v{};

	template<class T_Head,auto _Value,class T_Tail>
	struct _p_v;

	template<auto ...t_Head_Value, auto _Value, auto...T_Tail_Value>
	struct _p_v<_Head_v<t_Head_Value...>,_Value,
		_Tail_v<T_Tail_Value...>>
	{

	};

	template<auto ...t_Head_Value,auto _Value, auto...T_Tail_Value>
	struct _p<_Head<integral_constant<t_Head_Value>...>, 
		integral_constant<_Value>, 
		_Tail<integral_constant<T_Tail_Value>...>> :
		public _Control<_Head<integral_constant<t_Head_Value>...>, 
		integral_constant<_Value>, 
		_Tail<integral_constant<T_Tail_Value>...>>
	{
	private:
		using Control = _Control<_Head<integral_constant<t_Head_Value>...>,
			integral_constant<_Value>,
			_Tail<integral_constant<T_Tail_Value>...>>;
	public:

		static constexpr auto Flont_v = Control::Flnot::value;
		static constexpr auto Back_v = Control::Back::value;
		static constexpr auto This_v = Control::This::value;

		using As_Tuple_v = _v<t_Head_Value..., _Value, T_Tail_Value...>;

	};

	template<auto t_Flont_Value, auto ..._Value>
	struct _v<t_Flont_Value,_Value...> :
		public _p<_Head<>, integral_constant<t_Flont_Value>, _Tail<integral_constant<_Value>...>>
	{
	public:

		using As_Tuple_t = _p<_Head<>, integral_constant<t_Flont_Value>, _Tail<integral_constant<_Value>...>>;

	};

	template<>
	struct _v<> :
		public _p<_Head<>, _Tail<>>
	{
		using As_Tuple_t = _p<_Head<>, _Tail<>>;
	};

}


