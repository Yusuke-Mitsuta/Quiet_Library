#pragma once

#include"Tuple.h"

namespace N_Function
{

	template<class T_Fns, class ...TP_Bind_Args>
	struct Function_Core;

	template<class T_Fns, class ...TP_Bind_Args>
	struct I_Function_Core_Operator
	{


		template<class ...T_Fns>
		struct S_Function_Core_Operator
		{

		};

		template<class T_Flont_Fn,class ...T_Fns>
		struct S_Function_Core_Operator<T_Flont_Fn,T_Fns...> :
			S_Function_Core_Operator<T_Fns...>
		{

			//constexpr S_Function_Core_Operator(T_Flont_Fn fn) {}

		};

		template<class ...T_Fns>
		struct S_Function_Core_Operator<tuple_t<T_Fns...>> :
			S_Function_Core_Operator<T_Fns...> {};

	};


}