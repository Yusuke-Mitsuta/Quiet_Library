#pragma once

//#include"Function_Multiple_Helper.h"
//#include"Function_Multiple_Operator.h"


//namespace N_Function
//{
//
//	//�d�l
//	//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
//	//
//	//�e���v���[�g
//	//�֐��|�C���^�[�A����ɑ΂���������s�K���Ȃ�[T_FlontFn]��[std::nullopt_t]�ɂȂ�
//	template<not_same_as<std::nullopt_t> T_FlontFn, class ...T_Fns>
//	class Function_Multiple :
//		public N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type
//	{
//
//		using Parent = N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type;
//
//	public:
//
//		using N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type::operator();
//
//		template<int function_Number>
//		using N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type::Select<function_Number>();
//
//
//		//�d�l
//		//�����̊֐��|�C���^�[�A�y�т���ɑ΂�������̒l�����������A�����v�Ŕ��肷��
//		//
//		//����
//		//[MT_Fn_Parts...]::(���ʂŎg�p����N���X�|�C���^�[ , �֐��|�C���^�[or�֐��I�u�W�F�N�g , ����ɑ΂������ , ���Ŏg�p����N���X�|�C���^�[ . �֐��|�C���^�[or�֐��I�u�W�F�N�g ...)
//		//
//		//�ÓI�Ȋ֐��|�C���^�[ and �֐�Object�̓N���X�|�C���^�[�̐ݒ�s��
//		//
//		//���ʂŎg�p����N���X�̃|�C���^�[�̓N���X�|�C���^�[���ݒ肳��Ă��Ȃ��֐��|�C���^�[���Ăяo���̂Ɏg�p����
//		//
//		//���ʂŎg�p����N���X�|�C���^�[�͑S�Ă̊֐��|�C���^�[���Ăяo����ꍇ�ݒ�s�v
//		// 
//		//�⑫
//		//�֐��ɑ΂��Ĉ������������Ȃ��ꍇT_Fns��[std::nullopt_t]�ɂȂ萶���s�ɂȂ�
//		template<class ...MT_Fn_Parts>
//		constexpr Function_Multiple(MT_Fn_Parts... fn_Parts) :
//			N_Function::IS_Function_Multiple_Operator<MT_Fn_Parts...>::Type(fn_Parts...) {}
//
//	};
//
//	template<class MT_Flnot_Fn_Parts, class ...MT_Fn_Parts>
//	Function_Multiple(MT_Flnot_Fn_Parts flnot_Fn_Parts, MT_Fn_Parts... fn_Parts) -> Function_Multiple
//		<typename N_Function::IS_Function_Multiple_Helper<MT_Flnot_Fn_Parts, MT_Fn_Parts...>::Judge, MT_Fn_Parts...>;
//
//}