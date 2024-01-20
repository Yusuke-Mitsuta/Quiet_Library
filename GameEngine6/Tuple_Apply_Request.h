#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include<array>

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	template<class T_Fn, class T_Set_Types>
	struct I_Function_Operator_Search;
};

template<class _Ty1, size_t N>
class Array;

namespace N_Tuple::N_Apply
{
	//�d�l
	//�֐��I�u�W�F�N�g�̈����ƃ|�C���^�[�̌^���擾����.
	// �֐��I�u�W�F�N�g���Ɋ֐��I�u�W�F�N�g�����������Ă���ꍇ�A
	// �@��ԏ��߂Ɉ����ƌ݊��������������̂��Ă΂��B
	template<class T,class ...T_Set_Types>
	struct I_Request
	{

		template<class T=T,E_Type t_type = Select_Type_v<T>>
		struct S_Request
		{
			using args = invalid_t;
			using pointer = invalid_t;
		};

		template<class T>
		struct S_Request<T,E_Type::CLASS>
		{
			using args = tuple_t<T>;
			using pointer = invalid_t;
		};

		template<class T>
			requires is_invalid_not<typename S_Parameter<T>::tuple>
		struct S_Request<T, E_Type::CLASS>
		{
			using args = S_Parameter<T>::tuple;
			using pointer = invalid_t;
		};

		template<class T>
		struct S_Request<T,E_Type::CLASS_NEW>:
			S_Request<T,E_Type::CLASS>
		{};

		template<class T,size_t N>
		struct S_Request<T[N], E_Type::ARRAY>
		{
			using args = U_Repeat_Multiple<T, N>;
			using pointer = invalid_t;
		};

		//�d�l
		//�֐��I�u�W�F�N�g�̈����ƃ|�C���^�[�̌^���擾����B
		template<class T>
		struct S_Request<T,E_Type::FN>
		{
			using fn_core = N_Function::Function_Core<T>;
			using args = fn_core::request_args;
			using pointer = fn_core::request_pointer;
		};

		//�d�l
		// �֐��I�u�W�F�N�g���Ɋ֐��I�u�W�F�N�g�����������Ă���ꍇ�A
		// �@��ԏ��߂Ɉ����ƌ݊��������������̂��Ă΂��B
		template<class ...T_Parts>
		struct S_Request<Function<T_Parts...>,E_Type::FN>
		{
			using operator_search = N_Function::I_Function_Operator_Search<T, tuple_t<T_Set_Types...>>::type;
			using args = U_Select<1, operator_search>::back;
			using pointer = U_Select<2, operator_search>;
		};

		using args = S_Request<>::args;

		using pointer = S_Request<>::pointer;

	};
}