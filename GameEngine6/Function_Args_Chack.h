#pragma once

#include"Tuple.h"
#include"Expand.h"

namespace N_Function
{

	template<class T_Request_Args, class T_Bind_Args>
	struct I_Function_Args_Chack
	{
		using type = invalid_t;
	};
	
	//仕様
	//[T_Request_Args]と[T_Bind_Args]を後ろから比較し、
	//　互換性のある型か判定する。
	//
	// テンプレート
	// [T_Request_Args]：要求する引数の型(tuple_tp)
	// [T_Bind_Args]：セットする引数の型(tuple_t)
	// 
	//補足
	// 互換性のある型の定義は、[N_Tuple::S_Parameter]の特殊化にて定義を行う
	//
	template<class T_Request_Args, class T_Bind_Args>
		requires requires
	{
		requires N_Tuple::is_Tuple_t<T_Request_Args>;
		requires N_Tuple::is_Tuple_t<T_Bind_Args>;
	}
	struct I_Function_Args_Chack<T_Request_Args,T_Bind_Args>
	{
	public:

		using type = N_Tuple::N_Apply::I_Apply_Type_Chack<T_Request_Args, T_Bind_Args>::type::request;

	};

}
