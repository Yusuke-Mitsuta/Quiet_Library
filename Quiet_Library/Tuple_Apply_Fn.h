#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple::N_Apply
{


	//�d�l
	//�֐��I�u�W�F�N�g�ƃ|�C���^�[���擾���A
	//�֐��I�u�W�F�N�g�ɂ���āA�K�؂Ƀ|�C���^�[���g�p����B
	// 
	//�⑫
	//[T_Fn_Action]��
	//���I�֐��̏ꍇ�F�|�C���^�[���g�p���֐��|�C���^�[�ɃA�N�Z�X����
	//Function�̏ꍇ�F�|�C���^�[�̗v���̗L���ɂ���Ďg�p�𔻒f����
	//�ÓI�֐��̏ꍇ�F�|�C���^�[���g�p�����֐��|�C���^�[�ɃA�N�Z�X����
	template<class T_Fn_Action, class T_pointer>
	struct S_Fn_Action
	{
		T_Fn_Action fn;

		T_pointer* p;

		constexpr S_Fn_Action(T_Fn_Action set_fn, T_pointer* set_pointer) :
			fn(set_fn), p(set_pointer) {}

		constexpr S_Fn_Action(T_Fn_Action set_fn, T_pointer set_pointer) :
			fn(set_fn), p(&invalid) {}


		//�|�C���^�[���g�p�����֐��I�u�W�F�N�g�ɃA�N�Z�X����
		template<class MT_Fn = T_Fn_Action, is_invalid MT_pointer = T_pointer, class... T_Args>
		constexpr auto Apply(T_Args&&... args)
		{
			return fn(args...);
		}

		//�|�C���^�[���g�p���֐��I�u�W�F�N�g�ɃA�N�Z�X����
		template<class MT_Fn = T_Fn_Action, is_invalid_not MT_pointer = T_pointer, class... T_Args>
			requires requires
		{
			requires std::is_member_function_pointer_v<MT_Fn>;
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return (p->*fn)(args...);
		}

		//�|�C���^�[�������ɒǉ����A[Function]�ɃA�N�Z�X����
		template<class MT_Fn = T_Fn_Action, is_invalid_not MT_pointer = T_pointer, class... T_Args>
			requires requires
		{
			requires same_as_template_type<MT_Fn, Function>;
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return fn(p, args...);
		}

	};
}