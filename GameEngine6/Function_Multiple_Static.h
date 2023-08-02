#pragma once

#include"Function_Multiple_Static_Operator.h"

#include"I_Function.h"

template<auto ...t_Fns>
	requires not_same_as<typename N_Function::IS_Function_Multiple_Helper<std::remove_const_t<decltype(t_Fns)>...>::Judge, std::nullopt_t>
class Function::Multiple_Static :
	public N_Function::IS_Function_Multiple_Static_Operator<t_Fns...>::Type
{
private:
	using FunctionOperator = N_Function::IS_Function_Multiple_Static_Operator<t_Fns...>::Type;
public:


	using FunctionOperator::operator();
};

namespace N_Function
{

	template<auto ...t_Fns>
		requires not_same_as<typename N_Function::IS_Function_Multiple_Helper<std::remove_const_t<decltype(t_Fns)>...>::Judge, std::nullopt_t>
	class Function_Multiple_Static :
		public N_Function::IS_Function_Multiple_Static_Operator<t_Fns...>::Type
	{
	private:
		using FunctionOperator = N_Function::IS_Function_Multiple_Static_Operator<t_Fns...>::Type;
	public:


		using FunctionOperator::operator();
	};

}