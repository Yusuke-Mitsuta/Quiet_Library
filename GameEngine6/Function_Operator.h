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

			constexpr auto Action_Operator(auto* p, auto method, auto ...args)
				requires (same_as_template_type<Method_Core, decltype(method)>)
			{
				return method(p, args...);
			};


			constexpr auto Action_Operator(auto fn, auto ...args)
			{

				return fn(args...);
			};

		};

		template<class T_Tuple_Function_Operator>
		struct S_Function_Operator :
			S_Function_Operator_Core
		{

			constexpr auto operator()()
			{
			}

			constexpr S_Function_Operator(auto... args) :
				S_Function_Operator_Core(args...) {}
		};

		template<class T_Request_Args,size_t... t_request_args_number,size_t... t_bind_args_number,class ...T_Function_Operator_data_list>
		struct S_Function_Operator<tuple_t<tuple_t<T_Request_Args,tuple_v<t_request_args_number...>,tuple_v<t_bind_args_number...>>,
		T_Function_Operator_data_list...>> :
			S_Function_Operator<tuple_t<T_Function_Operator_data_list...>>
		{


			constexpr auto operator()(N_Tuple::U_Element_t<t_request_args_number, T_Request_Args>... args)
			{
				return S_Function_Operator_Core::Action_Operator(std::get<t_bind_args_number>(S_Function_Operator_Core::bind_list)..., args...);
			}

			using S_Function_Operator<tuple_t<T_Function_Operator_data_list...>>::operator();
			constexpr S_Function_Operator(auto... args) :
				S_Function_Operator<tuple_t<T_Function_Operator_data_list...>>(args...) {



				C_OUT("a");
				TYPE_ID(T_Request_Args);

			}
		};

		using type = S_Function_Operator<typename I_Function_Operator_Helper<T_Fns>::type>;

	};

}


namespace N_Function
{
	template<class T_Fns, class T_Bind_Args_Type>
	struct I_Function_Operator_2
	{
		
		template<class T_Fn,
			class T_request_data_numbers,
			class T_request_pointer,
			class T_request_args
		>
		struct S_Function_Operator
		{

		};

		template<class T_Fn>
		struct S_Function_Operator_Access;


		template<class T_Flont_Fn,class ...T_Fn>
		struct S_Function_Operator_Access<tuple_t<T_Flont_Fn, T_Fn...>>
		{
		};

	};
}