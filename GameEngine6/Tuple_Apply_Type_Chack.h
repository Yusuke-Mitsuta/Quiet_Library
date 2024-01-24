#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"


namespace N_Tuple::N_Apply
{


	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Apply_Type_Chack
	{

		//�d�l
		//�^�̔��肪�I������ۂɌĂяo�����
		template<class T_Request_Types_Tuple = invalid_t,
			class T_Set_Types_Tuple = invalid_t,
			class T_Set_Types_Convert = invalid_t>
		struct S_Result
		{
			using chack = T_Request_Types_Tuple;

			using convert = S_Result;

			template<class ...T_Args>
			static constexpr auto Apply(auto* fn, T_Args&&... args)
			{
				return fn->operator()(std::forward<T_Args>(args)...);
			}

		};



		template<class T_Request_Types_Tuple=,
			class T_Set_Types_Tuple,
			class T_Set_Types_Convert=tuple_t<>>
		struct S_Apply_Type_Chack
		{
			using request_t = T_Request_Types_Tuple::type;

			using set_t = T_Set_Types_Tuple::type;

			//�d�l
			//�݊����̂���^�ɓW�J����
			// [using tuple}�ɂĒ�`�����^
			template<class T_Tuple>
			using expand = N_Tuple::S_Parameter<T_Tuple>::tuple;


			template<bool t_constructible_from= (convertible_to<set_t,request_t>==T_Set_Types_Convert::size),
				bool t_Request_Types_Expand = is_invalid_not<expand<request_t>>,
				bool t_Set_Types_Expand= is_invalid_not<expand<set_t>> >
			struct S_Apply_Control
			{
				using type = S_Result<T_Request_Types_Tuple, T_Set_Types_Tuple, T_Set_Types_Convert>;
			};


			template<bool t_Request_Types_Expand, bool t_Set_Types_Expand>
			struct S_Apply_Control<true,t_Request_Types_Expand,t_Set_Types_Expand>
			{
				using type = S_Apply_Type_Chack<
					typename T_Request_Types_Tuple::next,
					typename T_Set_Types_Tuple::next>::type;
			};


			template<>
			struct S_Apply_Control<false, true, false>
			{
				
				using set_types_tuple =U_Merge_tuple_expand<
					typename T_Set_Types_Convert::reverse,
					typename T_Set_Types_Tuple::tail>;


				using request_type_convert =
					S_Apply_Type_Chack<
					typename expand<request_t>::reverse,
					set_types_tuple>::type;

				using type = S_Apply_Control;

				using next = S_Apply_Type_Chack<
					typename T_Request_Types_Tuple::next,
					typename request_type_convert::set_types_tuple,
					typename request_type_convert::set_types_convert>::type;




				template<class T_Unconverted = typename T_Set_Types_Tuple::tail::reverse,
					class T_Converting= T_Set_Types_Convert,
					class T_Convert = typename  T_Request_Types_Tuple::head::reverse>
				struct S_Convert
				{
					using convert = next::convert;

				};

				template<class ...T_Unconverted,class ...T_Converting,class ...T_Convert>
				struct S_Convert<tuple_t<T_Unconverted...>,tuple_t<T_Converting...>, tuple_t<T_Convert...>>
				{
					using convert = S_Convert;

					static constexpr auto Apply(auto* fn,
						T_Unconverted&&... unconverted_args, 
						T_Converting&&... converting_args,
						T_Convert&&... convert_args)
					{




					}

					//�d�l
					//[T_Request_Type]�^��[args...]������A���̎��̂�Ԃ�
					//
					//�⑫
					//�����Ő��������ϐ��́A�ϐ�[args...]�����ɐ�������邾���ł���A�A�ϐ���[&][*]���t�^����Ă����ꍇ���A
					// ��������N���X���Ōʂɒu�����Ȃ��ꍇ�A���������N���X����A�ϐ�[args...]�ɂ̓A�N�Z�X����Ȃ��B
					static constexpr auto Apply(auto* fn, T_Unconverted&&... converted_args, T_Convert&&... args)
					{
						
						request_type_convert::type::apply::Apply
						(
							
						)


						return next::convert::Apply(
							fn,
							std::forward<T_Unconverted>(converted_args)...,
							I_Apply_Action<std::remove_reference_t<T_Request_Type>, T_Convert...>::Apply(std::forward<T_Convert>(args)...),
					}


					//�d�l
					//[T_Request_Type]�^��[args...]������A���̃|�C���^�[��Ԃ�
					//
					//�⑫
					//�����Ő��������ϐ��́A�ϐ�[args...]�����ɐ�������邾���ł���A�ϐ���[&][*]���t�^����Ă����ꍇ���A
					// ��������N���X���Ōʂɒu�����Ȃ��ꍇ�A���������N���X����A�ϐ�[args...]�ɂ̓A�N�Z�X����Ȃ��B
					// 
					//[T_Request_Type]�^��[args...]������A���̃|�C���^�[��Ԃ�
					template<class ...T_back_args>
						requires requires
					{
						requires is_pointer<T_Request_Type>;
					}
					static constexpr auto Apply(auto* fn, T_Unconverted&&... converted_args, T_Set_Types&&... args, T_back_args&&... back_args)
					{

						//�|�C���^�[��Ԃ��ׂ̈ꎞ�I�u�W�F�N�g
						std::remove_pointer_t<T_Request_Type> temp =
							I_Apply_Action<std::remove_pointer_t<T_Request_Type>, T_Set_Types...>
							::Apply(std::forward<T_Set_Types>(args)...);

						return next::convert::Apply(
							fn,
							std::forward<T_Converted>(converted_args)...,
							&temp,
							std::forward<T_back_args>(back_args)...);

					}

				};



			};

			template<>
			struct S_Apply_Control<false, false, true>
			{
				//�d�l
				//�����̈����̌^���X�g����I�𒆂̌^��[expand]�Œ�`���ꂽ�^�ɕύX����
				using set_type_expand = N_Tuple::U_Insert_tuple_expand<
					typename T_Set_Types_Tuple::remove,
					typename expand<typename T_Set_Types_Tuple::type>::reverse>;

				using type = S_Apply_Control;

				using next = S_Apply_Type_Chack<
					T_Request_Types_Tuple,
					set_type_expand,
					T_Set_Types_Convert>::type;

			};

			using type = S_Apply_Control<>::type;

		};


		using type = S_Apply_Type_Chack<
			typename T_Request_Types_Tuple::reverse,
			typename T_Set_Types_Tuple::reverse::create_p>::type;

	};


}
