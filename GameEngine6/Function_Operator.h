#pragma once

#include"Function_Operator_Helper.h"

namespace N_Function
{

	//仕様
	//[T_Parts...]から全通りのoperator()を持つクラスを作る
	//
	//テンプレート
	//[T_Parts...]::[Funcsion]の引数の型
	// 
	//using
	//[type]でそのクラスにアクセスする
	template<class ...T_Parts>
	struct I_Function_Operator
	{

		template<class T_Operator_Parameter =typename I_Function_Operator_Helper<T_Parts...>::type>
		struct S_Function_Operator
		{
			std::tuple<T_Parts...> data;

			//constexpr auto Action_Operator(auto* p, auto method, auto ...args)
			//	requires (std::is_member_function_pointer_v<decltype(method)>)
			//{
			//	return (p->*method)(args...);
			//};
			//
			//constexpr auto Action_Operator(auto* p, auto method, auto ...args)
			//{
			//	return method(p, args...);
			//};

			constexpr auto operator()() {}

			constexpr auto Action_Operator(auto fn, auto ...args)
			{
				return fn(args...);
			};
			
			constexpr S_Function_Operator(auto... args)
				:data(args...) 
			{
			}
		};


		template<
			size_t ...t_access_number,
			class T_request_pointer,
			class ...T_request_args,
			class ...T_Operator_Parameters>
		struct S_Function_Operator<
			tuple_t<
				tuple_t<
				tuple_v<t_access_number...>, 
				T_request_pointer, 
				tuple_t< T_request_args...>>,
			T_Operator_Parameters...>> :
			S_Function_Operator<tuple_t<T_Operator_Parameters...>>
		{

			constexpr auto operator()(T_request_args... args)
			{
				
				return S_Function_Operator<tuple_t<>>::Action_Operator(std::get<t_access_number>(S_Function_Operator<tuple_t<>>::data)..., args...);
			}

			using S_Function_Operator<tuple_t<T_Operator_Parameters...>>::operator();

			constexpr S_Function_Operator(auto ...args) 
				: S_Function_Operator<tuple_t<T_Operator_Parameters...>>(args...)
			{
				TYPE_ID(tuple_t<T_request_args...>);
			}

		};

		using type = S_Function_Operator<>;

	};


}

