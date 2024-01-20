#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"

#include"main.h"

namespace N_Tuple
{



	//�d�l
	//�ϐ��ɑ΂��āA��Α��A���Έ�A���Α��̕ϊ����s���A
	// �֐��I�u�W�F�N�g�A�N���X�R���X�g���N�^�����s����
	//
	//�e���v���[�g
	// [T_Fn_Action]�F�ϐ������Ď��s����A[�֐��|�C���^�[�AFunction�A�N���X]�̌^
	//[T_Set_Types...]�F��Α��A���Έ�A���Α��̕ϊ��𔺂��ϐ�
	// 
	//�⑫
	//���s��[::Apply(args...)]���Ăяo����
	//��Α��̕ϊ��̓R���X�g���N�^���Ăяo���鎖�A
	//���Έ�̕ϊ��͓W�J����ϐ��̃N���X��
	// [using tuple=tuple_t< ... >]�A[auto& get<N>()]�L�q����Ă��鎖�B
	//
	// ��Α��̕ϊ����A�ϊ����[&],[*]�͎����ŕ⊮����邪�A
	// �ϊ���̕ϐ��ƕϊ��ɗp�����ϐ��̊֌W�͌ʂɒ�`����Ȃ�����R�s�[�ł���B
	template<class T_Fn,class ...T_Set_Types>
	struct I_Apply_Action
	{
	//private:

		using S_Request= N_Apply::I_Request<T_Fn, T_Set_Types...>;

		template<N_Apply::E_Type t_type>
		static constexpr bool is_apply_type= N_Apply::is_apply_type<T_Fn, t_type>;

		//�d�l
		//�^�̔��肪�I������ۂɌĂяo�����
		template<class T_Request_Types = invalid_t,class ...Ts>
		struct S_Result
		{
			using chack = T_Request_Types;

			using convert = S_Result;

			template<class ...T_Args>
			static constexpr auto Apply(auto* fn, T_Args&&... args)
			{
				return fn->operator()(std::forward<T_Args>(args)...);
			}

		};

		//�d�l
		//�v����������Ǝw�肵�������Ɍ݊��������邩���肷��B
		//
		//�e���v���[�g
		// [T_Request_Types_Tuple]�F�v����������𔽓]����tuple_tp
		// [T_Set_Types_Tuple]�F�w�肷������𔽓]����tuple_tp
		// [t_constructible_from]�F�v�����Ă���^�ɑ΂��āA[T_Set_Types...]�^�̕ϐ��ō��邩���肷��B
		// [T_Set_Types_Expand]�F�w�肷������̌^���W�J�o���邩���肷��
		// [T_Set_Types...]�F�v�����Ă���^�����^���X�g
		//
		//�⑫
		//[T_Set_Types_Expand]�̓W�J�ł��邩�́A[N_Tuple::S_Parameter::tuple]�Œ�`����Ă���
		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			bool t_constructible_from,
			bool T_Set_Types_Expand,
			class ...T_Set_Types>
		struct S_Apply_Args_Chack
		{
			using type = S_Result<>;
		};

		//�d�l
		// [T_Set_Types]��[invalid_t]�݂̂ŁA[T_Set_Types_Tuple]���Ō�܂Ŕ��肵����ƁA
		//���萬���Ƃ���
		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class ...T_Set_Types>
		using U_Function_Args_Chack_Next =
			S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple,
			std::constructible_from<std::remove_reference_t<typename T_Request_Types_Tuple::type>, typename T_Set_Types_Tuple::type, T_Set_Types...> ||
			std::constructible_from<std::remove_pointer_t<typename T_Request_Types_Tuple::type>, typename T_Set_Types_Tuple::type, T_Set_Types...>,
			is_invalid_not<typename N_Tuple::S_Parameter<typename T_Set_Types_Tuple::type>::tuple>,
			typename T_Set_Types_Tuple::type, T_Set_Types...>;



		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			bool t_constructible_from,
			bool T_Set_Types_Expand>
			requires (is_invalid<typename T_Set_Types_Tuple::type>)
		struct S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, t_constructible_from, T_Set_Types_Expand,
			invalid_t>
		{
			using type = S_Result<typename T_Request_Types_Tuple::reverse>;
		};


		//�d�l
		//�v����������̌^�ɑ΂��āA[T_Set_Types...]�̌^�Ő����ł������ꍇ�̓���
		// [T_Set_Types...]�����p���A[T_Set_Types_Tuple]�����ɐi�߂�
		//
		//�⑫
		//[U_Function_Args_Chack_Next]���ŁA���p����[T_Set_Types...]�ɑ΂��āA
		// [T_Set_Types_Tuple]�����ɐi�߂��ۂ̑I�𒆂̌^��ǉ�����B
		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class ...T_Set_Types>
			requires requires
		{
			requires is_invalid_not<typename T_Set_Types_Tuple::type>;
		}
		struct S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, false,
			T_Set_Types...>
		{
			using type = U_Function_Args_Chack_Next<T_Request_Types_Tuple,
				typename T_Set_Types_Tuple::next,
				T_Set_Types...>::type;
		};

