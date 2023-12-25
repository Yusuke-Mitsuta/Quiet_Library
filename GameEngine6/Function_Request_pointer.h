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
	template<class T_Request_pointer, class T_Fn_Data,
		class T_Pointer =typename T_Fn_Data ::pointer>
		struct S_Request_pointer
	{
		using type =
			U_Judge_t<T_Request_pointer,
			convertible_to_not<T_Pointer, T_Request_pointer>>;
	};


	template<class T_Request>
	struct S_Request_pointer_Access
	{
		using type = T_Request::request_pointer;
	};

}