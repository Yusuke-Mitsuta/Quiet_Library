#pragma once

#include"Concept.h"

namespace N_Function
{

	//仕様
	//要求するポインターの型を[T_Fn_Data]から取得し、
	// 互換性のあるポインターがセットされて入れば要求を取り消す
	//
	//補足
	//関数が纏められている場合、[tuple_t]で纏める
	//必要でない場合、[invalid_t]が返る
	template<class T_Request_pointer, class T_Pointer,
		bool t_judge = convertible_to<T_Pointer, T_Request_pointer>>
		struct S_Request_pointer
	{
		using type = T_Request_pointer;
	};

	template<class T_Request_pointer, class T_Pointer>
	struct S_Request_pointer<T_Request_pointer, T_Pointer, 1>
	{
		using type = invalid_t;
	};


	template<class T_Fn_Data, class T_Request>
	struct S_Request_pointer_Access
	{
		using request = T_Request::request_pointer;

		using type =
			typename S_Request_pointer<request,
			typename T_Fn_Data::pointer>::type;
	};

}