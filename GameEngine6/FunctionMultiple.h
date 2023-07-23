#pragma once
#include"Function.h"
#include"tuple_Helper.h"
#include"MethodSearch.h"
#include"Function_Bind_Fns.h"

//�d�l
//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
//
//�e���v���[�g
//T_Fns::tuple�Ƀ��b�s���O���ꂽ������[Function]
//�֐��|�C���^�[�A����ɑ΂���������s�K���Ȃ�[T_Fns]��[std::nullopt_t]�ɂȂ�
template<not_same_as<std::nullopt_t> T_Fns>
class FunctionMultiple
{
	T_Fns fns;

public:
	//�d�l
	//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
	//
	//����
	//setFns::�֐��|�C���^�[or[Function]�A����ɑ΂�������A���̊֐��Ƒ���
	//
	//�⑫
	//�֐��ɑ΂��Ĉ������������Ȃ��ꍇT_Fns��[std::nullopt_t]�ɂȂ萶���s�ɂȂ�
	template<class ...MT_Fns>
	constexpr FunctionMultiple(MT_Fns... setFns)
		:fns(N_Function::IS_BindFns(setFns...)) {}
	
	//�d�l
	//������[Function]����[T_Args...]�ŌĂяo����֐��I�u�W�F�N�g�����s����
	//
	//����
	//args::���͂������
	template<class ...T_Args>
		requires std::same_as<typename N_Function::IS_MethodSearch<T_Fns,T_Args...>::Judge, std::true_type>
	constexpr auto operator()(T_Args... args)
	{
		return std::get<N_Function::IS_MethodSearch<T_Fns,T_Args...>::MethodNumber>(fns)(args...);
	}

};

template<class ...MT_Fns>
FunctionMultiple(MT_Fns... fns) -> FunctionMultiple<typename N_Function::IS_BindFns<MT_Fns...>::FnsType>;
