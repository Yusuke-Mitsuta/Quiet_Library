#pragma once

#include<utility>
#include"Function_Operator_Helper.h"
#include"Function_Operator_Sort.h"
#include"Function_Args_Convert.h"

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

		template<class T_Request_Args, class T_Args>
		using args_chack = I_Function_Args_Convert<typename T_Request_Args::back, T_Args>::type;

		template<class T_request_args, class ...T_Args>
		static constexpr auto Convert(T_Args... args)
		{
			return I_Function_Args_Convert<T_request_args,
				tuple_t<T_Args...>>::Convert(args...);
		}

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

			//仕様
			//送られて来た変数から、第一引数が関数オブジェクトかつ、[Function]でなければ、
			//	引数を互換性のある型に変換し、[fn]を実行する
			template<class T_Fn, class ...T_Args>
			constexpr auto Action_Operator(T_Fn fn,T_Args ...args)
			{				
				return I_Function_Args_Convert<
					typename Function_Core<T_Fn>::request_args,
				tuple_t<T_Fn, T_Args...>>::Convert(fn,args...);
			};


			//仕様
			//送られて来た変数から、第一引数が関数オブジェクト[Function]であれば、
			//	第二引数以降を新たな引数とし、[fn(args...)]を実行する
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
		private:

			//仕様
			//[data]から関数オブジェクト、バインド済み引数を取得し、
			//[args...]と合わせて、[operator_core::Action_Operator]に変数を送る
			constexpr auto Action_Operator(T_request_args... args)
			{
				return operator_core::Action_Operator(
					std::get<t_fn_access_number>(operator_core::data),
					std::get<t_pointer_access_number>(operator_core::data)...,
					args...,
					std::get<t_args_access_number>(operator_core::data)...);
			}
		protected:

			//仕様
			//[T_request_args...]型を要求する[operator()]
			constexpr auto operator()(T_request_args... args)
			{
				return Action_Operator(args...);
			}

			//仕様
			//[T_request_args...]型と互換性のある型を要求する[operator()]、
			//	引数を[T_request_args...]型に変換する
			template<class ...T_Args>
				requires is_invalid_not<args_chack<tuple_t<T_request_args...>, tuple_t<T_Args...>>>
			constexpr auto operator()(T_Args... args)
			{
				return Convert<tuple_t<T_request_args...>>(&S_Function_Operator::Action_Operator, this, args...);
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
		private:
			constexpr auto Action_Operator(T_request_pointer* p, T_request_args... args)
			{
				return operator_core::Action_Operator(
					std::get<t_fn_access_number>(operator_core::data),
					p,
					args...,
					std::get<t_args_access_number>(operator_core::data)...);
			}

		protected:
		public:

			constexpr auto operator()(T_request_pointer* p,T_request_args... args)
			{
				return Action_Operator(p, args...);
			}

			template<class ...T_Args>
				requires is_invalid_not<args_chack<tuple_t<T_request_args...>, tuple_t<T_Args...>>>
			constexpr auto operator()(T_request_pointer* p, T_Args... args)
			{
				return Convert<tuple_t<T_request_args...>>(&S_Function_Operator::Action_Operator, this, p, args...);
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
		private:
			constexpr auto Action_Operator(T_request_args... args)
			{
				return operator_core::Action_Operator(
					std::get<t_fn_access_number>(operator_core::data),
					std::get<t_pointer_access_number>(operator_core::data)...,
					args...,
					std::get<t_args_access_number>(operator_core::data)...);
			}
		protected:

			constexpr auto operator()(T_request_args... args)
			{
				return Action_Operator(args...);
			}

			template<class ...T_Args>
				requires requires
			{
				requires is_invalid_not<args_chack<tuple_t<T_request_args...>, tuple_t<T_Args...>>>;
			}
			constexpr auto operator()(T_Args... args)
			{
				return Convert<tuple_t<T_request_args...>>(&S_Function_Operator::Action_Operator, this, args...);
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
		private:
			constexpr auto Action_Operator(T_request_pointer* p, T_request_args... args)
			{
				return operator_core::Action_Operator(
					std::get<t_fn_access_number>(operator_core::data),
					p,
					args...,
					std::get<t_args_access_number>(operator_core::data)...);
			}

		protected:

			constexpr auto operator()(T_request_pointer* p, T_request_args... args)
			{
				return Action_Operator(p, args...);
			}

			template<class ...T_Args>
				requires requires
			{
				requires is_invalid_not<args_chack<tuple_t<T_request_args...>, tuple_t<T_Args...>>>;
			}
			constexpr auto operator()(T_request_pointer* p, T_Args... args)
			{
				return Convert<tuple_t<T_request_args...>>(&S_Function_Operator::Action_Operator, this, p, args...);
			}

			using S_Function_Operator<typename T_Operator_Parameter::remove>::operator();

			constexpr S_Function_Operator(T_Parts&& ...args)
				: S_Function_Operator<typename T_Operator_Parameter::remove>(std::forward<T_Parts>(args)...) {}
		};
		
	public:

		using type = S_Function_Operator<>;

	};



}



