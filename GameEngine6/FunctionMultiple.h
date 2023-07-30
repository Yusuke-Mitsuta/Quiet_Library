#pragma once

#include"FunctionMultipleOperator.h"
#include"FunctionMultiple_Static.h"

//�d�l
//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
//
//�e���v���[�g
//�֐��|�C���^�[�A����ɑ΂���������s�K���Ȃ�[T_FlontFn]��[std::nullopt_t]�ɂȂ�
template<not_same_as<std::nullopt_t> T_FlontFn,class ...T_Fns>
class FunctionMultiple : 
	public N_Function::IS_FunctionMultipleOperator<T_FlontFn, T_Fns...>::Type
{

public:

	using N_Function::IS_FunctionMultipleOperator<T_FlontFn, T_Fns...>::Type::operator();

	//�d�l
	//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
	//
	//����
	//fns::�֐��|�C���^�[or[Function]�A����ɑ΂�������A���̊֐��Ƒ���
	//
	//�⑫
	//�֐��ɑ΂��Ĉ������������Ȃ��ꍇT_Fns��[std::nullopt_t]�ɂȂ萶���s�ɂȂ�
	template<class MT_FlontFn,class ...MT_Fns>
	constexpr FunctionMultiple(MT_FlontFn flontFn, MT_Fns... fns):
		N_Function::IS_FunctionMultipleOperator<MT_FlontFn, MT_Fns...>::Type(flontFn,fns...){}

};

template<class MT_FlontFn, class ...MT_Fns>
FunctionMultiple(MT_FlontFn setfn, MT_Fns... setFns) -> FunctionMultiple
<typename N_Function::IS_FunctionMultiple_Helper<MT_FlontFn, MT_Fns...>::Judge, MT_Fns...>;

