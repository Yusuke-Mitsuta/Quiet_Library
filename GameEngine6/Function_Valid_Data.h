#pragma once

#include"Function_Superficial_Data.h"
#include"Function_Valid_Data_Get.h"

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	//仕様
	//[T_Parts...]から、各種データを生成する
	template<class ...T_Parts>
	struct I_Function_Valid_Data

	{
	protected:


		using valid_data = I_Function_Valid_Data_Get<T_Parts...>::type;

	public:

		using superficial = I_Function_Superficial_Data<T_Parts...>;
		using type = 
			//valid_data::function;
			I_Function_Base_Data<T_Parts...>::core;

		using function = valid_data::function;

		using pointer = superficial::pointer;

		using bind_args = superficial::bind_args;

		using request_args = valid_data::request_args;

		using request_pointer = valid_data::request_pointer;

		using request = Request_Core<request_args, request_pointer>;
	};

}
