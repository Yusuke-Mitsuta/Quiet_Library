#pragma once

#include"Tuple.h"
#include"Expand.h"

namespace N_Function
{

	template<class T_Request_Args, class T_Bind_Args>
	struct I_Function_Args_Chack
	{
		using type = invalid_t;
	};
	
	//�d�l
	//[T_Request_Args]��[T_Bind_Args]����납���r���A
	//�@�݊����̂���^�����肷��B
	//
	// �e���v���[�g
	// [T_Request_Args]�F�v����������̌^(tuple_tp)
	// [T_Bind_Args]�F�Z�b�g��������̌^(tuple_t)
	// 
	//�⑫
	// �݊����̂���^�̒�`�́A[N_Tuple::S_Parameter]�̓��ꉻ�ɂĒ�`���s��
	//
	template<class T_Request_Args, class T_Bind_Args>
		requires requires
	{
		requires N_Tuple::is_Tuple_t<T_Request_Args>;
		requires N_Tuple::is_Tuple_t<T_Bind_Args>;
	}
	struct I_Function_Args_Chack<T_Request_Args,T_Bind_Args>
	{
	public:

		using type = N_Tuple::N_Apply::I_Apply_Type_Chack<T_Request_Args, T_Bind_Args>::type::request;

	};

}
