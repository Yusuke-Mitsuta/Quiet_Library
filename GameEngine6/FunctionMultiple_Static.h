#pragma once

#include"FunctionMultiple_Helper.h"
#include"FunctionMultipleOperator_Static.h"

template<auto ...t_Fns>
	requires not_same_as<typename N_Function::IS_FunctionMultiple_Helper<std::remove_const_t<decltype(t_Fns)>...>::Judge, std::nullopt_t>
class FunctionMultipleStatic :
	public N_Function::IS_FunctionMultipleOperatorStatic<t_Fns...>::Type
{
private:
	using FunctionOperator = N_Function::IS_FunctionOperator_Static<t_Fns...>::Type;
public:


	using FunctionOperator::operator();
};