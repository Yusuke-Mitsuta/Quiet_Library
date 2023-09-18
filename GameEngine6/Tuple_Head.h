#pragma once

#include"Tuple_Declare.h"


namespace N_Tuple
{

	//仕様
	//[Tuple_t]の選択位置より前を示す型
	template<class ...T_Head_Type>
	struct _Head
	{

	};

	template<auto ...t_Head_Value>
	struct _Head_v
	{

	};

}

namespace std 
{
	template<class ...T_Head_Type>
	struct tuple_size<N_Tuple::_Head<T_Head_Type...>> : 
		integral_constant<size_t,sizeof...(T_Head_Type)> 
	{
		static constexpr size_t value = sizeof...(T_Head_Type);
	};

	template<auto ...t_Head_Value>
	struct tuple_size<N_Tuple::_Head_v<t_Head_Value...>> :
		integral_constant<size_t, sizeof...(t_Head_Value)>
	{
		static constexpr size_t value = sizeof...(t_Head_Value);
	};
}

