#pragma once

namespace N_Function
{
	//仕様
	//クラスメソッドとメソッドを同一方法で扱う為のクラス
	template<class T_Method>
	struct Function_Core;

	template<class T_RType, class ...TP_Args>
	struct Function_Core<T_RType(*)(TP_Args...)>
	{
		T_RType(*method)(TP_Args...);

		constexpr Function_Core(T_RType(*set_Methed)(TP_Args...)) :
			method(set_Methed) {}

		constexpr T_RType operator()(TP_Args... args)
		{
			return method(args...);
		}

		constexpr Function_Core* operator->()
		{
			return this;
		}
	};

	template<class T_CName, class T_RType, class ...TP_Args >
	struct Function_Core<T_RType(T_CName::*)(TP_Args...)>
	{
		T_CName* p;
		T_RType(T_CName::* method)(TP_Args...);

		constexpr Function_Core(T_CName* set_p, T_RType(T_CName::* set_Methed)(TP_Args...)) :
			p(set_p), method(set_Methed) {}

		constexpr T_RType operator()(TP_Args... args)
		{
			return (p->*method)(args...);
		}

		constexpr Function_Core* operator->()
		{
			return this;
		}
	};


}