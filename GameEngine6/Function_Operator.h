#pragma once

#include"MethodData.h"

namespace N_Function 
{
	//�d�l
	//[Function]��Operator�����̎���
	//
	//template
	//T_Fn::�֐��̌^
	//...T_Args::Bind��������̌^���X�g
	//
	//�⑫
	//IS_FunctionOperator�̎��̉��͋֎~�Ƃ���
	//IS_FunctionOperator::Type�����̉����鎖
	template <class T_Fn, class ...T_Args>
	struct IS_FunctionOperator
	{
	private:
		using MethodData = N_Function::S_MethodData<T_Fn, T_Args...>;

		using BoundArgs = MethodData::BoundArgs;
		using BindArgs = MethodData::BindArgs;
		using CName = MethodData::CName;
		using RType = MethodData::RType;
		using Args = MethodData::Args;
		using Fn = MethodData::Fn;

		IS_FunctionOperator() = delete;
	public:

		template<class T_Args_Number,class T_Request_Args_Number>
		struct S_FunctionOperator;


		//�d�l
		//[Function]��Operator�����̎���
		//
		//template
		//...t_Args_BindNumber::�o�C���h�ς݂̈������Ăяo���ׂ�[size_t]�p�����[�^�p�b�N
		//...t_Request_Args_Number::operator()()�̈����ŗv������^��[size_t]�p�����[�^�p�b�N
		template<size_t ...t_Args_BindNumber,size_t... t_Request_Args_Number>
		struct S_FunctionOperator<std::index_sequence<t_Args_BindNumber...>,
			std::index_sequence<t_Request_Args_Number...>>
		{
		private:
			CName* classP = nullptr;
			Fn fn;
			BindArgs bindArgs;
		public:

			template<class MT_Fn, class ...MT_Args>
			constexpr S_FunctionOperator(MT_Fn setFn, MT_Args ...setArgs)
				:fn(setFn), bindArgs(setArgs...) {}

			constexpr RType operator()(std::tuple_element_t<t_Request_Args_Number, Args>... args)
				requires same_as<std::true_type, typename MethodData::Root>
			{
				return (classP->*fn)(args..., std::get<t_Args_BindNumber>(bindArgs)...);
			}

			constexpr RType operator()(std::tuple_element_t<t_Request_Args_Number, Args>... args)
				requires same_as<std::false_type, typename MethodData::Root>
			{
				return fn.operator()(args..., std::get<t_Args_BindNumber> (bindArgs)...);
			}
		};

	public:
		using Type = S_FunctionOperator<std::make_index_sequence<std::tuple_size_v< typename MethodData::BindArgs>>,std::make_index_sequence<std::tuple_size_v<typename MethodData::Args>-std::tuple_size_v<typename MethodData::BoundArgs>>>;

	};

}