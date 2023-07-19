#pragma once
#include"Function_BindFn.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"


template<class T_Fn, class ...T_Args>
class Function
{
protected:
	//constexpr Function() {}
public:
};

template<class T_CName, class T_RType, class ...T_Args, class ...T_SetArgs>
class Function<std::tuple<T_RType(T_CName::*)(T_Args...), T_SetArgs...>>:
	public Function<T_RType(T_CName::*)(T_Args...), T_SetArgs...>
{
public:

	T_CName* classP;

	using SetArgs = std::tuple<T_SetArgs...>;
	using Fn = T_RType(T_CName::*)(T_Args...);
	using Args = std::tuple<T_Args...>;

	Fn fn;
	std::tuple<T_SetArgs...> defaultSetArgs;

	template<class MT_Fn, class ...MT_Args>
	constexpr Function(MT_Fn setFn, MT_Args ...setArgs)
		:fn(setFn),defaultSetArgs(IS_TupleUnzip(setArgs...)){}

	template<class MT_Fn, class ...MT_Args>
	constexpr Function(std::tuple<MT_Fn, MT_Args...> setFn){}
	
	template<size_t ...N>
	constexpr T_RType Execution(auto args,std::index_sequence<N...>)
	{
		return (classP->*fn)(std::get<N>((args.tuple))...);
	}

	template<class ...MT_Args>
		requires tuple_convertible_to<typename IS_TupleUnzip<MT_Args..., T_SetArgs...>::Type, Args>
	constexpr auto operator()(MT_Args... args)
	{
		TYPE_ID(Args);
		using T = IS_TupleUnzip<MT_Args..., T_SetArgs...>::Type;
		TYPE_ID(T);
		return Execution(IS_TupleUnzip(args..., defaultSetArgs), std::make_index_sequence<sizeof...(T_Args)>());
	}
};

template<class T_FunctionInner, class ...T_NewArgs>
class Function<std::tuple<Function<T_FunctionInner>,T_NewArgs...>>
{
private:
	using ParentFn = Function<T_FunctionInner>;

public:
	

	using SetArgs = IS_TupleUnzip<std::tuple<T_NewArgs...,typename ParentFn::SetArgs>>::Type;
	using Fn = ParentFn::Fn;
	using Args = ParentFn::Args;


	ParentFn& fn;
	std::tuple<T_NewArgs...> defaultSetArgs;

	template<class MT_FunctionInner, class ...MT_NewArgs>
	constexpr Function(Function<MT_FunctionInner>& setFn,MT_NewArgs... newSetArgs)
		:fn(setFn), defaultSetArgs(IS_TupleUnzip(newSetArgs...)){}

	template<class ...MT_Args>
		requires tuple_convertible_to<typename IS_TupleUnzip<MT_Args..., SetArgs>::Type, Args>
	constexpr auto operator()(MT_Args... args)
	{
		return fn(args..., defaultSetArgs);
	}

};

template<class MT_Fn, class ...MT_Args>
	requires same_as<std::true_type, typename N_Function::IS_BindFn<MT_Fn, MT_Args...>::Judge>
Function(MT_Fn setFn, MT_Args... setArgs) -> Function<typename N_Function::IS_BindFn<MT_Fn,MT_Args...>::Type::FnType>;


template<class MT_FunctionInner, class ...MT_NewArgs>
Function(Function<MT_FunctionInner>& setFn, MT_NewArgs&&... newSetArgs)
	-> Function<typename IS_TupleUnzip<Function<MT_FunctionInner>,MT_NewArgs...>::Type>;