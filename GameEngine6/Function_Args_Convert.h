#pragma once

#include"Tuple.h"
#include"Expand.h"

namespace N_Function
{

	template<class T_Request_Args, class T_Bind_Args>
	struct I_Function_Args_Convert
	{
	private:
		template<class T_Request_Args = invalid_t>
		struct S_Result
		{
			using chack = T_Request_Args;

			using convert = S_Result;

			template<class T_Fn,class ...T_Args>
			static constexpr auto Convert(T_Fn&& fn,T_Args&&... args)
			{
				return std::forward<T_Fn>(fn)(args...);
			}

			template<class T_Fn,class ...T_Args>
			requires requires
			{
				requires std::is_member_function_pointer_v<std::remove_reference_t<T_Fn>> ;
			}
			static constexpr auto Convert(T_Fn&& fn,auto* p, T_Args... args)
			{
				return (p->*std::forward<T_Fn>(fn))(args...);
			}

		};

		//�d�l
		//�v����������Ǝw�肵�������Ɍ݊��������邩���肷��B
		//
		//�e���v���[�g
		// [T_Request_Args_Tuple]�F�v����������𔽓]����tuple_tp
		// [T_Bind_Args_Tuple]�F�w�肷������𔽓]����tuple_tp
		// [t_constructible_from]�F�v�����Ă���^�ɑ΂��āA[T_Bind_Args...]�^�̕ϐ��ō��邩���肷��B
		// [t_Bind_Args_Expand]�F�w�肷������̌^���W�J�o���邩���肷��
		// [T_Bind_Args...]�F�v�����Ă���^�����^���X�g
		//
		//�⑫
		//[t_Bind_Args_Expand]�̓W�J�ł��邩�́A[N_Tuple::S_Parameter::tuple]�Œ�`����Ă���
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
		struct S_Function_Args_Chack;
		



		//�d�l
		// [T_Bind_Args]��[invalid_t]�݂̂ŁA[T_Bind_Args_Tuple]���Ō�܂Ŕ��肵����ƁA
		//���萬���Ƃ���
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class ...T_Bind_Args>
		using U_Function_Args_Chack_Next =
			S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple,
			std::constructible_from<std::remove_reference_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...> ||
			std::constructible_from<std::remove_pointer_t<typename T_Request_Args_Tuple::type>, typename T_Bind_Args_Tuple::type, T_Bind_Args...> ,
			is_invalid_not<typename N_Tuple::S_Parameter<typename T_Bind_Args_Tuple::type>::tuple>,
			typename T_Bind_Args_Tuple::type, T_Bind_Args...>;



		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand>
			requires (is_invalid<typename T_Bind_Args_Tuple::type>)
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, t_constructible_from, t_Bind_Args_Expand,
			 invalid_t>
		{
			using type = S_Result<
				typename T_Request_Args_Tuple::reverse>;
		};


