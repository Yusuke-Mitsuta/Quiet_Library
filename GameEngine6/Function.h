#pragma once
#include"Function_BindFn.h"
#include"Function_Bind_Args.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"


template<class T_Fn, class ...T_Args>
	//requires same_as<std::true_type,typename N_Function::IS_BindFn<T_Fn, T_Args...>::Type::Judge>
class Function
{
public:

	T_Fn fn;
	std::tuple<T_Args...> args;

	template<class T_Fn, class ...T_Args>
	constexpr Function(T_Fn setFn,T_Args& ...setArgs):
		fn(setFn),args(IS_TupleUnzip<T_Args...>::I_TupleUnzip(setArgs...))
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

	template<class T_Fn, class ...T_Args>
	constexpr Function(T_Fn setFn, T_Args& ...setArgs) :
		fn(setFn), args(IS_TupleUnzip<T_Args...>::I_TupleUnzip(setArgs...))
	{
		
	}

};


//N_Function::IS_BindFn<T_Fn, T_Args...>
template<class T_Fn, class ...T_Args>
Function(T_Fn fn, T_Args& ...setArgs) -> Function<typename N_Function::IS_BindFn<T_Fn,T_Args...>::Type::FnType>;
