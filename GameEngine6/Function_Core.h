#pragma once

#include"Method_Core.h"

namespace N_Function
{
	//仕様
	//クラスメソッドとメソッドを同一方法で扱う為のクラス
	template<class T_Method,class ...TP_Bind_Args>
	struct Function_Core :
		public Method_Core<T_Method, TP_Bind_Args...>
	{
		constexpr Function_Core(T_Method set_Methed, TP_Bind_Args... set_Args) :
			Method_Core<T_Method, TP_Bind_Args...>(set_Methed, set_Args...) {}


	};

	template<class T_CName, class T_RType, class ...TP_Args, class ...TP_Bind_Args>
	struct Function_Core<T_RType(T_CName::*)(TP_Args...),TP_Bind_Args...> :
		public Method_Core<T_RType(T_CName::*)(TP_Args...), TP_Bind_Args...>
	{
		T_CName* p;

		constexpr Function_Core(T_CName* set_p, T_RType(T_CName::* set_Methed)(TP_Args...), TP_Bind_Args... set_Args) :
			Method_Core<T_RType(T_CName::*)(TP_Args...), TP_Bind_Args...>(set_Methed,set_Args...), p(set_p) {}


	};



}