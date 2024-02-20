#pragma once

#include"Function_Request_Core.h"

#include"Function_Request_Args.h"
#include"Function_Request_pointer.h"

namespace quiet::N_Function
{

	template<class ...T_Parts>
	struct I_Function_Single_Data;

	//�d�l
	//[T_Fn_Data]�ɑ΂��āA[TT_Access]�ŗv������v�f���擾����
	//
	//�⑫
	//�A���ė���f�[�^�͊֐��I�u�W�F�N�g����[tuple_t]�œZ�߂��Ă���
	template<
		template<class...>class TT_Access, 
		template<class...>class TT_Action, 
		class T_Fn_Data>
	struct I_Function_Request_Data
	{

		template<class T_Request>
		struct S_Request
		{
			using type = TT_Action<T_Request,T_Fn_Data>::type;
		};

		template< class ...T_Request>
		struct S_Request<tuple_t<T_Request... >>
		{
			using return_t = tuple_t<typename S_Request<T_Request>::type...>;

			using type = U_Judge_t<return_t, same_as_nand<invalid_t,typename S_Request<T_Request>::type...>>;
		};

		template<class ...T_Request>
		struct S_Request<Request_Core<T_Request... >>
		{
			using type = 
				typename S_Request<typename TT_Access<Request_Core<T_Request... >>::type>::type;
		};

		//�d�l
		//���ʂ̊֐��I�u�W�F�N�g�ɑ΂��āA[::request]���擾����
		template<class T_Fn = typename T_Fn_Data::function>
		struct S_Function_Type
		{
			using type = int;
		};

		//�d�l
		//���ʂ̊֐��I�u�W�F�N�g�����݂��Ȃ��ׁA�V���ɒ�`����
		template<class T_CName, class T_RType, class ...T_Args>
		struct S_Function_Type<T_RType(T_CName::*)(T_Args...)>
		{
			
			using type = S_Request<Request_Core<typename tuple_t<T_Args...>::create_p,T_CName>>::type;
		};

		//�d�l
		//���ʂ̊֐��I�u�W�F�N�g�����݂��Ȃ��ׁA�V���ɒ�`����
		template< class T_RType, class ...T_Args>
		struct S_Function_Type<T_RType(*)(T_Args...)>
		{
			using type = S_Request<Request_Core<typename tuple_t<T_Args...>::create_p,invalid_t>>::type;
		};

		//�d�l
		//���ʂ̊֐��I�u�W�F�N�g�ɑ΂��āA[::request]���擾����
		template< class ...T_Parts>
		struct S_Function_Type<Function_Core<T_Parts...>>
		{
			using type = S_Request<typename Function_Core<T_Parts...>::request>::type;
		};

		//�d�l
		//[tuple_t]���O���āA�ēx����̎��{����
		template< class T_Fn>
		struct S_Function_Type<tuple_t<T_Fn>>
		{
			using type = typename S_Function_Type<T_Fn>::type;
		};

		//�d�l
		//[tuple_t]���O���āA�ēx����̎��{���A���̌��ʂ�tuple_t�ɓZ�߂�
		template< class ...T_Fns>
		struct S_Function_Type<tuple_t<T_Fns...>>
		{
			using type = tuple_t<typename S_Function_Type<T_Fns>::type...>;
		};

		using type = S_Function_Type<>::type;

	};


}