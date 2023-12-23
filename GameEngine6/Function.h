#pragma once

#include"Function_Core.h"
#include"Function_Helper.h"
#include"Function_Operator.h"

template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function 
	//:public N_Function::I_Function_Operator<T_Front_Parts, T_Parts...>::type
{
public:

	template<class MT_Front_Parts, class ...MT_Parts>
	constexpr Function(MT_Front_Parts&& front_parts, MT_Parts&&... fn_Parts) 
		//:N_Function::I_Function_Operator<T_Front_Parts, T_Parts...>::type
		//(std::forward<MT_Front_Parts>(front_parts),std::forward<MT_Parts>(fn_Parts)...)
	{}

	constexpr Function* operator->()
	{
		return this;
	}

//	using N_Function::I_Function_Operator<T_Front_Parts,T_Parts...>::type::operator();
	//using sort = N_Function::I_Function_Operator<T_Front_Parts, T_Parts...>::function_operator_sort;
	//using data =
		//N_Function::Function_Core<T_Front_Parts, T_Parts...>::request_args;
		//N_Function::I_Function_Operator_Helper<T_Front_Parts, T_Parts...>::type;
		//N_Function::I_Function_Operator<T_Front_Parts, T_Parts...>::function_operator_data;

	using function = N_Function::I_Function_Helper<T_Front_Parts, T_Parts...>::type;

	using request_args= N_Function::I_Function_Valid_Data<Function>::request_args;
	using request_args_s= N_Function::I_Function_Superficial_Data<Function>::request_args;
	using function_s = N_Function::I_Function_Superficial_Data<Function>::function;

};

template<class T_Front_Parts, class ...T_Parts>
Function(T_Front_Parts&&, T_Parts&&...) -> Function<
	typename N_Function::I_Function_Helper<T_Front_Parts, T_Parts...>::judge,T_Parts...>;
