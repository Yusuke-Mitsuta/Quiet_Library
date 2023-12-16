#pragma once
//
//#include"Function_Single_Helper.h"
//#include"Function_Single_Static_Operator.h"
//
//namespace N_Function
//{
//	//仕様
//	//静的な関数オブジェクトを作成する
//	//t_Fn::静的な関数オブジェクトにする、関数ポインターor[Function_Single_Static]
//	//t_Args::[t_Fn]に対する引数
//	//
//	//補足
//	//[t_Fn]に[Function_Single_Static]を設定する場合[static constexpr]で修飾する事
//	template<auto t_Fn, auto ...t_Args>
//		requires not_same_as<typename N_Function::IS_Function_Single_Helper<std::remove_const_t<decltype(t_Fn)>, decltype(t_Args)...>::Judge, invalid_t>
//	class Function_Single_Static :
//		public N_Function::IS_Function_Single_Static_Operator<t_Fn, t_Args...>::Type
//	{
//	public:
//
//		using FunctionOperator = N_Function::IS_Function_Single_Static_Operator<t_Fn, t_Args...>::Type;
//
//		using FunctionOperator::operator();
//		using FunctionOperator::Execution;
//
//	};
//
//}