#pragma once

#include"Concept.h"
#include"Function_Helper.h"
#include"Function_Operator.h"


template<class T_Flont_Parts, class ...T_Parts>
class Function 
	:public N_Function::I_Function_Operator<T_Flont_Parts,T_Parts...>::type
{
public:

	template<class MT_Flont_Parts, class ...MT_Parts>
	constexpr Function(MT_Flont_Parts flont_parts, MT_Parts... fn_Parts) 
		:N_Function::I_Function_Operator<MT_Flont_Parts,MT_Parts...>::type(flont_parts,fn_Parts...)
	{

	}

	
	using N_Function::I_Function_Operator<T_Flont_Parts, T_Parts...>::type::operator();




	//using T = N_Function::I_Function_Operator_Helper<T_Parts...>::type;


};

template<class T_Flont_Parts, class ...T_Parts>
Function(T_Flont_Parts, T_Parts...) -> Function<
	typename N_Function::I_Function_Multiple_Helper<T_Flont_Parts, T_Parts...>::judge,T_Parts...>;
