#pragma once

#include"Concept.h"
#include"Function_Helper.h"
#include"Function_Operator.h"

template<not_is_invalid T_Fns>
class Function :
	public N_Function::I_Function_Operator_2<T_Fns>::type
{


public:

	template<class ...MT_Fn_Parts>
	constexpr Function(MT_Fn_Parts... fn_Parts) :
		N_Function::I_Function_Operator_2<T_Fns>::type(fn_Parts...)
		{
		C_OUT(T_Fns::t::size);
	
	}

	using N_Function::I_Function_Operator_2<T_Fns>::type::operator();

	using core = T_Fns;


};

template<class ...T_Fn_Parts>
Function(T_Fn_Parts... fn_Parts) -> Function<typename
	N_Function::I_Function_Multiple_Helper<T_Fn_Parts...>::type>;