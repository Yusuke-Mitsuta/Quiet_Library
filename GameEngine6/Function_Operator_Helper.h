#pragma once

#include"Tuple.h"
#include"Function_Single_Data.h"

namespace N_Function
{
	template<class ...T_Fn_Parts>
	struct I_Function_Base_Data;

	template<class ...T_Fn_Parts>
	struct Function_Core;

	template<class ...T_Parts>
	struct I_Function_Operator_Helper
	{
		using fn_multi_data = I_Function_Multiple_Helper<T_Parts...>;

		using core = Function_Core<typename fn_multi_data::type>;


		template<
			class T_access_number,
			class T_request_pointer,
			class T_request_args,
			class T_request_args_number,
			class T_Next>
		struct S_Function_Operator;

		template<
			size_t ...t_access_number,
			class T_request_pointer,
			class T_request_args,
			size_t ...t_request_args_number,
			class T_Next>
		struct S_Function_Operator<tuple_v<t_access_number...>,
			T_request_pointer, T_request_args, tuple_v<t_request_args_number...>, T_Next>
		{
			using data = tuple_t<tuple_v<t_access_number...>, T_request_pointer, tuple_t<N_Tuple::U_Element_t<t_request_args_number, T_request_args>...>>;

			using type = T_Next;

			constexpr S_Function_Operator(auto... args) :
				T_Next(args...) {}
		};

		template<
			class T_access_number = typename fn_multi_data::access_number,
			class T_request_pointer = typename core::request_pointer,
			class T_request_args = typename core::request_args>
		struct S_Function_Operator_Helper
		{
			using type = 
				S_Function_Operator_Helper;
		};


		template<
			class T_access_number,
			class T_request_pointer,
			class T_request_args>
			requires requires
		{
			requires T_access_number::size == 1;
		}
		struct S_Function_Operator_Helper<
			T_access_number,
			T_request_pointer,
			T_request_args>
		{
			using type = S_Function_Operator<
				typename T_access_number::type,
				T_request_pointer, T_request_args,
				N_Tuple::U_index_sequence<T_request_args::head_size +
				not_is_invalid<typename T_request_args::type>>,
				invalid_t>;
		};

		template<
			size_t ...t_access_number,
			class T_request_pointer,
			class T_request_args>
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>>,
			tuple_t<T_request_pointer>,
			tuple_t<T_request_args>> :
			S_Function_Operator_Helper<tuple_t<tuple_v<t_access_number...>>,
			T_request_pointer,T_request_args>{};


		template<
			size_t ...t_access_number,
			class ...T_access_number,
			class T_Flont_request_pointer,
			class ...T_request_pointer,
			class T_Flont_request_args,
			class ...T_request_args >
			requires requires
		{
			requires (sizeof...(T_request_pointer) >= sizeof...(T_access_number));
		}
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>, T_access_number...>,
			tuple_t<T_Flont_request_pointer, T_request_pointer...>,
			tuple_t<T_Flont_request_args, T_request_args...>>
		{

			using next = S_Function_Operator_Helper<
				tuple_t<tuple_v<t_access_number...>, T_access_number...>,
				tuple_t<T_request_pointer...>,
				tuple_t<T_request_args...>>::type;

			using type = S_Function_Operator<
				tuple_v<t_access_number...>,
				T_Flont_request_pointer, T_Flont_request_args,
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
			requires (sizeof...(T_request_pointer) < sizeof...(T_access_number) + 1);
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
			requires requires
		{
			requires (sizeof...(T_request_pointer) >= sizeof...(T_access_number));
		}
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>, T_access_number...>,
			tuple_t<tuple_t<T_request_pointer...>, T_Second_request_pointer...>,
			tuple_t<tuple_t<T_request_args...>, T_Second_request_args...>>
		{
			using type = S_Function_Operator_Helper<
				tuple_t<tuple_v<t_access_number...>, T_access_number...>,
				tuple_t<T_request_pointer..., T_Second_request_pointer...>,
				tuple_t<T_request_args..., T_Second_request_args...>>::type;
		};

		template<class T_Result=tuple_t<> ,class T_Operator_Data =typename S_Function_Operator_Helper<>::type>
		struct S_Function_Operator_Parameter
		{
			using type = T_Result;
		};

		template<class ...T_Result, not_is_invalid T_Operator_Data>
		struct S_Function_Operator_Parameter<tuple_t<T_Result...>, T_Operator_Data>
		{
			using type = S_Function_Operator_Parameter<
				tuple_t<T_Result..., typename T_Operator_Data::data>,
				typename T_Operator_Data::type>::type;
		};


		using type =S_Function_Operator_Parameter<>::type;

	};


}










