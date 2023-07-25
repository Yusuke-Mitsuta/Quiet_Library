#pragma once
#include"Function.h"
#include"tuple_Helper.h"
#include"FunctionMultiple_Helper.h"

//�d�l
//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
//
//�e���v���[�g
//T_Fns::tuple�Ƀ��b�s���O���ꂽ������[Function]
//�֐��|�C���^�[�A����ɑ΂���������s�K���Ȃ�[T_Fns]��[std::nullopt_t]�ɂȂ�
template<not_same_as<std::nullopt_t> T_FlontFn,class ...T_Fns>
class FunctionMultiple
{
	std::tuple<T_FlontFn,T_Fns...> fns;

public:

	//�d�l
	//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
	//
	//����
	//setFns::�֐��|�C���^�[or[Function]�A����ɑ΂�������A���̊֐��Ƒ���
	//
	//�⑫
	//�֐��ɑ΂��Ĉ������������Ȃ��ꍇT_Fns��[std::nullopt_t]�ɂȂ萶���s�ɂȂ�
	template<class MT_FlontFn,class ...MT_Fns>
	constexpr FunctionMultiple(MT_FlontFn setfn, MT_Fns... setFns)
		:fns(setfn,setFns...)
	{}
	
	//�d�l
	//������[Function]����[T_Args...]�ŌĂяo����֐��I�u�W�F�N�g�����s����
	//
	//����
	//args::���͂������
	template<class ...T_Args>
		requires not_same_as<typename N_Function::IS_FunctionMultiple_Helper<std::tuple<T_Args...>,T_FlontFn,T_Fns...>::MethodSearch, std::nullopt_t>
	constexpr auto operator()(T_Args... args)
	{
		return N_Function::IS_FunctionMultiple_Helper<std::tuple<T_Args...>, T_FlontFn, T_Fns...>::MethodSearch::Execution(fns, args...);
	}

};

template<class MT_FlontFn, class ...MT_Fns>
FunctionMultiple(MT_FlontFn setfn, MT_Fns... setFns) -> FunctionMultiple
//<MT_FlontFn, MT_Fns...>;
<typename N_Function::IS_FunctionMultiple_Helper<std::tuple<>,MT_FlontFn, MT_Fns...>::SetJudge, MT_Fns...>;

