#pragma once

namespace N_Function
{
	template<class ...T_Fn_Parts>
	struct Function_Core;

	//仕様
	//クラスメソッドとメソッドを同一方法で扱う為のクラス
	template<class ...T_Parts>
	struct I_Function_Core_Helper
	{

		template<class T_Result = Function_Core<>, class ...T_Parts>
		struct S_Function_Core_Helper;

		template<class T_pointer, class T_Fn, class T_Args>
		struct S_Function_Core_Helper<T_pointer, T_Fn, T_Args>
		{

		};


		using function = type::function;
		using request_args = type::request_args;
		using bind_args = type::bind_args;

		using c_name = type::c_name;

		static constexpr size_t fn_count = type::fn_count;

	};


}
