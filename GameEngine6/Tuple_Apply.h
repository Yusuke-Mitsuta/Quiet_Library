#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Action.h"

namespace N_Tuple
{

	//�d�l
	//�֐�[fn]�ɑ΂��āA
	// [args...]�̒��g��K�؂ɓW�J���A���s����
	template<class T_Fn, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>;
		requires is_invalid_not<U_Apply_chack<T_Fn, T_Args...>>;
	}
	static constexpr auto Apply(T_Fn&& fn, T_Args&&... args)
	{
		return I_Apply_Action<T_Fn, T_Args...>::Apply(
			std::forward<T_Fn>(fn),
			std::forward<T_Args>(args)...);
	}


	//�d�l
	//�֐�[fn]�ɑ΂��āA
	//�|�C���^[p]��p���āA[args...]�̒��g��K�؂ɓW�J���A���s����
	template<class T_Fn, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>;
		requires is_invalid_not<U_Apply_chack<T_Fn, T_Args...>>;
	}
	static constexpr auto Apply(T_Fn&& fn, auto* p, T_Args&&... args)
	{
		return I_Apply_Action<T_Fn, T_Args...>::Apply(
			std::forward<T_Fn>(fn),
			p,
			std::forward<T_Args>(args)...);
	}


	//�d�l
	//�N���X[T]�̃R���X�g���N�^�ɑ΂��āA
	//[args...]�̒��g��K�؂ɓW�J���A���s����
	template<class T, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T, N_Apply::E_Type::CLASS>;
		requires is_invalid_not<U_Apply_chack<T, T_Args...>>;
	}
	static constexpr auto Apply(T_Args&&... args)
	{
		return I_Apply_Action<T, T_Args...>::Apply(
			std::forward<T_Args>(args)...);
	};

	//�d�l
	//�N���X[T]�̃R���X�g���N�^�ɑ΂��āA
	//[args...]�̒��g��K�؂ɓW�J���ANew����
	template<class T, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T, N_Apply::E_Type::CLASS_NEW>;
		requires is_invalid_not<U_Apply_chack<T, T_Args...>>;
	}
	static constexpr auto Apply(T_Args&&... args)
	{
		return I_Apply_Action<T, T_Args...>::Apply(
			std::forward<T_Args>(args)...);
	}


	//�d�l
	//�z��^�̎Q�Ƃ�[array_ref]��[args...]�̒��g��K�؂ɓW�J���A�ǉ�����B
	// 
	// ����
	// [array_ref]�F�v�f���i�[����z��̎Q��
	// [args...]�Ftuple�ɂ��K�؂ɕϊ�����A�z��Ɋi�[����ϐ�
	template<class T_Array, size_t N, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T_Array[N], N_Apply::E_Type::ARRAY>;
		requires is_invalid_not<U_Apply_chack<T_Array, T_Args...>>;
	}
	static constexpr void Apply(T_Array(&array_ref)[N], T_Args&&... args)
	{
		I_Apply_Action<T_Array[N], T_Args...>::Apply(&array_ref,
			std::forward<T_Args>(args)...);
	}

	//�d�l
	//����̗v�f���w���A�z��^�̃|�C���^�[[array_p]��[set_Num]�̐�����[args...]�̒��g��K�؂ɓW�J���A�ǉ�����B
	//
	//�e���v���[�g
	//[set_Num]�F�v�f��ǉ����鑍��
	// 
	// ����
	// [array_p]�F�z��̓���̗v�f���w���|�C���^�[
	// [args...]�Ftuple�ɂ��K�؂ɕϊ�����A�z��Ɋi�[����ϐ�
	// 
	//�⑫
	// [array_p] �ɂ���
	// [int n[5] ]�Ƃ����z�񂪂��鎞
	// [int* p = &n[2]; ]p������̗v�f��(��Ԗ�)���w�����ɂȂ�B
	template<size_t set_Num, class T_Array, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T_Array[set_Num], N_Apply::E_Type::ARRAY>;
		requires is_invalid_not<U_Apply_chack<T_Array[set_Num], T_Args...>>;
	}
	static constexpr void Apply(T_Array* array_p, T_Args&&... args)
	{
		I_Apply_Action<T_Array[set_Num], T_Args...>::Apply(array_p,
			std::forward<T_Args>(args)...);
	}

}