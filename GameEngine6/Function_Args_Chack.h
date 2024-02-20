#pragma once

#include"Tuple.h"

namespace quiet::N_Function
{

	template<class T_Request_Args, class T_Bind_Args>
	struct I_Function_Args_Chack
	{
		using type = invalid_t;
	};
	
	//�d�l
	//[T_Request_Args]��[T_Bind_Args]���r���A
	//�@�݊����̂���^�����肷��B
	//
	// �e���v���[�g
	// [T_Request_Args]�F�v����������̌^(tuple_tp)
	// [T_Bind_Args]�F�Z�b�g��������̌^(tuple_t)
	// 
	//�⑫
	// �݊����̂���^�̒�`�́A[N_Tuple::S_Parameter]�̓��ꉻ�ɂĒ�`���s��
	template<class T_Request_Args, class T_Bind_Args>
		requires requires
	{
		requires N_Tuple::is_Tuple_t<T_Request_Args>;
		requires N_Tuple::is_Tuple_t<T_Bind_Args>;
	}
	struct I_Function_Args_Chack<T_Request_Args,T_Bind_Args>
	{
	public:


		//���P����
		//�v������^�̃��X�g��[tuple_tp]�A
		//�����̗v������^���X�g��Z�߂��^��[tuple_t]�ŋ�ʂ��Ă��邽�߉��P���邱��

		//�d�l
		//[I_Convert_Order]�ɂ��ƍ����A
		// �Z�b�g���������S�ĂŌ݊��������邩���肷��
		// 
		// �⑫
		//�v������^�̃��X�g��[tuple_tp]�A
		// �����̗v������^���X�g��Z�߂��^��[tuple_t]�ŋ�ʂ��Ă���
		template<class T_Chack_Result =
			typename N_Tuple::N_Apply::I_Convert_Order<typename T_Request_Args::remove_p, T_Bind_Args>::type,
			//class T_Request_Args = typename T_Chack_Result::request,
			class T_Bind_Args= typename T_Chack_Result::set>
		struct S_Function_Args_Chack
		{
			using type = invalid_t;
		};

		template<class T_Chack_Result>
		struct S_Function_Args_Chack<T_Chack_Result, tuple_t<>>
		{
			using type = typename T_Chack_Result::request::create_p;
		};

		using type = typename S_Function_Args_Chack<>::type;

	};

}
