#pragma once

#include"Tuple.h"
#include"Function_Superficial_Data.h"

namespace N_Function
{

	//�d�l
	//[T_Parts...]����S�ʂ��operator()���쐬����ׂɃf�[�^�𐮗�����B
	//
	//�e���v���[�g
	//[T_Parts...]::[Funcsion]�̈����̌^
	//
	//using 
	//[::type] �A���Ă���f�[�^�͊֐��P�P�ɑ΂���
	//	��������v�������ɌĂяo��[Funcsion]�̈����̔ԍ�
	//	�v������|�C���^�[�̌^
	//�@�v����������̌^
	//��[tuple_t]�œZ�߁A�P�P�̌��ʂ�[tuple_t]�œZ�߂�
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
		struct S_Function_Operator_Helper_Core;


		//�d�l
		// [S_Function_Operator_Helper]�œZ�߂�ꂽ�A�P�ʂ��operator()���Ăяo���f�[�^�ƁA
		//���ȍ~�̃f�[�^�ɃA�N�Z�X����
		template<
			size_t ...t_access_number,
			class T_request_pointer,
			class T_request_args,
			size_t ...t_request_args_number,
			class T_Next>
		struct S_Function_Operator_Helper_Core<tuple_v<t_access_number...>,
			T_request_pointer, T_request_args, tuple_v<t_request_args_number...>, T_Next>
		{
			using type = tuple_t<tuple_v<t_access_number...>, T_request_pointer,
				tuple_t<N_Tuple::U_Element_t<t_request_args_number, T_request_args>...>>;

			using next = T_Next;

			constexpr S_Function_Operator_Helper_Core(auto... args) :
				T_Next(args...) {}
		};




		//�d�l
		//[T_Parts...]�����ɑS�ʂ��operator()�ɃA�N�Z�X����ׂ̃f�[�^���쐬����B
		//
		//�e���v���[�g
		//[T_access_number]::�֐��I�u�W�F�N�g�P�P�̎g�p��������̔ԍ���Z�߂��^
		//[T_request_pointer]::�֐��I�u�W�F�N�g�P�P�̗v������|�C���^�[�̌^��Z�߂��^
		//[T_request_args]::�֐��I�u�W�F�N�g�P�P�̗v����������̌^��Z�߂��^
		//
		//using
		//[::type] 1�ʂ��operator()�ɃA�N�Z�X����ׂ̃f�[�^�ƁA���ȍ~�ɏ�����������f�[�^����������
		// [S_Function_Operator_Helper_Core]���Ăяo���B
		// ���ɏ�������f�[�^���Ȃ��ꍇ�́A[invalid_t]��ݒ肷��
		// 
		//�⑫
		//�֐��I�u�W�F�N�g�P�ɑ΂��āA�����̊֐����Z�߂��Ă���ꍇ�A������W�J������������
		template<
			class T_access_number = typename fn_multi_data::access_number,
			class T_request_pointer = typename core::request_pointer,
			class T_request_args = typename core::request_args>
		struct S_Function_Operator_Helper
		{
			using type = 
				S_Function_Operator_Helper;
		};
		

		//�d�l
		//[T_Parts...]�Ɋ֐���1�����Ȃ��ꍇ
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
			using type = S_Function_Operator_Helper_Core<
				typename T_access_number::type,
				T_request_pointer, T_request_args,
				N_Tuple::U_index_sequence<
				N_Tuple::S_Parameter<T_request_args>::head_size
				+not_is_invalid<typename T_request_args::type>
				>,
				invalid_t>;
		};

		//�d�l
		//�c��̊֐���1�����Ȃ��ꍇ
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

		//�d�l
		//�擪�̊֐��I�u�W�F�N�g�̎g�p��������̔ԍ���Z�߂��^���g�p����f�[�^��Z�߂�
		//
		//�⑫
		//�֐��I�u�W�F�N�g�P�ɑ΂��āA�����̊֐����Z�߂��Ă���ꍇ�A������W�J������������ׁA
		//�c��́u�֐��I�u�W�F�N�g�̎g�p��������̔ԍ���Z�߂��^�v�Ɓu�v����������̌^�v���������Ȃ�܂ł́A
		//�擪�̈����̔ԍ����g�p����֐��̃f�[�^�ƌ��Ȃ��ď���������
		template<
			size_t ...t_access_number,
			class ...T_access_number,
			class T_Front_request_pointer,
			class ...T_request_pointer,
			class T_Front_request_args,
			class ...T_request_args >
			requires requires
		{
			requires (sizeof...(T_request_pointer) >= sizeof...(T_access_number));
		}
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>, T_access_number...>,
			tuple_t<T_Front_request_pointer, T_request_pointer...>,
			tuple_t<T_Front_request_args, T_request_args...>>
		{

			using next = S_Function_Operator_Helper<
				tuple_t<tuple_v<t_access_number...>, T_access_number...>,
				tuple_t<T_request_pointer...>,
				tuple_t<T_request_args...>>::type;

			using type = S_Function_Operator_Helper_Core<
				tuple_v<t_access_number...>,
				T_Front_request_pointer, T_Front_request_args,
				N_Tuple::U_index_sequence<
					N_Tuple::S_Parameter<T_Front_request_args>::head_size + not_is_invalid<typename T_Front_request_args::type>>,
				next>;
		};

		//�d�l
		//�擪�̊֐��I�u�W�F�N�g�̎g�p��������̔ԍ���Z�߂��f�[�^���g�p���Ȃ��A
		//�v����������A�|�C���^�[�̌^�A�̏ꍇ�A�擪�̊֐��I�u�W�F�N�g�̎g�p��������̔ԍ������ɐi�߂�
		//
		//�⑫
		//�֐��I�u�W�F�N�g�̎g�p��������̔ԍ���Z�߂��^���A�v����������̌^�̎c�萔��葽���ꍇ�A
		// �擪�̊֐��I�u�W�F�N�g�̎g�p��������̔ԍ������ɐi�߂锻�������
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

		//�d�l
		//�֐��I�u�W�F�N�g�P�ɑ΂��āA�����̊֐����Z�߂��Ă���ꍇ�A������W�J����
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


		//�d�l
		//[S_Function_Operator_Helper]����[S_Function_Operator_Helper_Core]���󂯎��A
		//�P�ʂ��operator()�̃f�[�^��[T_Result]�Ɋi�[�A�y�ю��̃f�[�^���擾����
		template<class T_Result=tuple_t<> ,class T_Operator_Data =typename S_Function_Operator_Helper<>::type>
		struct S_Function_Operator_Parameter
		{
			using type = T_Result;
		};

		template<class ...T_Result, not_is_invalid T_Operator_Data>
		struct S_Function_Operator_Parameter<tuple_t<T_Result...>, T_Operator_Data>
		{

			//�d�l
			//�v����������̌^�������l�Ȃ�A�f�[�^�̊i�[���X�L�b�v����
			template<class T_Request_Args = N_Tuple::U_Element_t<2,typename T_Operator_Data::type>>
			struct S_Request_Args_Chack
			{
				using type= S_Function_Operator_Parameter<
					tuple_t<T_Result..., typename T_Operator_Data::type>,
					typename T_Operator_Data::next>::type;
			};

			template<>
			struct S_Request_Args_Chack<invalid_t>
			{
				using type= S_Function_Operator_Parameter<
					tuple_t<T_Result...>,
					typename T_Operator_Data::next>::type;
			};

			using type = S_Request_Args_Chack<>::type;
		};

		using type = S_Function_Operator_Parameter<>::type;

	};


}










