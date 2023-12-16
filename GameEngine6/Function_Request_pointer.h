#pragma once

#include"Concept.h"

namespace N_Function
{

	//�d�l
	//�v������|�C���^�[�̌^��[T_Fn_Data]����擾���A
	// �݊����̂���|�C���^�[���Z�b�g����ē���Ηv����������
	//
	//�⑫
	//�֐����Z�߂��Ă���ꍇ�A[tuple_t]�œZ�߂�
	//�K�v�łȂ��ꍇ�A[invalid_t]���Ԃ�
	template<class T_Request_pointer, class T_Pointer,
		bool t_judge = convertible_to<T_Pointer, T_Request_pointer>>
		struct S_Request_pointer
	{
		using type = T_Request_pointer;
	};

	template<class T_Request_pointer, class T_Pointer>
	struct S_Request_pointer<T_Request_pointer, T_Pointer, 1>
	{
		using type = invalid_t;
	};


	template<class T_Fn_Data, class T_Request>
	struct S_Request_pointer_Access
	{
		using request = T_Request::request_pointer;

		using type =
			typename S_Request_pointer<request,
			typename T_Fn_Data::pointer>::type;
	};

}