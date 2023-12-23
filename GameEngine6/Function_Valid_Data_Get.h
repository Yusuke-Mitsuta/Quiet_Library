#pragma once

#include"Tuple.h"

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	template<class ...T_Parts>
	struct I_Function_Superficial_Data;

	//仕様
	//[T_Parts...]から、各種データを生成する
	template<class ...T_Parts>
	struct I_Function_Valid_Data_Get
	{
	protected:

		using superficial = I_Function_Superficial_Data<T_Parts...>;

		template<class T_Fns=superficial::function,
		class T_Request_Args=superficial::request_args>
		struct S_Valid_Data_Get
		{

		};

		template<class T_Fns, class T_Request_Args>
			requires requires
		{
			requires N_Tuple::is_Tuple_t<T_Fns>;
			requires T_Request_Args::size > 0;
		}
		struct S_Valid_Data_Get<T_Fns,T_Request_Args>
		{

		};


	};

}
