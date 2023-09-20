#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Control.h"
#include"Tuple_Head.h"
#include"Tuple_Tail.h"

#include<optional>

namespace N_Tuple
{

	template<same_as_template_type<Head_t> T_Head,class T, same_as_template_type<Tail_t> T_Tail>
	struct Tuple_tp :
		Control_tp<T_Head,T,T_Tail>{};

	template<class ..._Types>
	struct Tuple_t;

	template<class T_Flont_Type,class ...T_Types>
	struct Tuple_t<T_Flont_Type,T_Types...> :
		Control_tp<Head_t<>,T_Flont_Type,Tail_t<T_Types...>>
	{

	};

	template<>
	struct Tuple_t<> : 
		Control_tp<Head_t<>, std::nullopt_t, Tail_t<>>
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

