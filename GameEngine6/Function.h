#pragma once
#include"Function_BindFn.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"MethodData.h"

template<not_same_as<std::nullopt_t> T_Fn,class ...T_Args>
class Function
{
protected:

	using MethodData = N_Function::S_MethodData<T_Fn, T_Args...>;

public:
	using BoundArgs = MethodData::BoundArgs;
	using BindArgs = MethodData::BindArgs;
	using CName = MethodData::CName;
	using RType = MethodData::RType;
	using Args = MethodData::Args;
	using Fn = MethodData::Fn;
	

	CName* classP;
	Fn fn;
	BindArgs bindArgs;

	template<size_t ...N>
	constexpr RType Execution(auto args, std::index_sequence<N...>);

	template<class MT_Fn, class ...MT_Args>
	constexpr Function(MT_Fn setFn, MT_Args ...setArgs)
		:fn(setFn), bindArgs(IS_TupleUnzip(setArgs...)) {}

	template<class MT_Fn, class ...MT_Args>
	constexpr Function(std::tuple<MT_Fn, MT_Args...> setFn)
		: fn(std::get<0>(setFn)), bindArgs(setFn) {}

	template<class ...MT_Args>
		requires tuple_convertible_to<typename IS_TupleUnzip<MT_Args...,BindArgs>::Type, Args>&& same_as<std::true_type, typename MethodData::Root>
	constexpr auto operator()(MT_Args... args)
	{
		return Execution(IS_TupleUnzip(args..., bindArgs), std::make_index_sequence<std::tuple_size_v<Args>>());
	}

	template<class ...MT_Args>
		requires tuple_convertible_to<typename IS_TupleUnzip<MT_Args...,BoundArgs>::Type, Args> && same_as<std::false_type,typename MethodData::Root>
	constexpr auto operator()(MT_Args... args)
	{
		return fn.operator()(args..., bindArgs);
	}

};

template<class MT_Fn, class ...MT_Args>
Function(MT_Fn setFn, MT_Args... setArgs) -> Function<typename N_Function::IS_BindFn<MT_Fn,MT_Args...>::Type::FnType>;

template<class MT_FunctionInner, class ...MT_NewArgs>
Function(Function<MT_FunctionInner> setFn, MT_NewArgs... newSetArgs)
	-> Function<typename IS_TupleUnzip<Function<MT_FunctionInner>,MT_NewArgs...>::Type>;


template<not_same_as<std::nullopt_t> T_Fn,class ...T_Args>
template<size_t ...N>
inline constexpr Function<T_Fn, T_Args...>::RType Function<T_Fn, T_Args...>::Execution(auto args, std::index_sequence<N...>)
{
	return (classP->*fn)(std::get<N>((args.tuple))...);
}
