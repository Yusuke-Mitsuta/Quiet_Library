#pragma once

#include"Concept.h"

namespace N_Tuple
{
	template<class ...T_Types>
	struct S_Parameter;

	template<class T_Tuple, int t_Number>
	concept is_Element_Head = is_Element<typename S_Parameter<T_Tuple>::Head, t_Number>;

	template<class T_Tuple, int t_Number>
	concept is_Element_Tail = is_Element<typename S_Parameter<T_Tuple>::Tial, t_Number>;


	//template<class T>
	//concept N= std::integral<T> || 


}