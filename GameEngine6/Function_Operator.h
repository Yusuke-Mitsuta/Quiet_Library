#pragma once

#include<utility>

#include"Tuple.h"
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


		using function_operator_data_list = typename I_Function_Operator_Helper<T_Parts...>::type;
		using function_operator_sort = typename I_Function_Operator_Sort<function_operator_data_list>::type;


		//�d�l
		//�|�C���^�[��v������ꍇ�A�v����������̐擪�ɕt��������B
		template<class T_Operator_data,
			class T_Request_Args= N_Tuple::U_Element_t<1, T_Operator_data>,
			class T_Request_Pointer= N_Tuple::U_Element_t<2, T_Operator_data>>
		struct S_Merge_Pointer
		{
			using type = T_Request_Args;
		};

		template<class T_Operator_data, class ...T_Request_Args,class T_Request_Pointer>
		requires requires
		{
			requires is_invalid_not<T_Request_Pointer>;
		}
		struct S_Merge_Pointer<T_Operator_data,tuple_t<T_Request_Args...>,T_Request_Pointer>
		{
			using type = tuple_t<T_Request_Pointer*, T_Request_Args...>;
		};


		//�d�l
		//[operator_data_list]����A[T_Args]�ƌ݊����̂��������v������f�[�^���擾����
		template<class T_Args, class T_Operator_Parameter = function_operator_data_list>
		struct I_Function_Operator_Search
		{
			using merge_pointer =S_Merge_Pointer<typename T_Operator_Parameter::type>::type::back;

			using args_chack = I_Function_Args_Convert<merge_pointer, T_Args>::type;
			
			template<bool t_detect_fg= (N_Tuple::S_Size<args_chack>::tail_size == merge_pointer::size)>
			struct S_Next_Search
			{
				using type = I_Function_Operator_Search<T_Args,typename T_Operator_Parameter::remove>::type;
			};
			
			template<>
			struct S_Next_Search<true>
			{
				using type = T_Operator_Parameter::type;
			};

			using type = S_Next_Search<>::type;
		};


		template<class T_Args,class T_Operator_Parameter>
			requires requires
		{
			requires is_invalid<typename T_Operator_Parameter::type>;
		}
		struct I_Function_Operator_Search<T_Args,T_Operator_Parameter>
		{
			using type = invalid_t;
		};
		

		template<class T_request_args, class ...T_Args>
		static constexpr auto Convert(T_Args... args)
		{
			return I_Function_Args_Convert<T_request_args,
				tuple_t<T_Args...>>::Convert(args...);
		}


		template<class T_Operator_Parameter = function_operator_sort,
		class T_Access_Number = N_Tuple::U_Element_t<0,typename T_Operator_Parameter::type>,
		class T_Request_Args = N_Tuple::U_Element_t<1,typename T_Operator_Parameter::type>,
		class T_Request_Pointer = N_Tuple::U_Element_t<2,typename T_Operator_Parameter::type>>
		struct S_Function_Operator
		{
		public:
			tuple_t<T_Parts...> data;

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

			//�d�l
			//�o�C���h�ς݂̊֐��I�u�W�F�N�g�S�Ă̒�����A
			// [T_Args...]�ƌ݊����̂��������L����֐��I�u�W�F�N�g���Ăяo���B
			template<class ...T_Args>
				requires is_invalid_not<typename I_Function_Operator_Search<tuple_t<T_Args...>, function_operator_data_list>::type>
			constexpr auto operator()(T_Args... args)
			{
				using hit_operator_data = I_Function_Operator_Search<tuple_t<T_Args...>>::type;

				return S_Function_Operator<tuple_t<hit_operator_data>>::Action_Operator(this, args...);
			}

			using type = S_Function_Operator;

		};

		using operator_core = S_Function_Operator<tuple_t<>>;
		
		template<
			class T_Operator_Parameter,
			size_t ...t_pointer_access_number,
			size_t t_fn_access_number,
			size_t ...t_args_access_number,
			class ...T_request_args,
			class T_request_pointer>
		struct S_Function_Operator<
			T_Operator_Parameter,
			tuple_vp<tuple_v<t_pointer_access_number...>, t_fn_access_number, tuple_v<t_args_access_number...>>,
			tuple_t<T_request_args...>,
			T_request_pointer>
		{
			//�d�l
			//[data_storage_p]�f�[�^�̕ۊǏꏊ�̃|�C���^�[����A
			// �o�C���h�ς݂̊֐��I�u�W�F�N�g�A�|�C���^�[�A�������擾���A�K�؂Ƀ}�[�W���s���B
			static constexpr auto Action_Operator(operator_core* data_storage_p,auto ...args)
			{
				return data_storage_p->Action_Operator(
					std::get<t_fn_access_number>(data_storage_p->data),
					std::get<t_pointer_access_number>(data_storage_p->data)...,
					args...,
					std::get<t_args_access_number>(data_storage_p->data)...);
			}

			using next = S_Function_Operator<typename T_Operator_Parameter::remove>::type;

			template<class T_request_pointer= T_request_pointer>
			struct S_Function_Operator_Create :
				next
			{
				//�d�l
				//[T_request_pointer*]�|�C���^�[�A[T_request_args...]��v������֐��I�u�W�F�N�g�Ɉ�����]������
				constexpr auto operator()(T_request_pointer* p, T_request_args... args)
				{
					return S_Function_Operator<T_Operator_Parameter>::Action_Operator(this,args...);
				}

				using next::operator();

				constexpr S_Function_Operator_Create(T_Parts&& ...args) :
					next(std::forward<T_Parts>(args)...) {}

			};

			template<>
			struct S_Function_Operator_Create<invalid_t> :
				next
			{	
				//�d�l
				//[T_request_args...]��v������֐��I�u�W�F�N�g�Ɉ�����]������
				constexpr auto operator()(T_request_args... args)
				{
					return S_Function_Operator<T_Operator_Parameter>::Action_Operator(this,args...);
				}

				using next::operator();

				constexpr S_Function_Operator_Create(T_Parts&& ...args) :
					next(std::forward<T_Parts>(args)...) {}
			};

			using type = S_Function_Operator_Create<>;

		};
		
	public:

		using type = S_Function_Operator<>::type;

	};



}



