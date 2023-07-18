#pragma once
#include"Function_BindFn.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"


template<class T_Fn, class ...T_Args>
class Function
{
protected:
	constexpr Function() {}
public:

};

template<class T_Fn, class ...T_Args>
class Function<std::tuple<T_Fn, T_Args...>>:
	public Function<T_Fn, T_Args...>
{
public:

	using Args = std::tuple<T_Args...>;
	using Fn = T_Fn;
	T_Fn fn;
	std::tuple<T_Args...> args;

	template<class MT_Fn, class ...MT_Args>
	constexpr Function(MT_Fn setFn, MT_Args ...setArgs)
		:fn(setFn),args(IS_TupleUnzip(setArgs...)){}

	template<class MT_Fn, class ...MT_Args>
	constexpr Function(std::tuple<MT_Fn, MT_Args...> setFn){}

};

template<class ...T_Fn_Args, class ...T_NewArgs>
class Function<Function<T_Fn_Args...>,std::tuple<T_NewArgs...>>
{
public:
	
	using Args = IS_TupleUnzip< std::tuple<T_NewArgs...,typename Function<T_Fn_Args...>::Args>>::Type;

	using Fn = Function<T_Fn_Args...>::Fn;


	Function<T_Fn_Args...>& fn;
	std::tuple<T_NewArgs...> args;

	template<class ...MT_Fn_Args, class ...MT_NewArgs>
	constexpr Function(Function<MT_Fn_Args...>& setFn,MT_NewArgs... newSetArgs)
		:fn(setFn), args(IS_TupleUnzip(newSetArgs...)){}
};

template<class MT_Fn, class ...MT_Args>
	requires same_as<std::true_type, typename N_Function::IS_BindFn<MT_Fn, MT_Args...>::Judge>
Function(MT_Fn setFn, MT_Args... setArgs) -> Function<typename N_Function::IS_BindFn<MT_Fn,MT_Args...>::Type::FnType>;


template<class ...MT_Fn_Args, class ...MT_NewArgs>
Function(Function<MT_Fn_Args...>& setFn, MT_NewArgs... newSetArgs)
	-> Function<Function<MT_Fn_Args...> , typename IS_TupleUnzip<MT_NewArgs...>::Type>;