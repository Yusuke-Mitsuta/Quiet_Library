#pragma once


#include"Function_Helper.h"

template<class TP_Methods>
class Method
{

	template<class ...MT_Fn_Parts>
	constexpr Method(MT_Fn_Parts... fn_Parts) {}


};

template<class ...T_Fn_Parts>
Method(T_Fn_Parts... fn_Parts) -> Method<typename
	N_Function::I_Function_Multiple_Helper<T_Fn_Parts...>::method_check>;
