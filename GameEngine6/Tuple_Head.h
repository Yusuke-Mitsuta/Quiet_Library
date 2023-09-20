#pragma once

#include"Tuple_Declare.h"


namespace N_Tuple
{
	template<class ...T_Head_Type>
	struct Head_t
	{

	};

	template<auto ...t_Head_Value>
	struct Head_v
	{

	};

}

namespace std 
{
	template<class ...T_Head_Type>
	struct tuple_size<N_Tuple::Head_t<T_Head_Type...>> : 
		integral_constant<size_t,sizeof...(T_Head_Type)> 
	{
		static constexpr size_t value = sizeof...(T_Head_Type);
	};

	template<auto ...t_Head_Value>
	struct tuple_size<N_Tuple::Head_v<t_Head_Value...>> :
		integral_constant<size_t, sizeof...(t_Head_Value)>
	{
		static constexpr size_t value = sizeof...(t_Head_Value);
	};
}