		//�d�l
		// [T_Bind_Args]���c���Ă����Ԃ�[T_Bind_Args_Tuple]���Ō�܂Ŕ��肵����ƁA
		//���莸�s�Ƃ���
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_constructible_from,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
			requires requires
		{
			requires is_invalid<typename T_Bind_Args_Tuple::type>;
			requires (sizeof...(T_Bind_Args) > 0);
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, t_constructible_from, t_Bind_Args_Expand,
			invalid_t, T_Bind_Args...>
		{
			using type = S_Result<>;

		};


		//�d�l
		//�v����������̌^�ɑ΂��āA[T_Bind_Args...]�̌^�Ő����ł������ꍇ�̓���
		// [T_Bind_Args...]�����p���A[T_Bind_Args_Tuple]�����ɐi�߂�
		//
		//�⑫
		//[U_Function_Args_Chack_Next]���ŁA���p����[T_Bind_Args...]�ɑ΂��āA
		// [T_Bind_Args_Tuple]�����ɐi�߂��ۂ̑I�𒆂̌^��ǉ�����B
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class ...T_Bind_Args>
			requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, false, false,
			T_Bind_Args...>
		{
			using type = U_Function_Args_Chack_Next<T_Request_Args_Tuple,
				typename T_Bind_Args_Tuple::next,
				T_Bind_Args...>::type;
		};

		//�d�l
		//�v����������̌^�ɑ΂��āA[T_Bind_Args...]�̌^�Ő����ł���ꍇ�̓���
		// [T_Bind_Args...]�����Z�b�g���A[T_Request_Args_Tuple][T_Bind_Args_Tuple]�����̔���ɐi�߂�A
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			bool t_Bind_Args_Expand,
			class ...T_Bind_Args>
			requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, true, t_Bind_Args_Expand,
			T_Bind_Args...>
		{

			using next = U_Function_Args_Chack_Next<
				typename T_Request_Args_Tuple::next,
				typename T_Bind_Args_Tuple::next>::type;

			using type = S_Function_Args_Chack;

			using chack = next::chack;

			template<class T_Converted = typename T_Bind_Args_Tuple::tail::reverse>
			struct S_Convert
			{
				using convert = next::convert;
			};

			template<class ...T_Converted>
				requires (sizeof...(T_Bind_Args) > 1)
			struct S_Convert<tuple_t<T_Converted...>>
			{
				using convert = S_Convert;


				//�d�l
				//[T_Request_Type]�^��[args...]������A���̎��̂�Ԃ�
				//
				//�⑫
				//�����Ő��������ϐ��́A�ϐ�[args...]�����ɐ�������邾���ł���A�A�ϐ���[&][*]���t�^����Ă����ꍇ���A
				// ��������N���X���Ōʂɒu�����Ȃ��ꍇ�A���������N���X����A�ϐ�[args...]�ɂ̓A�N�Z�X����Ȃ��B
				template<class ...T_back_args>
				static constexpr auto Convert(T_Converted&&... converted_args, T_Bind_Args&&... args, T_back_args&&... back_args)
				{

					return next::convert::Convert(
						std::forward<T_Converted>(converted_args)...,
						std::remove_reference_t<typename T_Request_Args_Tuple::type>(std::forward<T_Bind_Args>(args)...),
						std::forward<T_back_args>(back_args)...);
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
					requires is_pointer<typename T_Request_Args_Tuple::type>;
				}
				static constexpr auto Convert(T_Converted&&... converted_args, T_Bind_Args&&... args, T_back_args&&... back_args)
				{

					//�|�C���^�[��Ԃ��ׂ̈ꎞ�I�u�W�F�N�g
					std::remove_pointer_t<typename T_Request_Args_Tuple::type> temp(std::forward<T_Bind_Args>(args)...);

					return next::convert::Convert(
						std::forward<T_Converted>(converted_args)...,
						&temp,
						std::forward<T_back_args>(back_args)...);
				}

			};

			using convert = S_Convert<>::convert;


		};

		//�d�l
		//�݊����̂���^�̒�`������Ă���ꍇ�A���̌`�ɕϊ������{����
		// 
		//�⑫
		// �݊����̂���^�̒�`�́A[N_Tuple::S_Parameter]�̓��ꉻ�ɂĒ�`���s��
		template<class T_Request_Args_Tuple,
			class T_Bind_Args_Tuple,
			class T_Front_Bind_Args,
			class ...T_Bind_Args>
			requires requires
		{
			requires is_invalid_not<typename T_Bind_Args_Tuple::type>;
		}
		struct S_Function_Args_Chack<T_Request_Args_Tuple, T_Bind_Args_Tuple, false, true,
			T_Front_Bind_Args, T_Bind_Args...>
		{
			//�d�l
			//�݊����̂���^�ɓW�J����
			// [using tuple}�ɂĒ�`�����^
			using expand = N_Tuple::S_Parameter<T_Front_Bind_Args>::tuple;

			//�d�l
			//�����̈����̌^���X�g����I�𒆂̌^��[expand]�Œ�`���ꂽ�^�ɕύX����
			using insert_bind_args = N_Tuple::U_Insert_tuple_expand<typename T_Bind_Args_Tuple::remove, typename expand::reverse>;
			
			//�d�l
			//���̏������s���N���X
			using next = U_Function_Args_Chack_Next<
				T_Request_Args_Tuple,
				insert_bind_args,
				T_Bind_Args...>::type;

			//�d�l
			//[next]�̏I���ꍇ
			using type = S_Function_Args_Chack;

			//�d�l
			//�����̌݊������m���߂�
			using chack = next::chack;

			//�d�l
			//�������݊����̂���^�ɓW�J����
			template<class T_Converted =typename T_Bind_Args_Tuple::tail::reverse,
				class T_index_sequence = typename N_Tuple::U_index_sequence<expand::size>::reverse>
			struct S_Convert;


			template<class ...T_Converted,class T_index_sequence>
			struct S_Convert<tuple_t<T_Converted...>, T_index_sequence>
			{
				template<size_t t_select_number>
				using select_type = N_Tuple::U_Element_t<t_select_number, expand>;

				//�d�l
				//[change_args]��[t_select_number]�Ԗڂ̕ϐ����擾����
				template<size_t t_select_number>
					static constexpr auto get(T_Front_Bind_Args&& change_args)
				{
					return std::get<t_select_number>(std::forward<T_Front_Bind_Args>(change_args));
				}

				//�d�l
				//[change_args]��[t_select_number]�Ԗڂ̕ϐ����Q�ƂŎ擾����
				template<size_t t_select_number>
					requires is_reference<select_type<t_select_number>>
				static constexpr auto& get(T_Front_Bind_Args&& change_args)
				{
					return std::get<t_select_number>(std::forward<T_Front_Bind_Args>(change_args));
				}

				//�d�l
				//[change_args]��[t_select_number]�Ԗڂ̕ϐ����|�C���^�[�Ŏ擾����
				template<size_t t_select_number>
					requires is_pointer<select_type<t_select_number>>
				static constexpr auto* get(T_Front_Bind_Args&& change_args)
				{
					return &std::get<t_select_number>(std::forward<T_Front_Bind_Args>(change_args));
				}


				//�d�l
				//����[change_args]����납�珇�ԂɓW�J���čs��
				//
				//�e���v���[�g
				//[T_expand_Numbers]�F[change_args]�̓W�J����v�f���̔ԍ�����납����ׂ���
				//  
				//�⑫
				//[change_args]���A5�̗v�f���ɓW�J�����ꍇ�A[T_expand_Numbers = tuple_v<4,3,2,1,0> ]�ƂȂ�
				template<class T_expand_Numbers= T_index_sequence,class ...T_back_args>
				static constexpr auto Convert(T_Converted&&... args, T_Front_Bind_Args&& change_args, T_back_args&&... back_args)
				{
					return Convert<typename T_expand_Numbers::remove>(
						std::forward<T_Converted>(args)...,
						std::forward<T_Front_Bind_Args>(change_args),
						get<T_expand_Numbers::value>(std::forward<T_Front_Bind_Args>(change_args)),
						std::forward<T_back_args>(back_args)...);
				}

				//�d�l
				//����[change_args]�̓W�J���I������ꍇ�A���̍H���ɐi�߂�
				template<same_as<tuple_v<>> T_expand_Numbers = T_index_sequence, class ...T_back_args>
				static constexpr auto Convert(T_Converted&&... args, T_Front_Bind_Args&& change_args, T_back_args&&... back_args)
				{
					return next::convert::Convert(
						std::forward<T_Converted>(args)...,
						std::forward<T_back_args>(back_args)...);
				}

			};

			using convert = S_Convert<>;
		};

		using next = U_Function_Args_Chack_Next<typename T_Request_Args::reverse,
			typename T_Bind_Args::reverse::create_p>::type;

		using chack = next::chack;

	public:

		using type = chack;

		template<class ...T_Args>
		static constexpr auto Convert(T_Args&&... args)
		{
			return next::convert::Convert(std::forward<T_Args>(args)...);
		}


	};


}