#pragma once

#include"Function_Single_Static_Operator.h"

#include"I_Function.h"

//�d�l
//�ÓI�Ȋ֐��I�u�W�F�N�g���쐬����
//t_Fn::�ÓI�Ȋ֐��I�u�W�F�N�g�ɂ���A�֐��|�C���^�[or[Function_Single_Static]
//t_Args::[t_Fn]�ɑ΂������
//
//�⑫
//[t_Fn]��[Function_Single_Static]��ݒ肷��ꍇ[static constexpr]�ŏC�����鎖
template<auto t_Method, auto ...tP_Args>
	requires not_same_as<typename N_Function::IS_Function_Single_Helper<std::remove_const_t<decltype(t_Method)>, decltype(tP_Args)...>::Judge, std::nullopt_t>
class Function::Single_Static :
	public N_Function::IS_Function_Single_Static_Operator<t_Method, tP_Args...>::Type
{
public:

	using FunctionOperator = N_Function::IS_Function_Single_Static_Operator<t_Method, tP_Args...>::Type;

	using FunctionOperator::operator();
	using FunctionOperator::Execution;

};


namespace N_Function
{

	//�d�l
	//�ÓI�Ȋ֐��I�u�W�F�N�g���쐬����
	//t_Fn::�ÓI�Ȋ֐��I�u�W�F�N�g�ɂ���A�֐��|�C���^�[or[Function_Single_Static]
	//t_Args::[t_Fn]�ɑ΂������
	//
	//�⑫
	//[t_Fn]��[Function_Single_Static]��ݒ肷��ꍇ[static constexpr]�ŏC�����鎖
	template<auto t_Fn, auto ...t_Args>
		requires not_same_as<typename N_Function::IS_Function_Single_Helper<std::remove_const_t<decltype(t_Fn)>, decltype(t_Args)...>::Judge, std::nullopt_t>
	class Function_Single_Static :
		public N_Function::IS_Function_Single_Static_Operator<t_Fn, t_Args...>::Type
	{
	public:

		using FunctionOperator = N_Function::IS_Function_Single_Static_Operator<t_Fn, t_Args...>::Type;

		using FunctionOperator::operator();
		using FunctionOperator::Execution;

	};

}