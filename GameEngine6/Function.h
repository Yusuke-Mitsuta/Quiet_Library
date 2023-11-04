#pragma once

#include"Concept.h"
#include"Function_Helper.h"

template<class TP_Fns>
class Function
{
public:


	template<class ...MT_Fn_Parts>
	constexpr Function(MT_Fn_Parts... fn_Parts) {}


	




};

template<class ...T_Fn_Parts>
Function(T_Fn_Parts... fn_Parts) -> Function<typename
	N_Function::I_Function_Multiple_Helper<T_Fn_Parts...>::function_check>;