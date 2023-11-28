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

	template<class T_Fnsa>
	struct I_Function_Operator_Helper
	{


		template<class T_Fns,class T_Bind_Args_Numbers, class ...T_Reqest_Args_list>
		struct S_Function_Select
		{
		};

		template< class ...T_Reqest_Args_list>
		struct S_Function_Select<tuple_t<>, tuple_t<>, T_Reqest_Args_list...>
		{
			using type = tuple_t<T_Reqest_Args_list...>;

		};

		template<class T_Flont_Fn,class ...T_Fns, class T_Flont_Bind_Args_Number, class ...T_Bind_Args_Numbers, class ...T_Reqest_Args_list>
		struct S_Function_Select<tuple_t<T_Flont_Fn,T_Fns...>,tuple_t<T_Flont_Bind_Args_Number,T_Bind_Args_Numbers...>, T_Reqest_Args_list...>
		{

			template<class c_name, class T_Request_Args>
			struct S_Function_Operator_Helper_data
			{
				using data = tuple_t<N_Tuple::U_Insert<T_Request_Args, c_name*, 0>, N_Tuple::U_index_sequence<T_Request_Args::head_size + 2>, T_Flont_Bind_Args_Number>;
			};

			template<class T_Request_Args>
			struct S_Function_Operator_Helper_data<invalid_t, T_Request_Args>
			{
				using data = tuple_t<T_Request_Args, N_Tuple::U_index_sequence<T_Request_Args::head_size + 1>, T_Flont_Bind_Args_Number>;
			};


			template<
				class T_Fn_Core = T_Flont_Fn,
				size_t t_fn_count = I_Function_Single_Data<T_Fn_Core>::fn_count,
				class T_Request_Args = typename I_Function_Single_Data<T_Fn_Core>::request_args>
			struct S_Function_Operator_Helper;

			template<class T_Fn, class ...T_Bind_Args, size_t t_fn_count, class T_Request_Args>
				requires (t_fn_count == 1)
			struct S_Function_Operator_Helper<Function_Core<T_Fn, T_Bind_Args...>,t_fn_count,T_Request_Args>
			{
				using data = tuple_t<T_Request_Args, N_Tuple::U_index_sequence<T_Request_Args::head_size + 1>, T_Flont_Bind_Args_Number>;

				using type = typename S_Function_Select<tuple_t<T_Fns...>,tuple_t<T_Bind_Args_Numbers...>, T_Reqest_Args_list..., data>::type;

			};

			template<class T_Method, class ...T_Bind_Args, size_t t_fn_count, class T_Request_Args>
				requires (t_fn_count == 1)
			struct S_Function_Operator_Helper<Method_Core<T_Method, T_Bind_Args...>, t_fn_count, T_Request_Args>
			{


				using c_name = I_Function_Single_Data<T_Method>::c_name;

				using data = tuple_t<N_Tuple::U_Insert<T_Request_Args, c_name*, 0>, N_Tuple::U_index_sequence<T_Request_Args::head_size + 2>, T_Flont_Bind_Args_Number>;

				using type = typename S_Function_Select<tuple_t<T_Fns...>, tuple_t<T_Bind_Args_Numbers...>, T_Reqest_Args_list..., data>::type;

			};


			using type = S_Function_Operator_Helper<>::type;

			/*template<class T_Reqest_Args_list,class T_Fn,class T_Reqest_Args>
			struct S_request_args_expand
			{

				using type = S_Function_Operator_Helper<T_Reqest_Args_list, T_Fn, 1, T_Reqest_Args>;
			};

			template<class T_Reqest_Args_list, class T_Fns>
			struct S_request_args_expand<T_Reqest_Args_list, T_Fns, tuple_t<>>
			{
				using type = T_Reqest_Args_list;
			};

			template<class T_Reqest_Args_list, class T_Fns, class T_Flont_Reqest_Args, class ...T_Tuple_Reqest_Args>
			struct S_request_args_expand<T_Reqest_Args_list,T_Fns, tuple_t<T_Flont_Reqest_Args,T_Tuple_Reqest_Args...>>
			{
				using next = S_request_args_expand<T_Reqest_Args_list, T_Fns, tuple_t<T_Tuple_Reqest_Args...>>;

				using type = S_request_args_expand<next,
					T_Fns, T_Flont_Reqest_Args>::type;
			};

			template<class T_Reqest_Args_list, class T_Method, class ...T_Bind_Args, class ...T_Tuple_Reqest_Args>
			struct S_request_args_expand<T_Reqest_Args_list, Method_Core<T_Method, T_Bind_Args...>, tuple_t<T_Tuple_Reqest_Args...>>
			{
				using type = S_request_args_expand<T_Reqest_Args_list, T_Method, tuple_t<T_Tuple_Reqest_Args...>>::type;
			};

			template<class T_Reqest_Args_list,class T_Flont_Method,class ...T_Methods, class ...T_Bind_Args,class T_Flont_Reqest_Args, class ...T_Tuple_Reqest_Args>
			struct S_request_args_expand<T_Reqest_Args_list, Method_Core<tuple_t<T_Flont_Method,T_Methods...>, T_Bind_Args...>,tuple_t<T_Flont_Reqest_Args,T_Tuple_Reqest_Args...>>
			{
				using next = S_request_args_expand<T_Reqest_Args_list, Method_Core<tuple_t<T_Methods...>, T_Bind_Args...>, tuple_t<T_Tuple_Reqest_Args...>>;

				using type = S_request_args_expand<next, 
					T_Flont_Method, T_Flont_Reqest_Args>::type;
			};

			template<class T_Reqest_Args_list,class T_Fns, size_t t_fn_count, class T_Request_Args>
				requires (t_fn_count > 1)
			struct S_Function_Operator_Helper<T_Reqest_Args_list,T_Fns, t_fn_count, T_Request_Args>
			{
				using type = S_request_args_expand<T_Next_operator, T_Fns, T_Request_Args>::type;
			};*/


		};


		using type = typename S_Function_Select<N_Tuple::U_Element_t<0,T_Fnsa>, N_Tuple::U_Element_t<1, T_Fnsa>>::type;


	};


}

