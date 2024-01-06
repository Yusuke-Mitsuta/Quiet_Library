#pragma once

#include<utility>
#include"Function_Operator_Helper.h"
#include"Function_Operator_Sort.h"
#include"Function_Args_Convert.h"

namespace N_Function
{

	//�d�l
	//[T_Parts...]����S�ʂ��operator()�����N���X�����
	//
	//�e���v���[�g
	//[T_Parts...]::[Funcsion]�̈����̌^
	// 
	//using
	//[type]�ł��̃N���X�ɃA�N�Z�X����
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

			//�d�l
			//�����ė����ϐ�����A���������֐��I�u�W�F�N�g���A[Function]�łȂ���΁A
			//	�������݊����̂���^�ɕϊ����A[fn]�����s����
			template<class T_Fn, class ...T_Args>
			constexpr auto Action_Operator(T_Fn fn,T_Args ...args)
			{				
				return I_Function_Args_Convert<
					typename Function_Core<T_Fn>::request_args,
				tuple_t<T_Fn, T_Args...>>::Convert(fn,args...);
			};


			//�d�l
			//�����ė����ϐ�����A���������֐��I�u�W�F�N�g[Function]�ł���΁A
			//	�������ȍ~��V���Ȉ����Ƃ��A[fn(args...)]�����s����
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

			//�d�l
			//[data]����֐��I�u�W�F�N�g�A�o�C���h�ς݈������擾���A
			//[args...]�ƍ��킹�āA[operator_core::Action_Operator]�ɕϐ��𑗂�
			constexpr auto Action_Operator(T_request_args... args)
			{
				return operator_core::Action_Operator(
					std::get<t_fn_access_number>(operator_core::data),
					std::get<t_pointer_access_number>(operator_core::data)...,
					args...,
					std::get<t_args_access_number>(operator_core::data)...);
			}
		protected:

			//�d�l
			//[T_request_args...]�^��v������[operator()]
			constexpr auto operator()(T_request_args... args)
			{
				return Action_Operator(args...);
			}

			//�d�l
			//[T_request_args...]�^�ƌ݊����̂���^��v������[operator()]�A
			//	������[T_request_args...]�^�ɕϊ�����
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



