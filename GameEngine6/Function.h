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

	//template<class MT_Fn, class ...MT_Args>
	///constexpr Function(MT_Fn setFn, MT_Args... setArgs) {}

	//template<class MT_Fn, class ...MT_Args>
	//constexpr Function(std::tuple<MT_Fn,MT_Args...> setFn) {}
};

template<class T_Fn, class ...T_Args>
class Function<std::tuple<T_Fn, T_Args...>> :
	public Function<T_Fn, T_Args...>
{
public:

	T_Fn fn;
	std::tuple<T_Args...> args;

	template<class MT_Fn, class ...MT_Args>
	constexpr Function(MT_Fn setFn, MT_Args ...setArgs)
		:fn(setFn),args(IS_TupleUnzip(setArgs...)){}

	template<class MT_Fn, class ...MT_Args>
	constexpr Function(std::tuple<MT_Fn, MT_Args...> setFn){}

};

template<class MT_Fn, class ...MT_Args>
	requires same_as<std::true_type, typename N_Function::IS_BindFn<MT_Fn, MT_Args...>::Judge>
Function(MT_Fn setFn, MT_Args... setArgs) -> Function<typename N_Function::IS_BindFn<MT_Fn,MT_Args...>::Type::FnType>;