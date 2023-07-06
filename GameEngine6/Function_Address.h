#pragma once
#include<tuple>
#include<functional>
#include"Concept.h"



template<class C_Fn, class ...t_Set_Args>
struct Function_Address
{
	C_Fn fn;

	Function_Address(C_Fn setfn) :
		fn(setfn) {}
	Function_Address(C_Fn setfn, void* p) {}
	Function_Address(C_Fn setfn, void* p, t_Set_Args ...args) {}
};


template<class C_Name, class R_Type, class ...T_Args>
struct Function_Address<R_Type(C_Name::*)(T_Args...)>
{
protected:

	R_Type(C_Name::* fn)(T_Args...);

	C_Name* p;

public:

	constexpr Function_Address(R_Type(C_Name::* set_Fn)(T_Args...), C_Name* set_P) :
		fn(set_Fn), p(set_P) {}

	template<class ...Args>
		requires tuple_convertible_to<std::tuple<T_Args...>, std::tuple<Args...>>
	constexpr R_Type operator()(Args ...args)
	{
		std::function<R_Type()> method = std::bind(fn, p, args...);
		return method();
	}

};


template<class C_Name, class R_Type, class ...T_Args, class ...t_Set_Args>
struct Function_Address<R_Type(C_Name::*)(T_Args...),std::tuple<t_Set_Args...>>
{
private:

	R_Type(C_Name::* fn)(T_Args...);

	C_Name* p;

	std::tuple<t_Set_Args...> default_Args_Tuple;

public:


	constexpr Function_Address(R_Type(C_Name::* set_Fn)(T_Args...), C_Name* set_P, t_Set_Args ...args) :
		fn(set_Fn), p(set_P), default_Args_Tuple(args...) {}

	template<class ...Args>
		requires tuple_convertible_to<std::tuple<T_Args...>, std::tuple<t_Set_Args..., Args...>>
	constexpr R_Type operator()(Args ...args)
	{
		//Function_Execution<sizeof...(Set_Args) - 1>(args...);
	}

};
