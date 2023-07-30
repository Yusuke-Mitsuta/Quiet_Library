#pragma once

#include <iostream>
#include<tuple>
#include"Function.h"

namespace N_Function
{
	//仕様
	//[Function]のOperator部分の実装
	//
	//template
	//T_Fn::関数の型
	//...T_Args::Bindする引数の型リスト
	//
	//補足
	//IS_FunctionOperatorの実体化は禁止とする
	//IS_FunctionOperator::Typeを実体化する事
	template <auto ...t_Fns>
	struct IS_FunctionMultipleOperatorStatic
	{
		using Fns = typename IS_FunctionMultiple_Helper<std::remove_const_t<decltype(t_Fns)>...>::Fns;
		

		template<size_t _Index>
		using Fns_element = std::tuple_element_t<_Index, Fns>;

		static constexpr int Fns_Num = std::tuple_size_v<Fns>;

		template<size_t _Index>
		static constexpr int Args_Num= std::tuple_size_v<typename Function<Fns_element<_Index>>::Args>;

		template<size_t _Index>
		static constexpr int Bind_Args_Num= std::tuple_size_v<typename Function<Fns_element<_Index>>::BindArgs>;

		template<size_t _Index>
		static constexpr int Request_Args_Num= Args_Num<_Index>- std::tuple_size_v<typename Function<Fns_element<_Index>>::BoundArgs>;



		//template<int t_FnCount,
		//	class T_Args_Num,//=std::index_sequence<Args_Num<t_FnCount>>,
		//	class T_Bind_Args,//= std::index_sequence<Bind_Args_Num<t_FnCount>>,
		//	class T_Request_ArgsNum,//= std::index_sequence<Request_Args_Num<t_FnCount>>,
		//	bool t_Even,//= !((sizeof...(t_Fns) + t_FnNumber) % 2),
		//	auto ...t_Fns_Remaining>
		//struct S_FunctionMultipleOperatorStatic
		//{
		//	int b;
		//};



		//template<int t_FnCount,
		//	size_t ...t_Args_Num,
		//	size_t ...t_BindArgs_Num, 
		//	size_t ...t_Request_Args_Num,
		//	bool t_Even,
		//	auto ...t_Fns_Remaining>
		//struct S_FunctionMultipleOperatorStatic<t_FnCount,
		//	std::index_sequence<t_Args_Num...>,
		//	std::index_sequence<t_BindArgs_Num...>,
		//	std::index_sequence<t_Request_Args_Num...>,
		//	t_Even,t_Fns_Remaining...>
		//{
		//	template<auto t_Fn, std::tuple_element<t_BindArgs_Num, typename Fns_element<Fns_Num - 1>::BindArgs>::type... t_Args, auto ...t_Fns_Remaining>
		//	struct S:
		//		public FunctionStatic<t_Fn,t_Args...>,
		//		public S_FunctionMultipleOperatorStatic
		//		<
		//			t_FnCount + 1,
		//			std::make_index_sequence<Args_Num<t_FnCount + 1>>,
		//			std::make_index_sequence<Bind_Args_Num<t_FnCount + 1>>,
		//			std::make_index_sequence<Request_Args_Num<t_FnCount + 1>>,
		//			!((Fns_Num + t_FnCount) % 2),
		//			t_Fns_Remaining...
		//		>::Type
		//	{
		//		using FunctionStatic<t_Fn, t_Args...>::operator();

		//		using S_FunctionMultipleOperatorStatic
		//			<
		//			t_FnCount + 1,
		//			std::make_index_sequence<Args_Num<t_FnCount + 1>>,
		//			std::make_index_sequence<Bind_Args_Num<t_FnCount + 1>>,
		//			std::make_index_sequence<Request_Args_Num<t_FnCount + 1>>,
		//			!((Fns_Num + t_FnCount) % 2),
		//			t_Fns_Remaining...
		//			>::Type::operator();
		//	
		//	};

		//	using Type = S<t_Fns_Remaining...>;
		//};

		//template<//int t_FnCount,
		//	size_t ...t_Args_Num,
		//	size_t ...t_BindArgs_Num,
		//	size_t ...t_Request_Args_Num,
		//	bool t_Even,
		//	auto ...t_Fns_Remaining>
		//struct S_FunctionMultipleOperatorStatic<Fns_Num-1,
		//	std::index_sequence<t_Args_Num...>,
		//	std::index_sequence<t_BindArgs_Num...>,
		//	std::index_sequence< t_Request_Args_Num...>,
		//	t_Even, t_Fns_Remaining...>
		//{
		//	template<auto t_Fn,std::tuple_element<t_BindArgs_Num, typename Fns_element<Fns_Num - 1>::BindArgs>::type... t_Args,auto ...t_Fns_Remaining>
		//	struct S :
		//		public IS_FunctionOperator_Static<t_Fn,t_Args...>::Type
		//		//public FunctionStatic<t_Fn, t_Args...>
		//	{
		//		using MethodData =S_MethodData<std::remove_const_t<decltype(t_Fn)>, decltype(t_Args)...>;
		//		using Args = MethodData::Args;
		//		using RType = MethodData::RType;
		//		//仕様
		//		//静的な状態で関数にアクセスする
		//		static constexpr RType Execution(std::tuple_element_t<t_Request_Args_Num, Args>... args)
		//			requires same_as<std::true_type, typename MethodData::Root>
		//		{
		//			return (h->*t_Fn)(args..., t_Args...);
		//		}

		//		static constexpr RType Execution(std::tuple_element_t<t_Request_Args_Num, Args>... args)
		//			requires same_as<std::false_type, typename MethodData::Root>
		//		{
		//			return t_Fn.Execution(args..., t_Args...);
		//		}

		//		constexpr RType operator()(std::tuple_element_t<t_Request_Args_Num, Args>... args)
		//		{
		//			return Execution(args...);
		//		}
		//	};

		//	using Type = S<t_Fns_Remaining...>;

		//
		//};


using Type = int;
			//S_FunctionMultipleOperatorStatic<0,
		/*	std::make_index_sequence<static_cast<int>(Args_Num<0>)>,
			std::make_index_sequence<static_cast<int>(Bind_Args_Num<0>)>,
			std::make_index_sequence<static_cast<int>(Request_Args_Num<0>)>,
			static_cast<bool>(!(Fns_Num % 2)),
			t_Fns...>::Type;*/
	};

}