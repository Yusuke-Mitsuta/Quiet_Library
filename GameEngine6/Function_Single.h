#pragma once

#include"Function_Single_Helper.h"
#include"Function_Single_Operator.h"

namespace N_Function
{
	template<not_same_as<std::nullopt_t> T_Method, class ...TP_Args>
	class Function_Single :
		public N_Function::IS_Function_Single_Operator<T_Method, TP_Args...>::Type
	{
	protected:

		using MethodData = N_Function::S_MethodData<T_Method, TP_Args...>;

		using FunctionOperator = N_Function::IS_Function_Single_Operator<T_Method, TP_Args...>::Type;

	public:

		using FunctionOperator::operator();
		template<class MT_Fn, class ...MT_Args>
		constexpr Function_Single(MT_Fn fn, MT_Args ...args) :
			N_Function::IS_Function_Single_Operator<MT_Fn, MT_Args...>::Type(fn, args...) 
		{}

	};

	template<class MT_Fn, class ...TP_Args>
	Function_Single(MT_Fn setFn, TP_Args... setArgs) -> Function_Single<typename N_Function::IS_Function_Single_Helper<MT_Fn, TP_Args...>::Judge, TP_Args...>;

}