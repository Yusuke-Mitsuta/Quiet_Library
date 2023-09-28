#pragma once

#include"Tuple_Declare.h"
#include"Constexpr_String.h"

#define TUPLE_V_OPERATOR(select_operator) \
template<> \
struct S_Operator<#select_operator>\
{\
	using type = Tuple_t<integral_constant<value select_operator number >...>;\
}\

namespace N_Tuple
{
	template<class T_Tuple_v, N_Constexpr::String t_operator,auto number>
	struct I_Tuple_Calculate
	{
		template<class T_Tuple_v>
		struct S_Tuple_Calculate
		{
			using type = T_Tuple_v;
		};

		template<auto ...value>
		struct S_Tuple_Calculate<Tuple_t<integral_constant<value>...>>
		{
			template<N_Constexpr::String t_operator=t_operator>
			struct S_Operator
			{
				using type = T_Tuple_v;
			};

			TUPLE_V_OPERATOR(+);
			TUPLE_V_OPERATOR(-);
			TUPLE_V_OPERATOR(*);
			TUPLE_V_OPERATOR(/);

			using type = S_Operator<>::type;
		};

		using type = S_Action_Tuple_t<S_Tuple_Calculate,T_Tuple_v>::type;

	};




}
