#pragma once
#include"FunctionMultiple.h"
#include"Function.h"
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
template<class T_FlontFn, class ...T_Fns>
	requires not_same_as<T_FlontFn, std::nullopt_t>
class FunctionMultiple
{
public:

	std::tuple<T_FlontFn, T_Fns...> fns;

	template<class ...MT_Fns>
	constexpr FunctionMultiple(MT_Fns... setFns)
		:fns(N_Function::IS_BindFns(setFns...)) {}
	

};

template<class ...MT_Fns>
FunctionMultiple(MT_Fns... fns) -> FunctionMultiple<typename N_Function::IS_BindFns<MT_Fns...>::FnsType>;
