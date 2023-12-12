#pragma once



#include"Parts.h"

namespace N_Function
{
	template<class T_Request_Args, class T_Request_Pointert>
	struct Request_Core;

	template<class ...T_Fn_Parts>
	struct I_Function_Single_Data;

	template<class ...T_Fn_Parts>
	struct I_Function_Multiple_Helper;

	//仕様
	//クラスメソッドとメソッドを同一方法で扱う為のクラス
	template<class ...T_Parts>
	struct Function_Core
	{
		using fn_t = I_Function_Single_Data<T_Parts...>::type;

		using function = fn_t::function;

		using pointer = fn_t::pointer;

		using bind_args = fn_t::bind_args;

		using request = I_Function_Single_Data<T_Parts...>::request;

		using request_args = request::request_args;

		using request_pointer = request::request_pointer;
	};

}
