#pragma once


#include"Tuple_Declare.h"

namespace N_Tuple::N_Apply
{
	//�d�l
	//��������N���X[T_Fn]�^�̕ϐ��𐶐�����B
	// [T_Fn*]�̏ꍇ�̓C���X�^���X���������{����B
	template<class T>
	struct S_Class_Create
	{
		constexpr S_Class_Create() {}

		//�N���X�̐���
		template<class MT_Fn = T, class... T_Args>
		constexpr auto Apply(T_Args&&... args)
		{
			return T{args... };
		}

		//�N���X�̃C���X�^���X����
		template<class MT_Fn = T, class... T_Args>
			requires requires
		{
			requires is_pointer<MT_Fn>;
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return new std::remove_pointer_t<T>{ args... };
		}

	};
}