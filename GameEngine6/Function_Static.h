#pragma once

#include"Function_Helper.h"
#include"FunctionOperator_Static.h"

//仕様
//静的な関数オブジェクトを作成する
//t_Fn::静的な関数オブジェクトにする、関数ポインターor[FunctionStatic]
//t_Args::[t_Fn]に対する引数
//
//補足
//[t_Fn]に[FunctionStatic]を設定する場合[static constexpr]で修飾する事
template<auto t_Fn,auto ...t_Args>
	requires not_same_as<typename N_Function::IS_FunctionHelper<std::remove_const_t<decltype(t_Fn)>,decltype(t_Args)...>::Judge,std::nullopt_t>
class FunctionStatic :
	public N_Function::IS_FunctionOperator_Static<t_Fn,t_Args...>::Type
{
public:

	using FunctionOperator = N_Function::IS_FunctionOperator_Static<t_Fn, t_Args...>::Type;
	
	using FunctionOperator::operator();
	using FunctionOperator::Execution;

};