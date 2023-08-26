#pragma once

#include"Function_Single_Helper.h"
#include"Function_Single_Operator.h"
#include"Concept.h"
#include"Function_Core.h"
#include"SwapType.h"

namespace N_Function
{

	//�d�l
	//�֐��I�u�W�F�N�g�̒P�̂�\��
	template<not_same_as<std::nullopt_t> T_Method, class ...TP_Args>
	class Function_Single :
		public N_Function::IS_Function_Single_Operator<T_Method, TP_Args...>::Type
	{
	protected:

		using MethodData = N_Function::S_MethodData<T_Method, TP_Args...>;

		using FunctionOperator = N_Function::IS_Function_Single_Operator<T_Method, TP_Args...>::Type;

	public:

		using FunctionOperator::operator();

		constexpr Function_Single* operator->()
		{
			return this;
		}

		//�d�l
		//��̊֐������A�֐��I�u�W�F�N�g���쐬����
		//
		//����
		//fn::�֐��|�C���^�[
		//args...���炩���߃Z�b�g�������
		//
		//�⑫
		//[args...]�͌��l�߂ŃZ�b�g�����
		//[Fn( ... , args... )]�ƂȂ�
		template<class T_RType, class ...MT_Args, class ...MT_SetArgs>
		constexpr Function_Single(T_RType(*fn)(MT_Args...), MT_SetArgs ...args) :
			N_Function::IS_Function_Single_Operator<T_RType(*)(MT_Args...), MT_SetArgs...>::Type(
				Function_Core<T_RType(*)(MT_Args...)>(fn), args...) {}

		//�d�l
		//��̊֐������A�֐��I�u�W�F�N�g���쐬����
		//
		//����
		//set_p::�N���X�̃|�C���^�[
		//fn::�֐��|�C���^�[
		//args...���炩���߃Z�b�g�������
		//
		//�⑫
		//[args...]�͌��l�߂ŃZ�b�g�����
		//[Fn( ... , args... )]�ƂȂ�
		template<class MT_Pointer_Class,convertible_from<MT_Pointer_Class> T_CName, class T_RType, class ...MT_Args, class ...MT_SetArgs>
		constexpr Function_Single(MT_Pointer_Class* set_p,
			T_RType(T_CName::* fn)(MT_Args...), MT_SetArgs ...args) :
			N_Function::IS_Function_Single_Operator<T_RType(T_CName::*)(MT_Args...), MT_SetArgs...>::Type(
				Function_Core<T_RType(T_CName::*)(MT_Args...)>(set_p, fn), args...) {}

		//�d�l
		//�֐��I�u�W�F�N�g���R�s�[���A�ǉ��ň������Z�b�g����
		//
		//����
		//fn::�֐��I�u�W�F�N�g
		//args...�ǉ��ŃZ�b�g�������
		template<class ...TP_Default_SetArgs, class ...MT_Args>
		constexpr Function_Single(Function_Single<TP_Default_SetArgs...> fn, MT_Args ...args) :
			N_Function::IS_Function_Single_Operator<Function_Single<TP_Default_SetArgs...>, MT_Args...>::Type(fn, args...) {}

		//�d�l
		//�֐��I�u�W�F�N�g���Q�Ƃ��A�ǉ��ň������Z�b�g����
		//
		//����
		//fn::�֐��I�u�W�F�N�g
		//args...�ǉ��ŃZ�b�g�������
		template<class ...TP_Default_SetArgs, class ...MT_Args>
		constexpr Function_Single(Function_Single<TP_Default_SetArgs...>* fn, MT_Args ...args) :
			N_Function::IS_Function_Single_Operator<Function_Single<TP_Default_SetArgs...>*, MT_Args...>::Type(fn, args...)
		{}

	};


	template<class T_RType, class ...MT_Args, class ...TP_SetArgs>
	Function_Single(T_RType(*fn)(MT_Args...), TP_SetArgs... setArgs) ->
		Function_Single<typename N_Function::IS_Function_Single_Helper<T_RType(*)(MT_Args...), TP_SetArgs...>::Judge
		, TP_SetArgs...>;


	template<class MT_Pointer_Class, convertible_from<MT_Pointer_Class> T_CName, class T_RType, class ...MT_Args, class ...TP_SetArgs>
	Function_Single(MT_Pointer_Class* set_p, T_RType(T_CName::* fn)(MT_Args...), TP_SetArgs... setArgs) ->
		Function_Single<typename N_Function::IS_Function_Single_Helper<T_RType(T_CName::*)(MT_Args...), TP_SetArgs...>::Judge
		, TP_SetArgs...>;

	template<class ...TP_Default_SetArgs, class ...TP_Args>
	Function_Single(Function_Single<TP_Default_SetArgs...> setFn, TP_Args... setArgs) -> Function_Single<typename N_Function::IS_Function_Single_Helper<Function_Single<TP_Default_SetArgs...>, TP_Args...>::Judge, TP_Args...>;

	template<class ...TP_Default_SetArgs, class ...TP_Args>
	Function_Single(Function_Single<TP_Default_SetArgs...>* setFn, TP_Args... setArgs) -> Function_Single<typename N_Function::IS_Function_Single_Helper<Function_Single<TP_Default_SetArgs...>*, TP_Args...>::Judge, TP_Args...>;


}