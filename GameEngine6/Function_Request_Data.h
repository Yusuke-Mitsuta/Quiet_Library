#pragma once

#include"Function_Request._Core.h"

#include"Function_Request_Args.h"
#include"Function_Request_pointer.h"

namespace N_Function
{

	template<class ...T_Parts>
	struct I_Function_Single_Data;

	template<template<class...>class TT_Access, class T_Fn_Data>
	struct I_Function_Request_Data
	{

		template<  class T_Request>
		struct S_Request
		{
			using type = TT_Access<T_Fn_Data,T_Request>::type;
		};

		template< class ...T_Request>
		struct S_Request< tuple_t<T_Request... >>
		{
			using type = tuple_t<typename S_Request<T_Request>::type...>;
		};

		template< 
			class T_Fn = typename T_Fn_Data::function>
		struct S_Function_Type
		{
			using type = int;
		};

		template<  class T_CName, class T_RType, class ...T_Args>
		struct S_Function_Type<T_RType(T_CName::*)(T_Args...)>
		{
			using type = S_Request<Request_Core<typename tuple_t<T_Args...>::reverse,T_CName>>::type;
		};

		template< class T_RType, class ...T_Args>
		struct S_Function_Type< T_RType(*)(T_Args...)>
		{
			using type = S_Request<Request_Core<typename tuple_t<T_Args...>::reverse>>::type;
		};

		template< class ...T_Parts>
		struct S_Function_Type< Function_Core<T_Parts...>>
		{
			using type = S_Request<typename I_Function_Single_Data<T_Parts...>::request>::type;
		};


		template< class T_Fn>
		struct S_Function_Type<tuple_t<T_Fn>>
		{
			using type = typename S_Function_Type<T_Fn>::type;
		};

		template< class ...T_Fns>
		struct S_Function_Type<tuple_t<T_Fns...>>
		{
			using type = tuple_t<typename S_Function_Type< T_Fns>::type...>;
		};

		using type = S_Function_Type<>::type;

	};



}
