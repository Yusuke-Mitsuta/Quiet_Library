#pragma once

#include"Concept.h"
#include"Parameter.h"

namespace N_Function
{
	//仕様
	//クラスメソッドとメソッドを同一方法で扱う為のクラス

	template<class T_Fns,class ...TP_Bind_Args>
	struct Method_Core
	{
		T_Fns method;
		S_Parameter<TP_Bind_Args...> bind_Args;
		
		constexpr Method_Core(T_Fns set_Method, TP_Bind_Args... set_Bind_Args) :
			method(set_Method), bind_Args(set_Bind_Args...) {}

	};

	template<class T_Fns>
	struct Method_Core<T_Fns>
	{
		T_Fns method;

		constexpr Method_Core(T_Fns set_Method) :
			method(set_Method) {}

	};

}