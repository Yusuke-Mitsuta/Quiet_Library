/*!
 * Tuple_Template_Calculate.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"String.h"

#define TUPLE_V_OPERATOR(select_operator) \
template<> \
struct S_Operator<#select_operator>\
{\
	using type = tuple_t<integral_constant<value select_operator number >...>;\
}\

namespace quiet::N_Tuple
{
	//仕様
	//[Tuple_v< value...>]に対して[number]を["t_calculate_operator"]の演算子で計算する
	//
	//テンプレート
	//T_Calculate_Tuple::[number]に対して計算する[Tuple_v]
	//t_calculate_operator::[Tuple_v]と[number]の計算する演算子
	//number::[Tuple_v]の要素全てに対して計算する値
	//
	//補足
	//[t_calculate_operator]は["+"]["-"]["*"]["/"]で指定すること
	template<class T_Calculate_Tuple, String t_calculate_operator,auto number>
	struct I_Template_Calculate
	{

		template<class T_Tuple_v>
		struct S_Tuple_Calculate
		{
			using type = T_Tuple_v;
		};

		template<auto ...value>
		struct S_Tuple_Calculate<tuple_t<integral_constant<value>...>>
		{
			template<String t_operator>
			struct S_Operator
			{
				using type = T_Calculate_Tuple;
			};
		
			TUPLE_V_OPERATOR(+);
		
			TUPLE_V_OPERATOR(-);
		
			TUPLE_V_OPERATOR(*);
		
			TUPLE_V_OPERATOR(/);
		
			using type = S_Operator<t_calculate_operator>::type;
		};


	public:

		using type = I_Change_Tuple_t_Action<S_Tuple_Calculate, T_Calculate_Tuple>::type;

	};

}

#undef TUPLE_V_OPERATOR
