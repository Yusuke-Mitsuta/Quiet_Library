#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Control.h"
#include"Tuple_Head.h"
#include"Tuple_Tail.h"

namespace N_Tuple
{

	template<class ..._Types>
	struct Tuple_t
	{

	};

	template<class ..._Types>
	struct Tuple_tp;

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct Tuple_tp<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>> :
		public _Control_t<Tuple_tp<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
	{

	};


}

namespace std
{
	template<class ...T_Type>
	struct tuple_size<N_Tuple::Tuple_tp<T_Type...>> :
		integral_constant<size_t, N_Tuple::S_Parameter<
		N_Tuple::Tuple_tp<T_Type...>>::Size> 
	{
		static constexpr size_t value =
			N_Tuple::S_Parameter<N_Tuple::Tuple_tp<T_Type...>>::Size;
	};

	template<class ...T_Type>
	struct tuple_size<N_Tuple::Tuple_t<T_Type...>> :
		integral_constant<size_t, sizeof...(T_Type)>
	{
		static constexpr size_t value = sizeof...(T_Type);
	};
}

