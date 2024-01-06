#pragma once

#include<utility>
#include"Function_Operator_Helper.h"
#include"Function_Operator_Sort.h"

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
	private:
	public:
		using function_operator_data = typename I_Function_Operator_Helper<T_Parts...>::type;
		using function_operator_sort = typename I_Function_Operator_Sort<function_operator_data>::type;
		template<class T_Operator_Parameter = function_operator_sort,
		class T_Access_Number = N_Tuple::U_Element_t<0,typename T_Operator_Parameter::type>,
		class T_Request_Args = N_Tuple::U_Element_t<1,typename T_Operator_Parameter::type>,
		class T_Request_Pointer = N_Tuple::U_Element_t<2,typename T_Operator_Parameter::type>>
		struct S_Function_Operator
		{
		protected:

			tuple_t<T_Parts...> data;

			constexpr auto operator()() {}

			constexpr auto Action_Operator(auto fn, auto ...args)
			{
				return fn(args...);
			};

			template<class T_Fn>
				requires requires
			{
				requires std::is_member_function_pointer_v<T_Fn>;
			}
			constexpr auto Action_Operator( T_Fn fn, auto* p, auto ...args)
			{
				return (p->*fn)(args...);
			};

			template<class T_Fn>
				requires requires
			{
				requires same_as_template_type<std::remove_pointer_t<T_Fn>, Function>;
			}
			constexpr auto Action_Operator(T_Fn fn, auto ...args)
			{
				return fn->operator()(args...);
			};

			constexpr S_Function_Operator(T_Parts&& ...args)
				:data(std::forward<T_Parts>(args)...)
			{
			
			}

		};

		using operator_core = S_Function_Operator<tuple_t<>>;

		template<
			class T_Operator_Parameter,
			size_t ...t_pointer_access_number,
			size_t t_fn_access_number,
			size_t ...t_args_access_number,
			class ...T_request_args>
			requires (T_Operator_Parameter::size == 1)
		struct S_Function_Operator<
			T_Operator_Parameter,
			tuple_vp<tuple_v<t_pointer_access_number...>,t_fn_access_number,tuple_v<t_args_access_number...>>,
			tuple_t<T_request_args...>,
			invalid_t> :
		S_Function_Operator<typename T_Operator_Parameter::remove>
		{
		protected:

			constexpr auto operator()(T_request_args... args)
			{
				return operator_core::Action_Operator(
					std::get<t_fn_access_number>(operator_core::data),
					std::get<t_pointer_access_number>(operator_core::data)...,
					args...,
					std::get<t_args_access_number>(operator_core::data)...);
			}

			constexpr S_Function_Operator(T_Parts&& ...args)
				: S_Function_Operator<typename T_Operator_Parameter::remove>(std::forward<T_Parts>(args)...){}

		};

		template<
			class T_Operator_Parameter,
			size_t ...t_pointer_access_number,
			size_t t_fn_access_number,
			size_t ...t_args_access_number,
			class ...T_request_args,
			class T_request_pointer>
			requires (T_Operator_Parameter::size == 1)
		struct S_Function_Operator<
			T_Operator_Parameter,
			tuple_vp<tuple_v<t_pointer_access_number...>, t_fn_access_number, tuple_v<t_args_access_number...>>,
			tuple_t<T_request_args...>,
			T_request_pointer> :
			S_Function_Operator<typename T_Operator_Parameter::remove>
		{
		protected:

			constexpr auto operator()(T_request_pointer* p,T_request_args... args)
			{
				return operator_core::Action_Operator(
					std::get<t_fn_access_number>(operator_core::data),
					p,
					args...,
					std::get<t_args_access_number>(operator_core::data)...);
			}

			constexpr S_Function_Operator(T_Parts&& ...args)
				: S_Function_Operator<typename T_Operator_Parameter::remove>(std::forward<T_Parts>(args)...){}

		};


		template<
			class T_Operator_Parameter,
			size_t ...t_pointer_access_number,
			size_t t_fn_access_number,
			size_t ...t_args_access_number,
			class ...T_request_args>
			requires (T_Operator_Parameter::size > 1)
		struct S_Function_Operator<
			T_Operator_Parameter,
			tuple_vp<tuple_v<t_pointer_access_number...>, t_fn_access_number, tuple_v<t_args_access_number...>>,
			tuple_t<T_request_args...>,
			invalid_t> :
			S_Function_Operator<typename T_Operator_Parameter::remove>
		{
		protected:

			constexpr auto operator()(T_request_args... args)
			{
				return operator_core::Action_Operator(
					std::get<t_fn_access_number>(operator_core::data),
					std::get<t_pointer_access_number>(operator_core::data)...,
					args...,
					std::get<t_args_access_number>(operator_core::data)...);
			}

			using S_Function_Operator<typename T_Operator_Parameter::remove>::operator();

			constexpr S_Function_Operator(T_Parts&& ...args)
				: S_Function_Operator<typename T_Operator_Parameter::remove>(std::forward<T_Parts>(args)...) {}

		};

		template<
			class T_Operator_Parameter,
			size_t ...t_pointer_access_number,
			size_t t_fn_access_number,
			size_t ...t_args_access_number,
			class ...T_request_args,
			class T_request_pointer>
			requires (T_Operator_Parameter::size > 1)
		struct S_Function_Operator<
			T_Operator_Parameter,
			tuple_vp<tuple_v<t_pointer_access_number...>, t_fn_access_number, tuple_v<t_args_access_number...>>,
			tuple_t<T_request_args...>,
			T_request_pointer> :
			S_Function_Operator<typename T_Operator_Parameter::remove>
		{
		protected:

			constexpr auto operator()(T_request_pointer* p, T_request_args... args)
			{
				return operator_core::Action_Operator(
					std::get<t_fn_access_number>(operator_core::data),
					p,
					args...,
					std::get<t_args_access_number>(operator_core::data)...);
			}

			using S_Function_Operator<typename T_Operator_Parameter::remove>::operator();

			constexpr S_Function_Operator(T_Parts&& ...args)
				: S_Function_Operator<typename T_Operator_Parameter::remove>(std::forward<T_Parts>(args)...) {}
		};
		

	public:

		using type = S_Function_Operator<>;

	};


}

