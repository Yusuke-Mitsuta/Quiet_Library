#pragma once

#include"Tuple_Declare.h"

#include"Tuple_Control.h"




template<quiet::N_Tuple::same_as_tuple_t T_Head, class T, quiet::N_Tuple::same_as_tuple_t T_Tail>
struct tuple_tp :
	quiet::N_Tuple::Control_t<tuple_tp<T_Head, T, T_Tail>>
{
};

template<class ...T_Types>
struct tuple_t :
	quiet::N_Tuple::Control_t<tuple_t<T_Types...>>,
	std::tuple<T_Types...>
{
	using std::tuple<T_Types...>::tuple;
	
};

namespace std
{
	template<class ...T_Type>
	struct tuple_size<tuple_tp<T_Type...>> :
		integral_constant<size_t, quiet::N_Tuple::S_Parameter<
		tuple_tp<T_Type...>>::size> 
	{
		static constexpr size_t value =
			quiet::N_Tuple::S_Parameter<tuple_tp<T_Type...>>::size;
	};

	template<class ...T_Type>
	struct tuple_size<tuple_t<T_Type...>> :
		integral_constant<size_t, sizeof...(T_Type)>
	{
		static constexpr size_t value = sizeof...(T_Type);
	};
}