		//�d�l
		//�v����������̌^�ɑ΂��āA[T_Set_Types...]�̌^�Ő����ł���ꍇ�̓���
		// [T_Set_Types...]�����Z�b�g���A[T_Request_Types_Tuple][T_Set_Types_Tuple]�����̔���ɐi�߂�A
		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			bool T_Set_Types_Expand,
			class ...T_Set_Types>
			requires requires
		{
			requires is_invalid_not<typename T_Set_Types_Tuple::type>;
			
		}
		struct S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, true, T_Set_Types_Expand,
			T_Set_Types...>
		{

			//�d�l
			//���ȍ~�̕ϐ���[T_Set_Types...]�ǉ����Ă�[T_Request_Types_Tuple::type]�������o���邩���肷��
			// ���̌��ʂ�
			//�@�@�L���l�ł���΁A���ȍ~�̕ϐ���ǉ�����B
			//�@�@�����l�ł���΁A[T_Set_Types...]�̕ϐ���[T_Request_Types_Tuple::type]�𐶐�����
			//
			//�⑫
			//���ȍ~�̈����������A�G���[�ɂȂ�ꍇ�A�Ō�̈������擾�����Ɣ��肷��B
			template<class T = typename S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, T_Set_Types_Expand,
				T_Set_Types...>::type::chack>
			struct S_last_args_chack
			{
				using type = typename S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, T_Set_Types_Expand,
					T_Set_Types...>::type;
			};

			template<>
			struct S_last_args_chack<invalid_t>
			{
				using type = S_Apply_Args_Chack;
			};

			using type = S_last_args_chack<>::type;

			using next = U_Function_Args_Chack_Next<
				typename T_Request_Types_Tuple::next,
				typename T_Set_Types_Tuple::next>::type;

			using chack = next::chack;


			template<class T_Converted = typename T_Set_Types_Tuple::tail::reverse>
			struct S_Convert
			{
				using convert = next::convert;

			};

			template<class ...T_Converted>
				requires (sizeof...(T_Set_Types) > 1) &&
				((!is_apply_type<N_Apply::E_Type::CLASS>) ||
				(is_apply_type<N_Apply::E_Type::CLASS> &&
				is_invalid_not <typename S_Parameter<T_Fn>::tuple >))
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
				static constexpr auto Apply(auto* fn, T_Converted&&... converted_args, T_Set_Types&&... args, T_back_args&&... back_args)
				{
					return next::convert::Apply(
						fn,
						std::forward<T_Converted>(converted_args)...,
						std::remove_reference_t<typename T_Request_Types_Tuple::type>(std::forward<T_Set_Types>(args)...),
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
					requires is_pointer<typename T_Request_Types_Tuple::type>;
				}
				static constexpr auto Apply(auto* fn, T_Converted&&... converted_args, T_Set_Types&&... args, T_back_args&&... back_args)
				{

					//�|�C���^�[��Ԃ��ׂ̈ꎞ�I�u�W�F�N�g
					std::remove_pointer_t<typename T_Request_Types_Tuple::type> temp(std::forward<T_Set_Types>(args)...);

					return next::convert::Apply(
						fn,
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
		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class T_FronT_Set_Types,
			class ...T_Set_Types>
			requires requires
		{
			requires is_invalid_not<typename T_Set_Types_Tuple::type>;
		}
		struct S_Apply_Args_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, false, true,
			T_FronT_Set_Types, T_Set_Types...>
		{
			//�d�l
			//�݊����̂���^�ɓW�J����
			// [using tuple}�ɂĒ�`�����^
			using expand = N_Tuple::S_Parameter<T_FronT_Set_Types>::tuple;

			//�d�l
			//�����̈����̌^���X�g����I�𒆂̌^��[expand]�Œ�`���ꂽ�^�ɕύX����
			using inserT_Set_Types = N_Tuple::U_Insert_tuple_expand<typename T_Set_Types_Tuple::remove, typename expand::reverse>;

			//�d�l
			//���̏������s���N���X
			using next = U_Function_Args_Chack_Next<
				T_Request_Types_Tuple,
				inserT_Set_Types,
				T_Set_Types...>::type;

			//�d�l
			//[next]�̏I���ꍇ
			using type = S_Apply_Args_Chack;

			//�d�l
			//�����̌݊������m���߂�
			using chack = next::chack;

			//�d�l
			//�������݊����̂���^�ɓW�J����
			template<class T_Converted = typename T_Set_Types_Tuple::tail::reverse,
				class T_index_sequence = typename N_Tuple::U_index_sequence<expand::size>::reverse>
			struct S_Convert;


			template<class ...T_Converted, class T_index_sequence>
			struct S_Convert<tuple_t<T_Converted...>, T_index_sequence>
			{
				template<size_t t_select_number>
				using select_type = N_Tuple::U_Element_t<t_select_number, expand>;

				//�d�l
				//[change_args]��[t_select_number]�Ԗڂ̕ϐ����擾����
				template<size_t t_select_number>
				static constexpr auto get(T_FronT_Set_Types&& change_args)
				{
					return std::get<t_select_number>(std::forward<T_FronT_Set_Types>(change_args));
				}

				//�d�l
				//[change_args]��[t_select_number]�Ԗڂ̕ϐ����Q�ƂŎ擾����
				template<size_t t_select_number>
					requires is_reference<select_type<t_select_number>>
				static constexpr auto& get(T_FronT_Set_Types change_args)
				{
					return std::get<t_select_number>(std::forward<T_FronT_Set_Types>(change_args));
				}

				//�d�l
				//[change_args]��[t_select_number]�Ԗڂ̕ϐ����|�C���^�[�Ŏ擾����
				template<size_t t_select_number>
					requires is_pointer<select_type<t_select_number>>
				static constexpr auto* get(T_FronT_Set_Types&& change_args)
				{
					return &std::get<t_select_number>(std::forward<T_FronT_Set_Types>(change_args));
				}

				//�d�l
				//����[change_args]����납�珇�ԂɓW�J���čs��
				//
				//�e���v���[�g
				//[T_expand_Numbers]�F[change_args]�̓W�J����v�f���̔ԍ�����납����ׂ���
				//  
				//�⑫
				//[change_args]���A5�̗v�f���ɓW�J�����ꍇ�A[T_expand_Numbers = tuple_v<4,3,2,1,0> ]�ƂȂ�
				template<class T_expand_Numbers = T_index_sequence, class ...T_back_args>
				static constexpr auto Apply(auto* fn,T_Converted&&... args, T_FronT_Set_Types&& change_args, T_back_args&&... back_args)
				{
					return Apply<typename T_expand_Numbers::remove>(
						fn,
						std::forward<T_Converted>(args)...,
						std::forward<T_FronT_Set_Types>(change_args),
						get<T_expand_Numbers::value>(std::forward<T_FronT_Set_Types>(change_args)),
						std::forward<T_back_args>(back_args)...);
				}

				//�d�l
				//����[change_args]�̓W�J���I������ꍇ�A���̍H���ɐi�߂�
				template<same_as<tuple_v<>> T_expand_Numbers = T_index_sequence, class ...T_back_args>
				static constexpr auto Apply(auto* fn,T_Converted&&... args, T_FronT_Set_Types&& change_args, T_back_args&&... back_args)
				{
					return next::convert::Apply(
						fn,
						std::forward<T_Converted>(args)...,
						std::forward<T_back_args>(back_args)...);
				}

			};

			using convert = S_Convert<>;
		};


		using next = U_Function_Args_Chack_Next<
			typename S_Request::args::reverse,
			typename tuple_t<T_Set_Types...>::reverse::create_p>::type;

		using chack = next::chack;

	public:

		using type = chack;

		//�d�l
		//�^[fn]�ɑ΂��āA�v�������[args...] ����Α��A���Έ�̕ϊ����s���A
		// [fn]�̃R���X�g���N�^�����s����(��������)�B
		template<class T_Create_class = T_Fn, class ...T_Args>
			requires (N_Apply::is_apply_type<T_Create_class, N_Apply::E_Type::CLASS> ||
					  N_Apply::is_apply_type<T_Create_class, N_Apply::E_Type::CLASS_NEW>)
		static constexpr auto Apply(T_Args&&... args)
		{
			N_Apply::S_Class_Create<T_Create_class> fn_action = {};
			return next::convert::Apply(&fn_action, std::forward<T_Args>(args)...);
		}

		//�d�l
		//�z��^�̃|�C���^�[[array_p]��[T_Fn]��0�����ڂ̗v�f����ǉ�����B
		template<class T_Array, class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::ARRAY>
		static constexpr auto Apply(T_Array* array_p, T_Args&&... args)
		{
			N_Apply::S_Array_Create fn_action = { array_p };
			return next::convert::Apply(&fn_action, std::forward<T_Args>(args)...);
		}

		//�d�l
		//�֐�[fn]�ɑ΂��āA�v�������[args...] ����Α��A���Έ�̕ϊ����s���A
		// [fn]�����s����
		template<class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>
		static constexpr auto Apply(T_Fn&& fn,T_Args&&... args)
		{
			N_Apply::S_Fn_Action fn_action(fn, &invalid);
			return next::convert::Apply(&fn_action,std::forward<T_Args>(args)...);
		
		}

		//�d�l
		//�֐�[fn]�ɑ΂��āA�v�������[args...] ����Α��A���Έ�̕ϊ����s���A
		// �|�C���^�[��p����[fn]�����s����
		template<class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>
		static constexpr auto Apply(T_Fn&& fn,S_Request::pointer* p,T_Args&&... args)
		{
			N_Apply::S_Fn_Action fn_action(fn, p);
			return next::convert::Apply(&fn_action,std::forward<T_Args>(args)...);
		}
	};

}