#pragma once
//
//#include"Function_Multiple_Helper.h"
//#include"Function_Multiple_Static_Operator.h"
//
//namespace N_Function
//{
//
//	template<auto ...t_Fns>
//		requires not_same_as<typename N_Function::IS_Function_Multiple_Helper<std::remove_const_t<decltype(t_Fns)>...>::Judge, std::nullopt_t>
//	class Function_Multiple_Static :
//		public N_Function::IS_Function_Multiple_Static_Operator<t_Fns...>::Type
//	{
//	};
//
//}