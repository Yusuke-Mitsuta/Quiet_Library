#pragma once
#include"Function_Address.h"
#include"Function_Bind_Args.h"
#include"Using_Type.h"

#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"

template<class T, class ...T_Fns>
class Function
{
	T* p;

	std::tuple<T_Fns...> fns;

public:

	template<class T,class ...T_Fns>
	constexpr Function(T* set_p,T_Fns ...setFns):
		p(set_p)
	{
	}


	template<class ...Args>
		//requires tuple_convertible_to<std::tuple<T_Args...>, std::tuple<t_Set_Args..., Args...>>
	constexpr void operator()(Args ...args)
	{
		std::apply();
		//Function_Execution<sizeof...(t_Set_Args) - 1>(args...);
	}

	//// C++17
	//template<class F, class Tuple, size_t... I>
	//constexpr decltype(auto) apply - impl(F && f, Tuple && t, std::index_sequence<I...>) {
	//	return std::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
	//}

};

template<class T, class ...T_FnsDataBase>
Function(T* set_p,T_FnsDataBase ...set_Fns) -> Function<T, typename N_Function::IS_BindArgs<typename I_S_TupleUnzip<T_FnsDataBase...>::Type>::Type>;
