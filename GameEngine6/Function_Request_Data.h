#pragma once

#include"Function_Request_Core.h"

#include"Function_Request_Args.h"
#include"Function_Request_pointer.h"

namespace N_Function
{

	template<class ...T_Parts>
	struct I_Function_Single_Data;

	//仕様
	//[T_Fn_Data]に対して、[TT_Access]で要求する要素を取得する
	//
	//補足
	//帰って来るデータは関数オブジェクト事に[tuple_t]で纏められている
	template<template<class...>class TT_Access, class T_Fn_Data>
	struct I_Function_Request_Data
	{

		template<class T_Request>
		struct S_Request
		{
			using type = TT_Access<T_Fn_Data,T_Request>::type;
		};

		template< class ...T_Request>
		struct S_Request< tuple_t<T_Request... >>
		{
			using type = tuple_t<typename S_Request<T_Request>::type...>;
		};

		//仕様
		//一つ上位の関数オブジェクトに対して、[::request]を取得する
		template<class T_Fn = typename T_Fn_Data::function>
		struct S_Function_Type
		{
			using type = int;
		};

		//仕様
		//一つ上位の関数オブジェクトが存在しない為、新たに定義する
		template<class T_CName, class T_RType, class ...T_Args>
		struct S_Function_Type<T_RType(T_CName::*)(T_Args...)>
		{
			using type = S_Request<Request_Core<typename tuple_t<T_Args...>::back,T_CName>>::type;
		};

		//仕様
		//一つ上位の関数オブジェクトが存在しない為、新たに定義する
		template< class T_RType, class ...T_Args>
		struct S_Function_Type<T_RType(*)(T_Args...)>
		{
			using type = S_Request<Request_Core<typename tuple_t<T_Args...>::back,invalid_t>>::type;
		};

		//仕様
		//一つ上位の関数オブジェクトに対して、[::request]を取得する
		template< class ...T_Parts>
		struct S_Function_Type<Function_Core<T_Parts...>>
		{
			using type = S_Request<typename I_Function_Single_Data<T_Parts...>::request>::type;
		};

		//仕様
		//[tuple_t]を外して、再度判定の実施する
		template< class T_Fn>
		struct S_Function_Type<tuple_t<T_Fn>>
		{
			using type = typename S_Function_Type<T_Fn>::type;
		};

		//仕様
		//[tuple_t]を外して、再度判定の実施し、その結果をtuple_tに纏める
		template< class ...T_Fns>
		struct S_Function_Type<tuple_t<T_Fns...>>
		{
			using type = tuple_t<typename S_Function_Type<T_Fns>::type...>;
		};

		using type = S_Function_Type<>::type;

	};


}