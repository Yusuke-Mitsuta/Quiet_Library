#pragma once

#include<utility>

#include"Tuple.h"
#include"Function_Operator_Helper.h"
#include"Function_Operator_Sort.h"
#include"Function_Operator_Search.h"

template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function;

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

		template<class ...T_Args>
		using function_operator_search = I_Function_Operator_Search<Function<T_Parts...>, tuple_t<T_Args...>>::type;


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
			constexpr auto Action_Operator(T_Fn&& fn,T_Args&& ...args)
			{	
				return N_Tuple::Apply(std::forward<T_Fn>(fn), std::forward<T_Args>(args)...);
			};


			//�d�l
			//�����ė����ϐ�����A���������֐��I�u�W�F�N�g[Function]�ł���΁A
			//	�������ȍ~��V���Ȉ����Ƃ��A[fn(args...)]�����s����
			template<class T_Fn,class ...T_Args>
				requires requires
			{
				requires same_as_template_type<std::remove_pointer_t<T_Fn>, Function>;
			}
			constexpr auto Action_Operator(T_Fn&& fn, T_Args&& ...args)
			{
				return fn->Relay_Forward(std::forward<T_Args>(args)...);
			};


			constexpr S_Function_Operator(T_Parts&& ...args)
				:data(std::forward<T_Parts>(args)...)
			{
			
			}

			template<class ...T_Args>
				requires is_invalid_not< function_operator_search<T_Args...>>
			constexpr auto Relay_Forward(T_Args&&... args)
			{
				return S_Function_Operator<tuple_t<function_operator_search<T_Args...>>>::Action_Operator(this,
					std::forward<T_Args>(args)...);
					

			}

			//�d�l
			//�o�C���h�ς݂̊֐��I�u�W�F�N�g�S�Ă̒�����A
			// [T_Args...]�ƌ݊����̂��������L����֐��I�u�W�F�N�g���Ăяo���B
			template<class ...T_Args>				
				requires is_invalid_not<function_operator_search<T_Args...>>
			constexpr auto operator()(T_Args... args)
			{
				return this->Relay_Forward(std::forward<T_Args>(args)...);
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
			template<class ...T_Args>
			static constexpr auto Action_Operator(operator_core* data_storage_p,T_Args&&... args)
			{
				return data_storage_p->Action_Operator(
					std::get<t_fn_access_number>(data_storage_p->data),
					std::get<t_pointer_access_number>(data_storage_p->data)...,
					std::forward<T_Args>(args)...,
					std::get<t_args_access_number>(data_storage_p->data)...);
			}



			using next = S_Function_Operator<typename T_Operator_Parameter::remove>::type;

			template<class T_request_pointer= T_request_pointer>
			struct S_Function_Operator_Create :
				next
			{
				template<class T_pointer,class ...T_Args>
					requires (convertible_to<T_Args, T_request_args> &&... &&
							  convertible_to< T_pointer ,T_request_pointer*>)
				constexpr auto Relay_Forward(T_pointer&& p, T_Args&&... args)
				{
					return S_Function_Operator<T_Operator_Parameter>::Action_Operator(this,
						std::forward<T_pointer>(p),
						std::forward<T_Args>(args)...);
				}

				//�d�l
				//[T_request_pointer*]�|�C���^�[�A[T_request_args...]��v������֐��I�u�W�F�N�g�Ɉ�����]������
				constexpr auto operator()(T_request_pointer* p, T_request_args... args)
				{
					return Relay_Forward(p, args...);
				}


				using next::operator();

				constexpr S_Function_Operator_Create(T_Parts&& ...args) :
					next(std::forward<T_Parts>(args)...) {}

			};

			template<>
			struct S_Function_Operator_Create<invalid_t> :
				next
			{	
				template<class ...T_Args>
					requires (convertible_to<T_Args,T_request_args> &&...)
				constexpr auto Relay_Forward(T_Args&&... args)
				{

					return S_Function_Operator<T_Operator_Parameter>::Action_Operator(this,
						std::forward<T_Args>(args)...);
				}

				//�d�l
				//[T_request_args...]��v������֐��I�u�W�F�N�g�Ɉ�����]������
				constexpr auto operator()(T_request_args... args)
				{
					return Relay_Forward(args...);
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



