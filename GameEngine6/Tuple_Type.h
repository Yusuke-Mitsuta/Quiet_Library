#pragma once

#include"Tuple_Declare.h"

#include"Tuple_Control.h"




template<N_Tuple::same_as_tuple_t T_Head, class T, N_Tuple::same_as_tuple_t T_Tail>
struct tuple_tp :
	N_Tuple::Control_t<tuple_tp<T_Head, T, T_Tail>>
{
};

template<class ...T_Types>
struct tuple_t :
	N_Tuple::Control_t<tuple_t<T_Types...>>
{

};



namespace std
{
	template<class ...T_Type>
	struct tuple_size<tuple_tp<T_Type...>> :
		integral_constant<size_t, N_Tuple::S_Parameter<
		tuple_tp<T_Type...>>::size> 
	{
		static constexpr size_t value =
			N_Tuple::S_Parameter<tuple_tp<T_Type...>>::size;
	};

	template<class ...T_Type>
	struct tuple_size<tuple_t<T_Type...>> :
		integral_constant<size_t, sizeof...(T_Type)>
	{
		static constexpr size_t value = sizeof...(T_Type);
	};
}





