#pragma once

#include"tuple_convertible_to.h"
#include"SwapType.h"

namespace N_Function
{
	template<class T_Method, class ...TP_Args>
	struct S_MethodData;
	
	template<typename T_Mtehod,class ...TP_Args>
	struct IS_Function_Single_Helper
	{

		using Lapping_Meth = S_MethodData<T_Mtehod, TP_Args...>;

		using Judge = U_Judge_t<T_Mtehod,
			tuple_back_part_convertible_to<
			typename Lapping_Meth::BoundArgs,
			typename Lapping_Meth::Args>>;

	};

};

