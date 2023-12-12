#pragma once

#include"Function_Args_Chack.h"

namespace N_Function
{

	template<class T_Request_Args = invalid_t, class T_Request_Pointer = invalid_t>
	struct Request_Core
	{
		using request_args = T_Request_Args;

		using request_pointer = T_Request_Pointer;
	};

	template<class T_Fn_Data>
	struct I_Request
	{

		template<class T_Request>
		struct I_Request_Data
		{
			//�d�l
			//�������������[T_Fn_Data]����擾���A�v����������Ɣ��肷��
			//
			//�⑫
			//�֐����Z�߂��Ă���ꍇ�A[tuple_t]�œZ�߂�
			template<class T_Request_Args = typename T_Request::request_args,
				class T_Bind_Args = typename T_Fn_Data::bind_args>
			struct S_Request_args
			{
				using type = I_Function_Args_Chack<T_Request_Args, T_Bind_Args>::request_args;
			};

			template<class T_Request_Args>
			struct S_Request_args<T_Request_Args, invalid_t>
			{
				using type = T_Request_Args;
			};


			//�d�l
			//�v������|�C���^�[�̌^��[T_Fn_Data]����擾���A
			// �݊����̂���|�C���^�[���Z�b�g����ē���Ηv����������
			//
			//�⑫
			//�֐����Z�߂��Ă���ꍇ�A[tuple_t]�œZ�߂�
			//�K�v�łȂ��ꍇ�A[invalid_t]���Ԃ�
			template<class T_Request_pointer = typename T_Request::request_pointer,
				class T_Pointer = typename T_Fn_Data::pointer,
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

			using type = Request_Core<
				typename S_Request_args<>::type,
				typename S_Request_pointer<>::type>;

		};

		template<class T_Request>
		struct S_Request
		{
			using type = I_Request_Data<T_Request>::type;
		};

		template<class ...T_Request>
		struct S_Request<tuple_t<T_Request...>>
		{
			using type = tuple_t<typename S_Request<T_Request>::type...>;
		};

		template<class T_Fn = typename T_Fn_Data::function>
		struct S_Request_Access
		{
			using type = T_Fn::request;
		};

		template<class ...T_Fns>
		struct S_Request_Access<tuple_t<T_Fns...>>
		{
			using type = tuple_t<typename T_Fns::request...>;
		};

		template<>
		struct S_Request_Access<invalid_t>
		{
			using type = invalid_t;
		};

		using type = S_Request_Access<>::type;

	};

}