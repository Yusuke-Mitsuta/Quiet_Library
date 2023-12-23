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
	template<class T_Request_pointer, class T_Fn_Data,
		class T_Pointer =typename T_Fn_Data ::pointer>
		struct S_Request_pointer
	{
		using type =
			U_Judge_t<T_Request_pointer,
			convertible_to_not<T_Pointer, T_Request_pointer>>;
	};


	template<class T_Request>
	struct S_Request_pointer_Access
	{
		using type = T_Request::request_pointer;
	};

}