/*
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

	template<class T_Fnsa>
	struct I_Function_Operator_Helper
	{


		template<class T_Fns,class T_Bind_Args_Numbers, class ...T_Reqest_Args_list>
		struct S_Function_Select
		{
		};

		template< class ...T_Reqest_Args_list>
		struct S_Function_Select<tuple_t<>, tuple_t<>, T_Reqest_Args_list...>
		{
			using type = tuple_t<T_Reqest_Args_list...>;

		};

		template<class T_Flont_Fn,class ...T_Fns, class T_Flont_Bind_Args_Number, class ...T_Bind_Args_Numbers, class ...T_Reqest_Args_list>
		struct S_Function_Select<tuple_t<T_Flont_Fn,T_Fns...>,tuple_t<T_Flont_Bind_Args_Number,T_Bind_Args_Numbers...>, T_Reqest_Args_list...>
		{

			template<class c_name, class T_Request_Args>
			struct S_Function_Operator_Helper_data
			{
				using data = tuple_t<N_Tuple::U_Insert<T_Request_Args, c_name*, 0>, N_Tuple::U_index_sequence<T_Request_Args::head_size + 2>, T_Flont_Bind_Args_Number>;
			};

			template<class T_Request_Args>
			struct S_Function_Operator_Helper_data<invalid_t, T_Request_Args>
			{
				using data = tuple_t<T_Request_Args, N_Tuple::U_index_sequence<T_Request_Args::head_size + 1>, T_Flont_Bind_Args_Number>;
			};


			template<
				class T_Fn_Core = T_Flont_Fn,
				size_t t_fn_count = I_Function_Single_Data<T_Fn_Core>::fn_count,
				class T_Request_Args = typename I_Function_Single_Data<T_Fn_Core>::request_args>
			struct S_Function_Operator_Helper
			{

				using c_name = I_Function_Single_Data<T_Fn_Core>::c_name;

				using data = S_Function_Operator_Helper_data<invalid_t, T_Request_Args>::type;

				using type = typename S_Function_Select<tuple_t<T_Fns...>, tuple_t<T_Bind_Args_Numbers...>, T_Reqest_Args_list..., data>::type;
			};


			using type = S_Function_Operator_Helper<>::type;

			template<class T_Reqest_Args_list,class T_Fn,class T_Reqest_Args>
			struct S_request_args_expand
			{

				using type = T_Reqest_Args_list;// S_Function_Operator_Helper<T_Reqest_Args_list, T_Fn, 1, T_Reqest_Args>;
			};

			template<class ...T_Reqest_Args_list, class T_Fn>
			struct S_request_args_expand<tuple_t<T_Reqest_Args_list...>, T_Fn, tuple_t<>>
			{
				using type = tuple_t<T_Reqest_Args_list...>;
			};


			template<class ...T_Reqest_Args_list, class T_Fn, class T_Reqest_Args>
			struct S_request_args_expand<tuple_t<T_Reqest_Args_list...>, T_Fn, T_Reqest_Args>
			{

				using c_name = I_Function_Single_Data<T_Fn>::c_name;
				using data = S_Function_Operator_Helper_data<c_name, T_Reqest_Args>::type;

				using type = tuple_t<T_Reqest_Args_list..., data>;
			};



			template<class ...T_Reqest_Args_list, class T_Fn, class T_Flont_Reqest_Args, class ...T_Tuple_Reqest_Args>
			struct S_request_args_expand<tuple_t<T_Reqest_Args_list...>,T_Fn, tuple_t<T_Flont_Reqest_Args,T_Tuple_Reqest_Args...>>
			{

				using child_reqest_args_list = S_request_args_expand<tuple_t<T_Reqest_Args_list...>, T_Fn, T_Flont_Reqest_Args>::type;


				using type = S_request_args_expand<N_Tuple::U_Merge_tuple_expand<tuple_t<T_Reqest_Args_list...>, child_reqest_args_list>,
					T_Fn, tuple_t<T_Tuple_Reqest_Args...>>;
			};

			template<class ...T_Reqest_Args_list, class T_Method, class ...T_Bind_Args, class ...T_Tuple_Reqest_Args>
			struct S_request_args_expand<tuple_t<T_Reqest_Args_list...>, Method_Core<T_Method, T_Bind_Args...>, tuple_t<T_Tuple_Reqest_Args...>>
			{
				using type = S_request_args_expand<tuple_t<T_Reqest_Args_list...>, T_Method, tuple_t<T_Tuple_Reqest_Args...>>::type;
			};


			template<class ...T_Reqest_Args_list,class T_Flont_Method,class ...T_Methods, class ...T_Bind_Args,class T_Flont_Reqest_Args, class ...T_Tuple_Reqest_Args>
			struct S_request_args_expand<tuple_t<T_Reqest_Args_list...>, Method_Core<tuple_t<T_Flont_Method,T_Methods...>, T_Bind_Args...>,tuple_t<T_Flont_Reqest_Args,T_Tuple_Reqest_Args...>>
			{
				using child_reqest_args_list = S_request_args_expand<tuple_t<T_Reqest_Args_list...>,T_Flont_Method, T_Flont_Reqest_Args>::type;

				using type = S_request_args_expand<N_Tuple::U_Merge_tuple_expand<tuple_t<T_Reqest_Args_list...>, child_reqest_args_list>,
					Method_Core<tuple_t<T_Methods...>, T_Bind_Args...>, tuple_t<T_Tuple_Reqest_Args...>>;
			};



			template<class ...T_Reqest_Args_list, class T_Flont_Method, class ...T_Methods, class ...T_Bind_Args, class T_Flont_Reqest_Args, class ...T_Tuple_Reqest_Args>
				requires(I_Function_Single_Data<T_Flont_Method>::fn_count == 1)
			struct S_request_args_expand<tuple_t<T_Reqest_Args_list...>, Method_Core<tuple_t<T_Flont_Method, T_Methods...>, T_Bind_Args...>, tuple_t<T_Flont_Reqest_Args, T_Tuple_Reqest_Args...>>
			{
				using c_name = I_Function_Single_Data<T_Flont_Method>::c_name;

				using data = S_Function_Operator_Helper_data<c_name, T_Flont_Reqest_Args>::type;

				using type = S_request_args_expand<tuple_t<T_Reqest_Args_list...,data>, Method_Core<tuple_t<T_Methods...>, T_Bind_Args...>, tuple_t<T_Tuple_Reqest_Args...>>::type;

			};




			//template<class T_Fns, size_t t_fn_count, class T_Request_Args>
			//	requires (t_fn_count > 1)
			//struct S_Function_Operator_Helper<T_Fns, t_fn_count, T_Request_Args>
			//{
			//	using type = int;
			//		//S_request_args_expand<tuple_t<>,T_Fns, T_Request_Args>::type;
			//};
			using type = S_Function_Operator_Helper<>::type;

		};


		using type = typename S_Function_Select<N_Tuple::U_Element_t<0,T_Fnsa>, N_Tuple::U_Element_t<1, T_Fnsa>>::type;


	};


}
*/