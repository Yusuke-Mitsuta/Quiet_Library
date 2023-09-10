//#pragma once
//
//#include <iostream>
//
//#include"SwapType.h"
//#include"main.h"
//
//namespace N_Function
//{
//	template<class T_Method, class ...T_Args>
//	struct S_MethodData;
//
//	//仕様
//	//[Function_Single_Static]のOperator部分の実装
//	//
//	//template
//	//t_Fn::関数ポインターor[Function_Single_Static]
//	//...t_Args::Bindする引数
//	//
//	//補足
//	//[IS_Function_Single_Static_Operator::Type]を継承する事
//	//t_Fnに[Function_Single_Static]をセットする際は[static constexpr]で修飾する事
//	template <auto t_Fn, auto ...t_Args>
//	struct IS_Function_Single_Static_Operator
//	{
//	private:
//		using MethodData = N_Function::S_MethodData<std::remove_const_t<decltype(t_Fn)>, decltype(t_Args)...>;
//
//		using BoundArgs = MethodData::BoundArgs;
//		using RType = MethodData::RType;
//		using Args = MethodData::Args;
//
//		IS_Function_Single_Static_Operator() = delete;
//
//	public:
//
//		template<class T_Request_Args_Number>
//		struct S_Function_Operator_Static;
//
//		//仕様
//		//bindArgsを持たない[Function]のOperator部分の実装
//		//
//		//template
//		//...t_Request_Args_Number::operator()()の引数で要求する型の[size_t]パラメータパック
//		template<size_t... t_Request_Args_Number>
//		struct S_Function_Operator_Static<
//			std::index_sequence<t_Request_Args_Number...>>
//		{
//			//仕様
//			//静的な状態で関数にアクセスする
//			static constexpr RType Execution(std::tuple_element_t<t_Request_Args_Number, Args>... args)
//				requires same_as<std::true_type, typename MethodData::Root>
//			{
//				return (h->*t_Fn)(args..., t_Args...);
//			}
//
//			static constexpr RType Execution(std::tuple_element_t<t_Request_Args_Number, Args>... args)
//				requires same_as<std::false_type, typename MethodData::Root>
//			{
//				return t_Fn.Execution(args...,t_Args...);
//			}
//
//			constexpr RType operator()(std::tuple_element_t<t_Request_Args_Number, Args>... args)
//			{
//				return Execution(args...);
//			}
//
//		};
//
//	public:
//
//		using Type = S_Function_Operator_Static
//			<
//				std::make_index_sequence<std::tuple_size_v<typename MethodData::Args>-std::tuple_size_v<typename MethodData::BoundArgs>>
//		
//			>;
//
//	};
//
//}