#pragma once

#include"Function_Superficial_Data.h"

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

		using superficial = I_Function_Superficial_Data<T_Parts...>;

	public:

		//using type = 


	};

}
