#pragma once

#include<tuple>
#include"Tuple_Unzip.h"
#include"Concept.h"

#include"I_Function.h"

namespace N_Function
{

	//仕様
	//先頭の関数に対して、戻り値、クラス、引数の型を返す。
	//関数以降の引数に対して、現在バインド済みの引数の型を返す
	template<class T_Method,class ...T_Args>
	struct S_MethodData {};

	template<class T_CName, class T_RType, class ...T_Args, class ...T_SetArgs >
	struct S_MethodData<T_RType(T_CName::*)(T_Args...), T_SetArgs...>
	{
		//仕様
		//関数の型
		using Fn =T_RType(T_CName::*)(T_Args...);

		//仕様
		//引数の型
		using BindArgs = std::tuple<T_SetArgs...>;

		//仕様
		//今までに指定済みの引数の型
		using BoundArgs = BindArgs;

		//仕様
		//関数が所属するクラスの型
		using CName = T_CName;

		//仕様
		//戻り値の型
		using RType = T_RType;

		//仕様
		//関数の引数に要求されている引数の型
		using Args = std::tuple<T_Args...>;

		//仕様
		//関数本体のデータかどうか
		using Root = std::true_type;
	};

	template<class ...T_FunctionInner, class ...T_SetArgs >
	struct S_MethodData<Function::Single<T_FunctionInner...>, T_SetArgs...>
	{
		//仕様
		//既に一部引数を指定済みの関数の型
		using Fn = Function::Single<T_FunctionInner...>;

		//仕様
		//[Method]のMethodDataにアクセスする
		using ParentFn = S_MethodData<T_FunctionInner...>;

		using BindArgs = std::tuple<T_SetArgs...>;

		//仕様
		//今までに指定済みの引数の型
		using BoundArgs = IS_TupleUnzip<BindArgs,typename ParentFn::BoundArgs>::Type;

		using CName = ParentFn::CName;
		using RType = ParentFn::RType;
		using Args = ParentFn::Args;
		using Root = std::false_type;
	};

	template<auto t_Function_v, auto ...t_FunctionArgs_v, class ...T_SetArgs >
	struct S_MethodData<Function::Single_Static<t_Function_v,t_FunctionArgs_v...>, T_SetArgs...>
	{

		//仕様
		//既に一部引数を指定済みの関数の型
		using Fn = Function::Single_Static<t_Function_v,t_FunctionArgs_v...>;

		//仕様
		//[Method]のMethodDataにアクセスする
		using ParentFn = S_MethodData<std::remove_const_t<decltype(t_Function_v)>,decltype(t_FunctionArgs_v)...>;

		using BindArgs = std::tuple<T_SetArgs...>;

		//仕様
		//今までに指定済みの引数の型
		using BoundArgs = IS_TupleUnzip<BindArgs, typename ParentFn::BoundArgs>::Type;

		using CName = ParentFn::CName;
		using RType = ParentFn::RType;
		using Args = ParentFn::Args;
		using Root = std::false_type;
	};

}