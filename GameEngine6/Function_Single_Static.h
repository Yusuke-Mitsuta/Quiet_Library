#pragma once
//
//#include"Function_Single_Helper.h"
//#include"Function_Single_Static_Operator.h"
//
//namespace N_Function
//{
//	//�d�l
//	//�ÓI�Ȋ֐��I�u�W�F�N�g���쐬����
//	//t_Fn::�ÓI�Ȋ֐��I�u�W�F�N�g�ɂ���A�֐��|�C���^�[or[Function_Single_Static]
//	//t_Args::[t_Fn]�ɑ΂������
//	//
//	//�⑫
//	//[t_Fn]��[Function_Single_Static]��ݒ肷��ꍇ[static constexpr]�ŏC�����鎖
//	template<auto t_Fn, auto ...t_Args>
//		requires same_as_not<typename N_Function::IS_Function_Single_Helper<std::remove_const_t<decltype(t_Fn)>, decltype(t_Args)...>::Judge, invalid_t>
//	class Function_Single_Static :
//		public N_Function::IS_Function_Single_Static_Operator<t_Fn, t_Args...>::type
//	{
//	public:
//
//		using FunctionOperator = N_Function::IS_Function_Single_Static_Operator<t_Fn, t_Args...>::type;
//
//		using FunctionOperator::operator();
//		using FunctionOperator::Execution;
//
//	};
//
//}