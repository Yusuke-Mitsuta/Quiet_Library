#pragma once

#include <iostream>

#include"MethodData.h"
#include"SwapType.h"
#include"main.h"

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
		//bindArgs�������Ȃ�[Function]��Operator�����̎���
		//
		//template
		//...t_Request_Args_Number::operator()()�̈����ŗv������^��[size_t]�p�����[�^�p�b�N
		template<size_t... t_Request_Args_Number>
		struct S_FunctionOperator<std::nullopt_t,
			std::index_sequence<t_Request_Args_Number...>>
		{
		private:

			Fn fn;

		public:
			template<class MT_Fn>
			constexpr S_FunctionOperator(MT_Fn setFn)
				:fn(setFn) {}

			constexpr RType operator()(std::tuple_element_t<t_Request_Args_Number, Args>... args)
				requires same_as<std::true_type, typename MethodData::Root>
			{
				return (h->*fn)(args...);
			}

			constexpr RType operator()(std::tuple_element_t<t_Request_Args_Number, Args>... args)
				requires same_as<std::false_type, typename MethodData::Root>
			{
				return fn.operator()(args...);
			}

		};

		//�d�l
		//�v������֐��̈����̔ԍ��̃f�t�H���g�l
		template<size_t t_Changes = 0 >
		using T_Default_Request_Args_Number =
			std::make_index_sequence<
			std::tuple_size_v<typename MethodData::Args> -
			std::tuple_size_v<typename MethodData::BoundArgs>+t_Changes>;

		//�d�l
		//[Function]��Operator�����̎���
		//
		//template
		//...t_Args_BindNumber::�o�C���h�ς݂̈������Ăяo���ׂ�[size_t]�p�����[�^�p�b�N
		//...t_Request_Args_Number::operator()()�̈����ŗv������^��[size_t]�p�����[�^�p�b�N
		template<size_t ...t_Args_BindNumber,size_t... t_Request_Args_Number>
		struct S_FunctionOperator<std::index_sequence<t_Args_BindNumber...>,
			std::index_sequence<t_Request_Args_Number...>>:
			public S_FunctionOperator<std::nullopt_t,
			T_Default_Request_Args_Number<sizeof...(T_Args)>>
		{
		private:

			using Fn = S_FunctionOperator<std::nullopt_t,
				T_Default_Request_Args_Number<sizeof...(T_Args)>>;

			BindArgs bindArgs;
		public:

			template<class MT_Fn, class ...MT_Args>
			constexpr S_FunctionOperator(MT_Fn setFn, MT_Args ...setArgs)
				:Fn(setFn), bindArgs(setArgs...) {}

			constexpr RType operator()(std::tuple_element_t<t_Request_Args_Number, Args>... args)
			{
				return Fn::operator()(args..., std::get<t_Args_BindNumber>(bindArgs)...);
			}
		};

	private:
		using Judge = IS_JudgeType_t<std::make_index_sequence<sizeof...(T_Args)>,
			(sizeof...(T_Args))>;
	public:

		using Type = S_FunctionOperator<Judge,T_Default_Request_Args_Number<>>;
	};

}