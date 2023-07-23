#pragma once
#include"Function.h"
#include"tuple_Helper.h"
#include"MethodSearch.h"
#include"Function_Bind_Fns.h"

//�d�l
//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
//
//�e���v���[�g
//T_FlontFn,T_Fns...::�֐��|�C���^�[�A����ɑ΂��������Tuple
//
//�⑫
//T_FlontFn,T_Fns...�͊֐��|�C���^�[�A����Ɏw�肷������A���̊֐��|�C���^�[�A�ƂȂ�悤�ɂ��鎖
//�֐��|�C���^�[�A����ɑ΂���������s�K���Ȃ�[T_FlontFn]��[std::nullopt_t]�ɂȂ�
template<not_same_as<std::nullopt_t> T_FlontFn, class ...T_Fns>
class FunctionMultiple
{
	T_FlontFn fns;

public:

	template<class ...MT_Fns>
	constexpr FunctionMultiple(MT_Fns... setFns)
		:fns(N_Function::IS_BindFns(setFns...)) {}
	
	template<class ...MT_Args>
		requires std::same_as <typename N_Function::IS_MethodSearch<T_FlontFn,MT_Args...>::Judge, std::true_type>
	constexpr auto operator()(MT_Args... args)
	{
		return std::get<N_Function::IS_MethodSearch<T_FlontFn,MT_Args...>::MethodNumber>(fns)(args...);
	}

};

template<class ...MT_Fns>
FunctionMultiple(MT_Fns... fns) -> FunctionMultiple<typename N_Function::IS_BindFns<MT_Fns...>::FnsType>;
