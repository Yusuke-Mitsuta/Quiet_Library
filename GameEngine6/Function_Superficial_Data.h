#pragma once

#include"Function_Base_Data.h"
#include"Function_Request_Data.h"

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	//仕様
	//[T_Parts...]から、各種データを生成する
	template<class ...T_Parts>
	struct I_Function_Superficial_Data
	{
	protected:

		using base_data = I_Function_Base_Data<T_Parts...>::type;

	public:

		using type = I_Function_Base_Data<T_Parts...>::core;

		using function = base_data::function;

		using pointer = base_data::pointer;

		using bind_args = base_data::bind_args; 

		using request_args = I_Function_Request_Data<S_Request_args_Access,
			S_Request_args,base_data>::type;

		using request_pointer = I_Function_Request_Data<S_Request_pointer_Access,S_Request_pointer,base_data>::type;

		using request = Request_Core<request_args, request_pointer>;
	};


	template<class ...T_Parts>
	struct I_Function_Single_Data :
		I_Function_Superficial_Data<T_Parts...> 
	{};
}
