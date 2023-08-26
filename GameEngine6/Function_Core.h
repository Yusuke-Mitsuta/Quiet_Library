#pragma once

namespace N_Function
{
	//仕様
	//クラスメソッドとメソッドを同一方法で扱う為のクラス
	template<class T_Method, class ...T_Args>
	struct Function_Core;


	template<class T_RType, class ...T_Args>
	struct Function_Core<T_RType(*)(T_Args...)>
	{
		T_RType(*method)(T_Args...);

		constexpr Function_Core(T_RType(*set_Methed)(T_Args...)) :
			method(set_Methed) {}

		constexpr T_RType operator()(T_Args... args)
		{
			return method(args...);
		}

		constexpr Function_Core* operator->()
		{
			return this;
		}
	};

	template<class T_CName, class T_RType, class ...T_Args>
	struct Function_Core<T_RType(T_CName::*)(T_Args...)>
	{
		T_CName* p;
		T_RType(T_CName::* method)(T_Args...);

		constexpr Function_Core(T_CName* set_p, T_RType(T_CName::* set_Methed)(T_Args...)) :
			p(set_p), method(set_Methed) {}

		constexpr T_RType operator()(T_Args... args)
		{
			return (p->*method)(args...);
		}

		constexpr Function_Core* operator->()
		{
			return this;
		}
	};
}