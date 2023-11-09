#pragma once

#include"Concept.h"

namespace N_Function
{
	template<class T_Fn, class ...TP_Bind_Args>
	struct Function_Core;

	template<class ...T_Fn_Parts>
	struct I_Function_Single_Data;

	template<class T_Fns>
	struct I_Function_Operator;

	template<class T_Commond_p,class T_Dedicated_p, class T_Fn, class ...T_Bind_Args>
	struct I_Function_Operator_Core
	{
		template<class T_Fn, class ...T_Bind_Args>
		struct S_Function_Operator_Core
		{
			T_Dedicated_p* dedicated_p;
			T_Fn fn;
			std::tuple<T_Bind_Args...> bind_args;
		};
		
		template<class T_Fn, class ...T_Bind_Args>
			requires requires
		{
			requires (I_Function_Single_Data<Function_Core<T_Fn>>::fn_count == 1);
			requires (is_invalid<typename I_Function_Single_Data<Function_Core<T_Fn>>::c_name>);
		}
		struct S_Function_Operator_Core
		{
			T_Fn fn;
			std::tuple<T_Bind_Args...> bind_args;
		};

		using type = S_Function_Operator_Core<T_Fn,T_Bind_Args...>;
	};
}

