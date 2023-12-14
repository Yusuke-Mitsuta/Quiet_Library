#pragma once

#include"Function_Base_Data.h"
#include"Function_Request_Data.h"

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;


	template<class ...T_Parts>
	struct I_Function_Single_Data
	{
	protected:
		using base_data = I_Function_Base_Data<T_Parts...>::type;

	public:

		using type = I_Function_Base_Data<T_Parts...>::core;
			//typename N_Tuple::I_Expand_Set<Function_Core, T_Parts...>::type;

		using function = base_data::function;

		using pointer = base_data::pointer;

		using bind_args = base_data::bind_args;

		using request_args = I_Function_Request_Data<S_Request_args_Access,base_data>::type;

		using request_pointer = I_Function_Request_Data<S_Request_pointer_Access,base_data>::type;

		using request = Request_Core<request_args, request_pointer>;
	};

}
