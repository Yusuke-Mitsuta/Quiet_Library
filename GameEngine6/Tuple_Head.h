#pragma once

#include"Tuple_Declare.h"


namespace N_Tuple
{

	//�d�l
	//[Tuple_t]�̑I���ʒu���O�������^
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
		integral_constant<size_t,sizeof...(T_Head_Type)> {};
}

