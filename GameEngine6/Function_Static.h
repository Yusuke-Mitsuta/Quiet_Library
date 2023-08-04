#pragma once

#include"Function_Helper.h"
#include"FunctionOperator_Static.h"

//�d�l
//�ÓI�Ȋ֐��I�u�W�F�N�g���쐬����
//t_Fn::�ÓI�Ȋ֐��I�u�W�F�N�g�ɂ���A�֐��|�C���^�[or[FunctionStatic]
//t_Args::[t_Fn]�ɑ΂������
//
//�⑫
//[t_Fn]��[FunctionStatic]��ݒ肷��ꍇ[static constexpr]�ŏC�����鎖
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