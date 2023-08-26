#pragma once

#include"Function_Single_Helper.h"
#include"Function_Single_Operator.h"
#include"Concept.h"
#include"Function_Core.h"
#include"SwapType.h"

namespace N_Function
{

	//仕様
	//関数オブジェクトの単体を表す
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

		//仕様
		//一つの関数を持つ、関数オブジェクトを作成する
		//
		//引数
		//fn::関数ポインター
		//args...あらかじめセットする引数
		//
		//補足
		//[args...]は後ろ詰めでセットされる
		//[Fn( ... , args... )]となる
		template<class T_RType, class ...MT_Args, class ...MT_SetArgs>
		constexpr Function_Single(T_RType(*fn)(MT_Args...), MT_SetArgs ...args) :
			N_Function::IS_Function_Single_Operator<T_RType(*)(MT_Args...), MT_SetArgs...>::Type(
				Function_Core<T_RType(*)(MT_Args...)>(fn), args...) {}

		//仕様
		//一つの関数を持つ、関数オブジェクトを作成する
		//
		//引数
		//set_p::クラスのポインター
		//fn::関数ポインター
		//args...あらかじめセットする引数
		//
		//補足
		//[args...]は後ろ詰めでセットされる
		//[Fn( ... , args... )]となる
		template<class MT_Pointer_Class,convertible_from<MT_Pointer_Class> T_CName, class T_RType, class ...MT_Args, class ...MT_SetArgs>
		constexpr Function_Single(MT_Pointer_Class* set_p,
			T_RType(T_CName::* fn)(MT_Args...), MT_SetArgs ...args) :
			N_Function::IS_Function_Single_Operator<T_RType(T_CName::*)(MT_Args...), MT_SetArgs...>::Type(
				Function_Core<T_RType(T_CName::*)(MT_Args...)>(set_p, fn), args...) {}

		//仕様
		//関数オブジェクトをコピーし、追加で引数をセットする
		//
		//引数
		//fn::関数オブジェクト
		//args...追加でセットする引数
		template<class ...TP_Default_SetArgs, class ...MT_Args>
		constexpr Function_Single(Function_Single<TP_Default_SetArgs...> fn, MT_Args ...args) :
			N_Function::IS_Function_Single_Operator<Function_Single<TP_Default_SetArgs...>, MT_Args...>::Type(fn, args...) {}

		//仕様
		//関数オブジェクトを参照し、追加で引数をセットする
		//
		//引数
		//fn::関数オブジェクト
		//args...追加でセットする引数
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