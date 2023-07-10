#pragma once
#include"Function_BindFn.h"
#include"Function_Bind_Args.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"


template<class T_Fn, class ...T_Args>
	requires same_as<std::true_type,typename N_Function::IS_BindFn<T_Fn, T_Args...>::Type::Judge>
class Function
{
public:

	T_Fn fn;
	std::tuple<T_Args...> args;

	template<class MT_Fn, class ...MT_Args>
	constexpr Function(MT_Fn setFn,MT_Args... setArgs)
		:fn(setFn),args(IS_TupleUnzip<MT_Args...>::I_TupleUnzip(setArgs...))
	{
	}

	template<class ...Args>
		//requires tuple_convertible_to<std::tuple<T_Args...>, std::tuple<t_Set_Args..., Args...>>
	constexpr void operator()(Args ...args)
	{
		std::apply();
		//Function_Execution<sizeof...(t_Set_Args) - 1>(args...);
	}

};


template<class T_Fn, class ...T_Args>
class Function<std::tuple<T_Fn,T_Args...>>
{
public:

	T_Fn fn;
	std::tuple<T_Args...> args;

	template<class MT_Fn, class ...MT_Args>
	constexpr Function(MT_Fn setFn, MT_Args ...setArgs) 
		: fn(setFn), args(IS_TupleUnzip<MT_Args...>::I_TupleUnzip(setArgs...))
	{
		//type_id(IS_TupleUnzip<MT_Args...>::I_TupleUnzip(std::forward<MT_Args>(setArgs)...))
	}

};

template<class MT_Fn, class ...MT_Args>
Function(MT_Fn setFn, MT_Args... setArgs) -> Function<typename N_Function::IS_BindFn<MT_Fn, MT_Args...>::Type::FnType>;