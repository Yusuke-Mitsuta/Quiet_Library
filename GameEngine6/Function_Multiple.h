#pragma once

#include"Function_Multiple_Helper.h"
#include"Function_Multiple_Operator.h"


namespace N_Function
{

	//�d�l
	//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
	//
	//�e���v���[�g
	//�֐��|�C���^�[�A����ɑ΂���������s�K���Ȃ�[T_FlontFn]��[std::nullopt_t]�ɂȂ�
	template<not_same_as<std::nullopt_t> T_FlontFn, class ...T_Fns>
	class Function_Multiple :
		public N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type
	{

	public:

		using N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type::operator();

		//�d�l
		//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
		//
		//����
		//fns::�֐��|�C���^�[or[Function_Single]�A����ɑ΂�������A���̊֐��Ƒ���
		//
		//�⑫
		//�֐��ɑ΂��Ĉ������������Ȃ��ꍇT_Fns��[std::nullopt_t]�ɂȂ萶���s�ɂȂ�
		template<class MT_FlontFn, class ...MT_Fns>
		constexpr Function_Multiple(MT_FlontFn flontFn, MT_Fns... fns) :
			N_Function::IS_Function_Multiple_Operator<MT_FlontFn, MT_Fns...>::Type(flontFn, fns...) {}

	};

	template<class MT_FlontFn, class ...MT_Fns>
	Function_Multiple(MT_FlontFn setfn, MT_Fns... setFns) -> Function_Multiple
		<typename N_Function::IS_Function_Multiple_Helper<MT_FlontFn, MT_Fns...>::Judge, MT_Fns...>;

}