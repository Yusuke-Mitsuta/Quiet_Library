#pragma once

#include"Tuple.h"
#include"Function_Single_Data.h"

namespace N_Function
{
	template<class ...T_Fn_Parts>
	struct I_Function_Single_Data;

	template<class ...T_Fn_Parts>
	struct Function_Core;

	template<class ...T_Method_Parts>
	struct Method_Core;

	template<class T_Fns>
	struct I_Function_Operator_Helper
	{


		template<class T_Fns,class T_Bind_Args_Numbers>
		struct S_Function_Select
		{


			template<
				class T_Next_operator,
				class T_Fn_Core,
				size_t t_fn_count,
				class T_Request_Args>
				struct S_Function_Operator_Helper;

			template<
				class T_Next_operator = typename S_Function_Select<typename T_Fns::next, typename T_Bind_Args_Numbers::next>,
				class T_Fn_Core = typename T_Fns::type,
				size_t t_fn_count = I_Function_Single_Data<T_Fn_Core>::fn_count,
				class T_Request_Args = typename I_Function_Single_Data<T_Fn_Core>::request_args>
			struct S_Function_Operator_Helper
			{

				using type = tuple_t<>;

			};

			using type = S_Function_Operator_Helper<>::type;

			template<class T_Next_operator,class T_Fn, class ...T_Bind_Args, size_t t_fn_count, class T_Request_Args>
				requires (t_fn_count == 1)
			struct S_Function_Operator_Helper<T_Next_operator,Function_Core<T_Fn, T_Bind_Args...>,t_fn_count,T_Request_Args>
			{

				using next = T_Next_operator::type;

				using data = tuple_t<T_Request_Args, N_Tuple::U_index_sequence<T_Request_Args::head_size+1>,typename T_Bind_Args_Numbers::type>;

				using type = N_Tuple::U_Insert<next, data,0>;
				


				//constexpr auto operator()(N_Tuple::U_Element_t<t_request_args_numbers, T_Request_Args>... args)
				//{
				//	return S_Function_Operator_Core::Action_Operator(std::get<t_bind_args_numbers>(S_Function_Operator_Core::bind_list)..., args...);

				//}

				//constexpr S_Function_Operator_Helper(auto... args) :
				//	T_Next_operator::type(args...) 
				//		{C_OUT("Function_op");
				//this->operator()(3);
				//}
			};

			template<class T_Next_operator, class T_Method, class ...T_Bind_Args, size_t t_fn_count, class T_Request_Args>
				requires (t_fn_count == 1)
			struct S_Function_Operator_Helper<T_Next_operator, Method_Core<T_Method, T_Bind_Args...>, t_fn_count, T_Request_Args>
			{


				using c_name = I_Function_Single_Data<T_Method>::c_name;

				using next = T_Next_operator::type;

				
				using data = tuple_t<N_Tuple::U_Insert<T_Request_Args,c_name*,0>, N_Tuple::U_index_sequence<T_Request_Args::head_size+2>,typename T_Bind_Args_Numbers::type>;

				using type = N_Tuple::U_Insert<next, data>;



				//constexpr auto operator()(c_name* pointer, N_Tuple::U_Element_t<t_request_args_numbers, T_Request_Args>... args)
				//{
				//	return S_Function_Operator_Core::Action_Operator(pointer,std::get<t_bind_args_numbers>(S_Function_Operator_Core::bind_list)..., args...);
				//}
				//
				//constexpr S_Function_Operator_Helper(auto... args) :
				//	T_Next_operator::type(args...) {
				//	C_OUT("Method_op");
				//}
			};



			template<class T_Return_type,class T_Fn,class T_Reqest_Args>
			struct S_request_args_expand
			{
				using type = S_Function_Operator_Helper<T_Return_type, T_Fn, 1, T_Reqest_Args>;
			};

			template<class T_Return_type, class T_Fns>
			struct S_request_args_expand<T_Return_type, T_Fns, tuple_t<>>
			{
				using type = T_Return_type;
			};

			template<class T_Return_type, class T_Fns, class T_Flont_Reqest_Args, class ...T_Tuple_Reqest_Args>
			struct S_request_args_expand<T_Return_type,T_Fns, tuple_t<T_Flont_Reqest_Args,T_Tuple_Reqest_Args...>>
			{
				using next = S_request_args_expand<T_Return_type, T_Fns, tuple_t<T_Tuple_Reqest_Args...>>;

				using type = S_request_args_expand<next,
					T_Fns, T_Flont_Reqest_Args>::type;
			};

			template<class T_Return_type, class T_Method, class ...T_Bind_Args, class ...T_Tuple_Reqest_Args>
			struct S_request_args_expand<T_Return_type, Method_Core<T_Method, T_Bind_Args...>, tuple_t<T_Tuple_Reqest_Args...>>
			{
				using type = S_request_args_expand<T_Return_type, T_Method, tuple_t<T_Tuple_Reqest_Args...>>::type;
			};

			template<class T_Return_type,class T_Flont_Method,class ...T_Methods, class ...T_Bind_Args,class T_Flont_Reqest_Args, class ...T_Tuple_Reqest_Args>
			struct S_request_args_expand<T_Return_type, Method_Core<tuple_t<T_Flont_Method,T_Methods...>, T_Bind_Args...>,tuple_t<T_Flont_Reqest_Args,T_Tuple_Reqest_Args...>>
			{
				using next = S_request_args_expand<T_Return_type, Method_Core<tuple_t<T_Methods...>, T_Bind_Args...>, tuple_t<T_Tuple_Reqest_Args...>>;

				using type = S_request_args_expand<next, 
					T_Flont_Method, T_Flont_Reqest_Args>::type;
			};

			template<class T_Next_operator, class T_Fns, size_t t_fn_count, class T_Request_Args>
				requires (t_fn_count > 1)
			struct S_Function_Operator_Helper<T_Next_operator,T_Fns, t_fn_count, T_Request_Args>
			{
				using type = S_request_args_expand<T_Next_operator, T_Fns, T_Request_Args>::type;
			};


		};

		using type = S_Function_Select<typename T_Fns::type, typename T_Fns::next::type>::type;


	};


}