#pragma once
#include<tuple>

namespace N_Function
{
	//�d�l
	//�擪�̊֐��ɑ΂��āA�߂�l�A�N���X�A�����̌^��Ԃ��B
	//�֐��ȍ~�̈����ɑ΂��āA���݃o�C���h�ς݂̈����̌^��Ԃ�
	template<class T_Fn,class ...T_Args>
	struct S_MethodData {};

	template<class T_CName, class T_RType, class ...T_Args, class ...T_SetArgs >
	struct S_MethodData<T_RType(T_CName::*)(T_Args...), T_SetArgs...>
	{
		//�d�l
		//�֐��̌^
		using Fn =T_RType(T_CName::*)(T_Args...);

		//�d�l
		//�����̌^
		using BindArgs = std::tuple<T_SetArgs...>;

		//�d�l
		//���܂łɎw��ς݂̈����̌^
		using BoundArgs = BindArgs;

		//�d�l
		//�֐�����������N���X�̌^
		using CName = T_CName;

		//�d�l
		//�߂�l�̌^
		using RType = T_RType;

		//�d�l
		//�֐��̈����ɗv������Ă�������̌^
		using Args = std::tuple<T_Args...>;

		//�d�l
		//�֐��{�̂̃f�[�^���ǂ���
		using Root = std::true_type;
	};

	template<class T_FunctionInner, class ...T_SetArgs >
	struct S_MethodData<Function<T_FunctionInner>, T_SetArgs...>
	{
		//�d�l
		//���Ɉꕔ�������w��ς݂̊֐��̌^
		using Fn = Function<T_FunctionInner>;

		//�d�l
		//[Fn]��MethodData�ɃA�N�Z�X����
		using ParentFn = S_MethodData<T_FunctionInner>;

		using BindArgs = std::tuple<T_SetArgs...>;

		//�d�l
		//���܂łɎw��ς݂̈����̌^
		using BoundArgs = IS_TupleUnzip<BindArgs,typename ParentFn::BoundArgs>::Type;

		using CName = ParentFn::CName;
		using RType = ParentFn::RType;
		using Args = ParentFn::Args;
		using Root = std::false_type;
	};

	template<class T_CName, class T_RType, class ...T_Args, class ...T_SetArgs >
	struct S_MethodData<std::tuple<T_RType(T_CName::*)(T_Args...), T_SetArgs...>>:
		public S_MethodData<T_RType(T_CName::*)(T_Args...), T_SetArgs...>{};

	template<class T_FunctionInner, class ...T_SetArgs >
	struct S_MethodData<std::tuple<Function<T_FunctionInner>, T_SetArgs...>> :
		public S_MethodData<Function<T_FunctionInner>, T_SetArgs...>{};
}