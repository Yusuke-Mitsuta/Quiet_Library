#pragma once

#include <iostream>

#include"MethodData.h"
#include"SwapType.h"
#include"main.h"

namespace N_Function
{
	//�d�l
	//[FunctionStatic]��Operator�����̎���
	//
	//template
	//t_Fn::�֐��|�C���^�[or[FunctionStatic]
	//...t_Args::Bind�������
	//
	//�⑫
	//[IS_FunctionOperator_Static::Type]���p�����鎖
	//t_Fn��[FunctionStatic]���Z�b�g����ۂ�[static constexpr]�ŏC�����鎖
	template <auto t_Fn, auto ...t_Args>
	struct IS_FunctionOperator_Static
	{
	private:
		using MethodData = N_Function::S_MethodData<std::remove_const_t<decltype(t_Fn)>, decltype(t_Args)...>;

		using BoundArgs = MethodData::BoundArgs;
		using RType = MethodData::RType;
		using Args = MethodData::Args;

		IS_FunctionOperator_Static() = delete;

	public:

		template<class T_Request_Args_Number>
		struct S_FunctionOperator_Static;

		//�d�l
		//bindArgs�������Ȃ�[Function]��Operator�����̎���
		//
		//template
		//...t_Request_Args_Number::operator()()�̈����ŗv������^��[size_t]�p�����[�^�p�b�N
		template<size_t... t_Request_Args_Number>
		struct S_FunctionOperator_Static<
			std::index_sequence<t_Request_Args_Number...>>
		{

			//�d�l
			//�ÓI�ȏ�ԂŊ֐��ɃA�N�Z�X����
			static constexpr RType Execution(std::tuple_element_t<t_Request_Args_Number, Args>... args)
				requires same_as<std::true_type, typename MethodData::Root>
			{
				return (h->*t_Fn)(args..., t_Args...);
			}

			static constexpr RType Execution(std::tuple_element_t<t_Request_Args_Number, Args>... args)
				requires same_as<std::false_type, typename MethodData::Root>
			{
				return t_Fn.Execution(args...,t_Args...);
			}

			constexpr RType operator()(std::tuple_element_t<t_Request_Args_Number, Args>... args)
			{
				return Execution(args...);
			}

		};

	public:

		using Type = S_FunctionOperator_Static
			<
				std::make_index_sequence<std::tuple_size_v<typename MethodData::Args>-std::tuple_size_v<typename MethodData::BoundArgs>>
		
			>;

	};

}