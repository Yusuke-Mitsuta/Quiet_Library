#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Convert_Order.h"
#include"Tuple_Apply_Args_Convert_Action.h"
#include"Tuple_Apply_Type_Chack.h"

#include"main.h"

namespace N_Tuple
{

	namespace N_Apply
	{

		template<class T_Fn, class ...T_Set_Types>
		static constexpr bool Chack()
		{
			return static_cast<bool>(N_Apply::I_Type_Chack<
				typename  N_Apply::I_Request<T_Fn, T_Set_Types...>::args,
				tuple_t<T_Set_Types...>>::value+1);
		}

	}




	//�d�l
	//�ϐ��ɑ΂��āA��Α��A���Έ�A���Α��̕ϊ����s���A
	// �֐��I�u�W�F�N�g�A�N���X�R���X�g���N�^�����s����
	//
	//�e���v���[�g
	// [T_Fn_Action]�F�ϐ������Ď��s����A[�֐��|�C���^�[�AFunction�A�N���X]�̌^
	//[T_Set_Types...]�F��Α��A���Έ�A���Α��̕ϊ��𔺂��ϐ�
	// 
	//�⑫
	//���s��[::Apply(args...)]���Ăяo����
	//��Α��̕ϊ��̓R���X�g���N�^���Ăяo���鎖�A
	//���Έ�̕ϊ��͓W�J����ϐ��̃N���X��
	// [using tuple=tuple_t< ... >]�A[auto& get<N>()]�L�q����Ă��鎖�B
	//
	// ��Α��̕ϊ����A�ϊ����[&],[*]�͎����ŕ⊮����邪�A
	// �ϊ���̕ϐ��ƕϊ��ɗp�����ϐ��̊֌W�͌ʂɒ�`����Ȃ�����R�s�[�ł���B
	template<class T_Fn,class ...T_Set_Types>
	struct I_Apply_Action
	{
	//private:


		using request = N_Apply::I_Request<T_Fn, T_Set_Types...>;

		using apply = N_Apply::I_Args_Convert_Action<typename request::args,
			tuple_t<T_Set_Types...>>::type;

	public:

		//�d�l
		//�^[fn]�ɑ΂��āA�v�������[args...] ����Α��A���Έ�̕ϊ����s���A
		// [fn]�̃R���X�g���N�^�����s����(��������)�B
		template<class T_Create_class = T_Fn, class ...T_Args>
			requires (N_Apply::is_apply_type<T_Create_class, N_Apply::E_Type::CLASS> ||
					  N_Apply::is_apply_type<T_Create_class, N_Apply::E_Type::CLASS_NEW>)
		static constexpr auto Apply(T_Args&&... args)
		{
			N_Apply::S_Class_Create<T_Create_class> fn_action = {};
			return apply::Apply(&fn_action, std::forward<T_Args>(args)...);
		}

		//�d�l
		//�z��^�̃|�C���^�[[array_p]��[T_Fn]��0�����ڂ̗v�f����ǉ�����B
		template<class T_Array, class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::ARRAY>
		static constexpr auto Apply(T_Array* array_p, T_Args&&... args)
		{
			N_Apply::S_Array_Create fn_action = { array_p };
			return apply::Apply(&fn_action, std::forward<T_Args>(args)...);
		}

		//�d�l
		//�֐�[fn]�ɑ΂��āA�v�������[args...] ����Α��A���Έ�̕ϊ����s���A
		// [fn]�����s����
		template<class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>
		static constexpr auto Apply(T_Fn&& fn,T_Args&&... args)
		{
			N_Apply::S_Fn_Action fn_action(fn, &invalid);
			return apply::Apply(&fn_action,std::forward<T_Args>(args)...);
		
		}

		//�d�l
		//�֐�[fn]�ɑ΂��āA�v�������[args...] ����Α��A���Έ�̕ϊ����s���A
		// �|�C���^�[��p����[fn]�����s����
		template<class ...T_Args>
			requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>
		static constexpr auto Apply(T_Fn&& fn,request::pointer* p,T_Args&&... args)
		{
			N_Apply::S_Fn_Action fn_action(fn, p);
			return apply::Apply(&fn_action,std::forward<T_Args>(args)...);
		}
	};


}

