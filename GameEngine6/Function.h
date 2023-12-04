#pragma once

#include"Concept.h"
#include"Function_Helper.h"
#include"Function_Operator.h"

template<class TP_Fns,class TP_Args_type>
class Function :
	public N_Function::I_Function_Operator<TP_Fns,TP_Args_type>::type
{


public:

	template<class ...MT_Fn_Parts>
	constexpr Function(MT_Fn_Parts... fn_Parts) :
		N_Function::I_Function_Operator<TP_Fns, TP_Args_type>::type(fn_Parts...)
		{}


	using N_Function::I_Function_Operator<TP_Fns, TP_Args_type>::type::operator();




};

template<class ...T_Fn_Parts>
Function(T_Fn_Parts... fn_Parts) -> Function<typename
	N_Function::I_Function_Multiple_Helper<T_Fn_Parts...>::function_check,tuple_t<T_Fn_Parts...>>;