#pragma once

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"SwapType.h"

template<not_same_as<std::nullopt_t> T_Fn, class ...T_Args>
class Function;

namespace N_Function
{
	template<class T_Fn,class ...T_Args>
	struct IS_FunctionHelper
	{

		using LappingFn = Function<T_Fn, T_Args...>;

		using Judge = IS_JudgeType_t<T_Fn,
			tuple_back_part_convertible_to<
			typename LappingFn::BoundArgs,
			typename LappingFn::Args>>;


		using Type = Judge;

	};

};

