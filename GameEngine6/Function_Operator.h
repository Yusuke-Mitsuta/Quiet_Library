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
		template<class T_Operator_Parameter = function_operator_sort>
		struct S_Function_Operator
		{
		protected:

			std::tuple<T_Parts...> data;

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
			constexpr auto Action_Operator(auto* p, T_Fn fn, auto ...args)
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


			template<class T_p,class T_Fn>
				requires requires
			{
				requires !same_as_template_type<T_p, Function>;
				requires same_as_template_type<std::remove_pointer_t<T_Fn>, Function>;
			}
			constexpr auto Action_Operator(T_p* p,T_Fn fn, auto ...args)
			{
				return Action_Operator(fn, p, args...);
			};

			constexpr S_Function_Operator(T_Parts&& ...args)
				:data(std::forward<T_Parts>(args)...)
			{}

		};

		template<
			size_t ...t_access_number,
			class ...T_request_args>
		struct S_Function_Operator<
			tuple_t<
			tuple_t<
			tuple_v<t_access_number...>,
			invalid_t,
			tuple_t< T_request_args...>>
			>> :
		S_Function_Operator<tuple_t<>>
		{
		protected:
			constexpr auto operator()(T_request_args... args)
			{
				return S_Function_Operator<tuple_t<>>::Action_Operator(std::get<t_access_number>(S_Function_Operator<tuple_t<>>::data)..., args...);
			}

			constexpr S_Function_Operator(T_Parts&& ...args)
				: S_Function_Operator<tuple_t<>>(std::forward<T_Parts>(args)...)
			{}

		};

		template<
			size_t ...t_access_number,
			class T_request_pointer,
			class ...T_request_args>
		struct S_Function_Operator<
			tuple_t<
			tuple_t<
			tuple_v<t_access_number...>,
			T_request_pointer,
			tuple_t< T_request_args...>>
			>> :
		S_Function_Operator<tuple_t<>>
		{
		protected:

			constexpr auto operator()(T_request_pointer* p,T_request_args... args)
			{
				return S_Function_Operator<tuple_t<>>::Action_Operator(p,std::get<t_access_number>(S_Function_Operator<tuple_t<>>::data)..., args...);
			}

			constexpr S_Function_Operator(T_Parts&& ...args)
				: S_Function_Operator<tuple_t<>>(std::forward<T_Parts>(args)...)
			{}

		};


		template<
			size_t ...t_access_number,
			class ...T_request_args,
			class ...T_Operator_Parameters>
		struct S_Function_Operator<
			tuple_t<
				tuple_t<
				tuple_v<t_access_number...>, 
				invalid_t, 
				tuple_t< T_request_args...>>,
			T_Operator_Parameters...>> :
		S_Function_Operator<tuple_t<T_Operator_Parameters...>>
		{
		protected:
			constexpr auto operator()(T_request_args... args)
			{
				return S_Function_Operator<tuple_t<>>::Action_Operator(std::get<t_access_number>(S_Function_Operator<tuple_t<>>::data)..., args...);
			}

			using S_Function_Operator<tuple_t<T_Operator_Parameters...>>::operator();

			constexpr S_Function_Operator(T_Parts&& ...args) 
				: S_Function_Operator<tuple_t<T_Operator_Parameters...>>(std::forward<T_Parts>(args)...)
			{}

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
		protected:

			constexpr auto operator()(T_request_pointer* p,T_request_args... args)
			{
				return S_Function_Operator<tuple_t<>>::Action_Operator(p,std::get<t_access_number>(S_Function_Operator<tuple_t<>>::data)..., args...);
			}

			using S_Function_Operator<tuple_t<T_Operator_Parameters...>>::operator();

			constexpr S_Function_Operator(T_Parts&& ...args)
				: S_Function_Operator<tuple_t<T_Operator_Parameters...>>(std::forward<T_Parts>(args)...)
			{}

		};

	public:

		using type = S_Function_Operator<>;

	};


}

