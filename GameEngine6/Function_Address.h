#pragma once
#include<tuple>
#include<functional>
#include"Concept.h"

namespace N_Function
{
	template<class C_Fn, class ...T_SetArgs>
	struct S_Address
	{
		C_Fn fn;

		S_Address(C_Fn setfn) :
			fn(setfn) {}
		S_Address(C_Fn setfn, void* p) {}
		S_Address(C_Fn setfn, void* p, T_SetArgs ...args) {}
	};


	template<class C_Name, class R_Type, class ...T_Args>
	struct S_Address<R_Type(C_Name::*)(T_Args...)>
	{
	protected:

		R_Type(C_Name::* fn)(T_Args...);

		C_Name* p;

	public:

		constexpr S_Address(R_Type(C_Name::* set_Fn)(T_Args...), C_Name* set_P) :
			fn(set_Fn), p(set_P) {}

		template<class ...Args>
			requires tuple_convertible_to<std::tuple<T_Args...>, std::tuple<Args...>>
		constexpr R_Type operator()(Args ...args)
		{
			std::function<R_Type()> method = std::bind(fn, p, args...);
			return method();
		}

	};


	template<class C_Name, class R_Type, class ...T_Args, class ...T_SetArgs>
	struct S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_SetArgs...>>
	{
	private:

		R_Type(C_Name::* fn)(T_Args...);

		C_Name* p;

		std::tuple<T_SetArgs...> default_Args_Tuple;

	public:

		constexpr S_Address(R_Type(C_Name::* set_Fn)(T_Args...), C_Name* set_P, T_SetArgs ...args) :
			fn(set_Fn), p(set_P), default_Args_Tuple(args...) {}

		template<class ...Args>
			requires tuple_convertible_to<std::tuple<T_Args...>, std::tuple<T_SetArgs..., Args...>>
		constexpr R_Type operator()(Args ...args)
		{
			//Function_Execution<sizeof...(Set_Args) - 1>(args...);
		}

	};



}