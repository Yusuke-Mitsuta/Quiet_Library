#pragma once

#include"Function_Operator_Helper.h"

#include"Parts.h"


namespace N_Function
{
	template<class ...T_Parts>
	struct I_Function_Operator
	{
		using fn_multi_data = I_Function_Multiple_Helper<T_Parts...>;

		using core = Function_Core<typename fn_multi_data::type>;

		struct S_Function_Operator_Core
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


			constexpr auto Action_Operator(auto fn, auto ...args)
			{
				return fn(args...);
			};

			constexpr S_Function_Operator_Core(auto... args) :
				data(args...) {
			}

		};

		template<
			class T_access_number ,
			class T_request_pointer ,
			class T_request_args ,
			class T_request_args_number,
			class T_Next>
		struct S_Function_Operator;

		template<
			size_t ...t_access_number,
			class T_request_args,
			size_t ...t_request_args_number,
			class T_Next>
		struct S_Function_Operator<tuple_v<t_access_number...>,
			invalid_t, T_request_args, tuple_v<t_request_args_number...>, T_Next> :
			T_Next
		{
			constexpr auto operator()(N_Tuple::U_Element_t<t_request_args_number,T_request_args>... args)
			{
				return S_Function_Operator_Core::Action_Operator(std::get<t_access_number>(S_Function_Operator_Core::data)..., args...);
			}

			using T_Next::operator();

			constexpr S_Function_Operator(auto... args) :
				T_Next(args...) 
			{
				TYPE_ID(T_request_args);
				TYPE_ID(tuple_v<t_request_args_number...>);
			
			}


		};

		template<
			size_t ...t_access_number,
			class T_request_pointer,
			class T_request_args,
			size_t ...t_request_args_number,
			class T_Next>
		struct S_Function_Operator<tuple_v<t_access_number...>,
			T_request_pointer, T_request_args, tuple_v<t_request_args_number...>, T_Next> :
			T_Next
		{
			constexpr auto operator()(T_request_pointer p, N_Tuple::U_Element_t<t_request_args_number, T_request_args>... args)
			{
				return S_Function_Operator_Core::Action_Operator(p,std::get<t_access_number>(S_Function_Operator_Core::data)..., args...);
			}

			using T_Next::operator();

			constexpr S_Function_Operator(auto... args) :
				T_Next(args...) {}
		};

		template<
			size_t ...t_access_number,
			class T_request_args,
			size_t ...t_request_args_number>
		struct S_Function_Operator<tuple_v<t_access_number...>,
			invalid_t, T_request_args, tuple_v<t_request_args_number...>, S_Function_Operator_Core> :
			S_Function_Operator_Core
		{
			constexpr auto operator()(N_Tuple::U_Element_t<t_request_args_number, T_request_args>... args)
			{
				return S_Function_Operator_Core::Action_Operator(std::get<t_access_number>(S_Function_Operator_Core::data)..., args...);
			}
			constexpr S_Function_Operator(auto... args) :
				S_Function_Operator_Core(args...) 
			{
				TYPE_ID(T_request_args);
				TYPE_ID(tuple_v<t_request_args_number...>);
			}
		};

		template<
			size_t ...t_access_number,
			class T_request_pointer,
			class T_request_args,
			size_t ...t_request_args_number>
		struct S_Function_Operator<tuple_v<t_access_number...>,
			T_request_pointer, T_request_args, tuple_v<t_request_args_number...>, S_Function_Operator_Core> :
			S_Function_Operator_Core
		{
			constexpr auto operator()(T_request_pointer p, N_Tuple::U_Element_t<t_request_args_number, T_request_args>... args)
			{
				return S_Function_Operator_Core::Action_Operator(p, std::get<t_access_number>(S_Function_Operator_Core::data)..., args...);
			}

			constexpr S_Function_Operator(auto... args) :
				S_Function_Operator_Core(args...) 
			{
				TYPE_ID(T_request_args);
				TYPE_ID(T_request_pointer);
				TYPE_ID(tuple_v<t_request_args_number...>);
			}
		};



		template<
			class T_access_number = typename fn_multi_data::access_number,
			class T_request_pointer = typename core::request_pointer,
			class T_request_args = typename core::request_args>
		struct S_Function_Operator_Helper;


		template<
			size_t ...t_access_number,
			class T_request_pointer,
			class T_request_args>
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>>,
			T_request_pointer,T_request_args>
		{
			using type = S_Function_Operator <
				tuple_v<t_access_number...>,
				T_request_pointer, 
				T_request_args,
				N_Tuple::U_index_sequence<T_request_args::head_size + not_is_invalid<typename T_request_args::type>>, 
				S_Function_Operator_Core>;
		};


		template<>
		struct S_Function_Operator_Helper<
			tuple_t<>,
			tuple_t<>,
			tuple_t<>>
		{
			using type = S_Function_Operator_Core;
		};




		template<
			size_t ...t_access_number,
			class ...T_access_number,
			class T_Flont_request_pointer,
			class ...T_request_pointer,
			class T_Flont_request_args,
			class ...T_request_args >
			requires (sizeof...(T_request_pointer) >= sizeof...(T_access_number))
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>, T_access_number...>,
			tuple_t<T_Flont_request_pointer,T_request_pointer...>, 
			tuple_t<T_Flont_request_args,T_request_args...>>
		{

			using next = S_Function_Operator_Helper<
				tuple_t<tuple_v<t_access_number...>, T_access_number...>,
				tuple_t<T_request_pointer...>,
				tuple_t<T_request_args...>>::type;

			using type = S_Function_Operator<
				tuple_v<t_access_number...>,
				T_Flont_request_pointer,T_Flont_request_args,
				N_Tuple::U_index_sequence<T_Flont_request_args::head_size + not_is_invalid<typename T_Flont_request_args::type>>,
				next>;
		};


		template<
			size_t ...t_access_number,
			class ...T_access_number,
			class ...T_request_pointer,
			class ...T_request_args >
			requires requires
		{
			requires (sizeof...(T_request_pointer) < sizeof...(T_access_number)+1);
			requires (sizeof...(T_request_pointer) != 0);
		}
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>, T_access_number...>,
			tuple_t<T_request_pointer...>,
			tuple_t<T_request_args...>>
		{
			using type = S_Function_Operator_Helper<
				tuple_t<T_access_number...>,
				tuple_t<T_request_pointer...>,
				tuple_t<T_request_args...>>::type;
		};


		template<
			size_t ...t_access_number,
			class ...T_access_number,
			class ...T_request_pointer,
			class ...T_Second_request_pointer,
			class ...T_request_args,
			class ...T_Second_request_args>
			requires (sizeof...(T_Second_request_pointer) >= sizeof...(T_access_number) )
		struct S_Function_Operator_Helper <
			tuple_t<tuple_v<t_access_number...>, T_access_number...>,
			tuple_t < tuple_t<T_request_pointer...>, T_Second_request_pointer... > ,
			tuple_t<tuple_t<T_request_args...>,T_Second_request_args...>>
		{
			using type = S_Function_Operator_Helper<
				tuple_t<tuple_v<t_access_number...>, T_access_number...>,
				tuple_t<T_request_pointer..., T_Second_request_pointer...>,
				tuple_t<T_request_args..., T_Second_request_args...>>::type;
		};

		using type = S_Function_Operator_Helper<>::type;

	};
}

