/*!
 * Function_Core.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Function_Valid_Data.h"

namespace quiet::N_Function
{
	//仕様
	//クラスメソッドとメソッドを同一方法で扱う為のクラス
	template<class ...T_Parts>
	struct Function_Core :
		I_Function_Valid_Data<T_Parts...>
	{


	};

}
