#pragma once


#include"Tuple_Declare.h"

namespace N_Tuple::N_Apply
{
	//�d�l
	//��������N���X[T_Fn]�^�̕ϐ��𐶐�����B
	// [T_Fn*]�̏ꍇ�̓C���X�^���X���������{����B
	template<class T, class T_Request_Args = typename S_Parameter<T>::tuple>
	struct S_Class_Create {};

	template<class T, class ...T_Request_Args>
	struct S_Class_Create<T,tuple_t<T_Request_Args...>>
	{
		constexpr S_Class_Create() {}

		//�N���X�̐���
		template<class MT_Fn = T, class... T_Args>
		constexpr auto Apply(T_Args&&... args)
		{
			return T{static_cast<T_Request_Args>(args)... };

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