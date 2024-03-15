/*!
 * Function.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Function_Core.h"
#include"Function_Helper.h"
#include"Function_Operator.h"

namespace quiet
{
	//仕様
	//複雑の関数オブジェクトの管理、変数のバインドを行う
	template<is_invalid_not T_Front_Parts, class ...T_Parts>
	class Function
		:public quiet::N_Function::I_Function_Operator<T_Front_Parts, T_Parts...>::type
	{
	public:

		template<class MT_Front_Parts, class ...MT_Parts>
		constexpr Function(MT_Front_Parts && front_parts, MT_Parts&&... fn_Parts)
			:quiet::N_Function::I_Function_Operator<T_Front_Parts, T_Parts...>::type
			(std::forward<MT_Front_Parts>(front_parts),std::forward<MT_Parts>(fn_Parts)...)
		{}

		constexpr Function* operator->()
		{
			return this;
		}
		
		using quiet::N_Function::I_Function_Operator<T_Front_Parts,T_Parts...>::type::operator();

	};

	template<class T_Front_Parts, class ...T_Parts>
	Function(T_Front_Parts&&, T_Parts&&...) -> Function<
		typename quiet::N_Function::I_Function_Helper<T_Front_Parts, T_Parts...>::judge, T_Parts...>;

}
