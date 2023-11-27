#pragma once

#include"Function_Operator_Helper.h"


namespace N_Function
{
	template<class T_Fns, class T_Bind_Args_Type>
	struct I_Function_Operator
	{

		struct S_Function_Operator_Core
		{

			//protected:
			T_Bind_Args_Type::tuple bind_list;


			constexpr S_Function_Operator_Core(auto... args) :
				bind_list(args...) {}

			constexpr auto Action_Operator(auto* p, auto method, auto ...args)
				requires (std::is_member_function_pointer_v<decltype(method)>)
			{
				return (p->*method)(args...);
			};

			//constexpr auto Action_Operator(auto* p, auto method, auto ...args)
			//	requires (same_as_template_type<Method_Core, decltype(method)>)
			//{
			//	return method(p, args...);
			//};


			constexpr auto Action_Operator(auto fn, auto ...args)
			{

				return fn(args...);
			};

		};

		template<class T_Tuple_Function_Operator_data,class T_Select_data = typename T_Tuple_Function_Operator_data::type>
		struct S_Function_Operator :
			S_Function_Operator_Core
		{
			constexpr auto operator()(T_Select_data a)
			{
				C_OUT("5");
			}

			constexpr S_Function_Operator(auto... args) :
				S_Function_Operator_Core(args...) {}
		};

		template<class T_Tuple_Function_Operator_data, class T_Request_Args,size_t... t_request_args_number,size_t... t_bind_args_number>
		struct S_Function_Operator<T_Tuple_Function_Operator_data,tuple_t<T_Request_Args,tuple_v<t_request_args_number...>,tuple_v<t_bind_args_number...>>> :
			S_Function_Operator<typename T_Tuple_Function_Operator_data::next>
		{


			constexpr auto operator()(N_Tuple::U_Element_t<t_request_args_number, T_Request_Args>... args)
			{
				return S_Function_Operator_Core::Action_Operator(std::get<t_bind_args_number>(S_Function_Operator_Core::bind_list)..., args...);
			}

			using ty = tuple_t<N_Tuple::U_Element_t<t_request_args_number, T_Request_Args>...>;

			constexpr S_Function_Operator(auto... args) :
				S_Function_Operator<typename T_Tuple_Function_Operator_data::next>(args...) {




			}
		};

		using t = I_Function_Operator_Helper<T_Fns>::type;
		using type = S_Function_Operator<typename I_Function_Operator_Helper<T_Fns>::type>;

	};

}
