#pragma once

#include"Function_Args_Chack.h"

namespace N_Function
{

	//�d�l
	//�������������[T_Fn_Data]����擾���A�v����������Ɣ��肷��
	//
	//�⑫
	//�֐����Z�߂��Ă���ꍇ�A[tuple_t]�œZ�߂�
	template<class T_Request_Args, class T_Bind_Args>
	struct S_Request_args
	{
		using type = I_Function_Args_Chack<T_Request_Args, T_Bind_Args>::request_args;
	};

	template<class T_Request_Args>
	struct S_Request_args<T_Request_Args, invalid_t>
	{
		using type = T_Request_Args;
	};

	template<class T_Fn_Data, class T_Request>
	struct S_Request_args_Access
	{
		using request = T_Request::request_args;

		using type = 
			typename S_Request_args<request,
			typename T_Fn_Data::bind_args>::type;
	};
	

}