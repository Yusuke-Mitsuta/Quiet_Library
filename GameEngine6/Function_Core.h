#pragma once

#include"Method_Core.h"

namespace N_Function
{
	//仕様
	//クラスメソッドとメソッドを同一方法で扱う為のクラス
	template<class T_Fn,class ...TP_Bind_Args>
	struct Function_Core 
	{
		constexpr Function_Core(T_Fn set_Methed, TP_Bind_Args... set_Args) {}

		constexpr Function_Core(void* set_p, T_Fn set_Methed, TP_Bind_Args... set_Args) {}

	};



}
