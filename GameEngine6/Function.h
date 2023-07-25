#pragma once
#include"Function_BindFn.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"MethodData.h"


struct H
{
	void Args_1(int a)
	{
		C_OUT(a);
	}

	void Args_2(int a, int b)
	{
		C_OUT(a);
		C_OUT(b);
	}

	void Args_3(int a, int b, int c)
	{
		Args_2(a, b);
		C_OUT(c);
	}

	void Args_4(int a, int b, int c, int d)
	{
		Args_3(a, b, c);
		C_OUT(d);

	}

	void Args_5(int a, int b, int c, int d, int e)
	{
		Args_4(a, b, c, d);
		C_OUT(e);
	}
};

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
	
	CName* classP = nullptr;
	Fn fn;
	BindArgs bindArgs;

	template<size_t ...N>
	constexpr RType Execution(auto args, std::index_sequence<N...>);

	template<class MT_Fn, class ...T_Args>
	constexpr Function(MT_Fn setFn, T_Args ...setArgs)
		:fn(setFn), bindArgs(IS_TupleUnzip(setArgs...)) {}

	template<class ...T_Args>
		requires tuple_convertible_to<typename IS_TupleUnzip<T_Args...,BindArgs>::Type, Args>&& same_as<std::true_type, typename MethodData::Root>
	constexpr auto operator()(T_Args... args)
	{
		return Execution(IS_TupleUnzip(args..., bindArgs), std::make_index_sequence<std::tuple_size_v<Args>>());
	}

	template<class ...T_Args>
		requires tuple_convertible_to<typename IS_TupleUnzip<T_Args...,BoundArgs>::Type, Args> && same_as<std::false_type,typename MethodData::Root>
	constexpr auto operator()(T_Args... args)
	{
		return fn.operator()(args..., bindArgs);
	}

};

template<class MT_Fn, class ...T_Args>
Function(MT_Fn setFn, T_Args... setArgs) -> Function<typename N_Function::IS_BindFn<MT_Fn,T_Args...>::Type::FnType,T_Args...>;

template<not_same_as<std::nullopt_t> T_Fn,class ...T_Args>
template<size_t ...N>
inline constexpr Function<T_Fn, T_Args...>::RType Function<T_Fn, T_Args...>::Execution(auto args, std::index_sequence<N...>)
{
	//return (classP->*fn)(std::get<N>((args.tuple))...);
}
