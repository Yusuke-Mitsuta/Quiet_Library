#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	//�d�l
	//[T_Tuple]�̗v�f��������o���A[TT_Action]��[::type]�����s���A���ʂ�[tuple_t]�ɓZ�߂�
	//
	//�e���v���[�g
	//[TT_Action]::[type]���Ăяo���N���X�e���v���[�g
	//[T_Tuple]::�W�J���A�e�v�f��[TT_Action::type]���Ăяo��
	//[T_Extra...]::[TT_Action::type]���Ăяo���ہA�ǉ��ŃZ�b�g����^
	//
	//�⑫
	//[T_Tuple -> tuple_t<T...>] -> [tuple_t<TT_Action<T,T_Extra...>::type...>]�ƂȂ�
	template<template<class...>class TT_Action,class T_Tuple,class ...T_Extra>
	struct I_Elements_Action
	{
	private:
		template<class T_Tuple>
		struct S_Elements_Action
		{
			using type = TT_Action<T_Tuple, T_Extra...>::type;
		};

		template<class ...T>
		struct S_Elements_Action<tuple_t<T...>>
		{
			using type = tuple_t<typename TT_Action<T, T_Extra...>::type...>;
		};
	public:
		using type = S_Tuple_t_Change_Action<S_Elements_Action, T_Tuple>::Return_not_p;

	};

}