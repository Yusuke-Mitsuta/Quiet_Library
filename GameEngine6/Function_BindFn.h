#pragma once

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"


template<not_same_as<std::nullopt_t> T_Fn, class ...T_Args>
class Function;

namespace N_Function
{
	template<class ...T_Args>
	struct IS_FunctionHelper
	{
		template<class ...T_Args>
		struct S_CorrectType
		{
			using Type = S_CorrectType;
			using FnType = std::nullopt_t;
			using Judge = std::false_type;
		};

		template<class T_Fn,class ...T_Args>
		struct S_CorrectType<std::tuple<T_Fn,T_Args...>>
		{
			using Type = S_CorrectType<T_Fn,T_Args...>::Type;
		};

		template<class T_CName, class T_RType, class ...T_Args, class ...T_SetArgs>
			requires tuple_back_part_convertible_to<std::tuple<T_SetArgs...>, std::tuple<T_Args...>>
		struct S_CorrectType<T_RType(T_CName::*)(T_Args...), T_SetArgs...>
		{
			using Type = S_CorrectType;
			using FnType = T_RType(T_CName::*)(T_Args...);
			using Judge = std::true_type;
		};

		template<class ...T_FunctionInner,class ...T_SetArgs>
			requires tuple_back_part_convertible_to<
				typename IS_TupleUnzip<T_SetArgs...,typename Function<T_FunctionInner...>::BoundArgs>::Type,
					typename Function<T_FunctionInner...>::Args>
		struct S_CorrectType<Function<T_FunctionInner...>,T_SetArgs...>
		{
			using Type = S_CorrectType;
			using FnType = Function<T_FunctionInner...>;
			using Judge = std::true_type;

		};

		using Type = S_CorrectType<typename IS_TupleUnzip<T_Args...>::Type>::Type;

		using FnType = Type::FnType;
		using Judge = Type::Judge;

	};

};

