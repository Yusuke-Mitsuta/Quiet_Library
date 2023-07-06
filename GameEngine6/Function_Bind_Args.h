#pragma once
#include"Function_Address.h"
#include<optional>

namespace N_Function
{
	template<class ...T_Fn_Args>
	struct S_BindArgs{};

	template<class ...T_Fn_Args>
	struct S_BindArgs<std::nullopt_t, T_Fn_Args...>
	{
		template<class T_Method, class ...T_DefaultSetArgs>
		using Type = std::tuple<T_Fn_Args..., S_Address<T_Method, std::tuple<T_DefaultSetArgs...>>>;
	};

	template<class Args, class ...T_Fn_Args>
	struct S_BindArgs<Args,T_Fn_Args...>
	{
		template<class T_Method, class ...T_DefaultSetArgs>
		using Type = S_BindArgs<T_Fn_Args...>::Type<T_Method, std::tuple<T_DefaultSetArgs...,Args>>;
	};

	template<class C_Name, class R_Type, class ...T_Args, class ...T_Fn_Args>
	struct S_BindArgs<R_Type(C_Name::*)(T_Args...), T_Fn_Args...>
	{
		using Start= S_BindArgs<T_Fn_Args...>::Type<S_Address<R_Type(C_Name::*)(T_Args...)>>;

		template<class T_Method, class ...T_DefaultSetArgs>
		using Type = S_BindArgs<T_Fn_Args..., S_Address<T_Method,std::tuple<T_DefaultSetArgs...>>>::Type<S_Address<R_Type(C_Name::*)(T_Args...)>>;
	
	};

	template<class C_Name, class R_Type, class ...T_Args, class ...T_DefaultSetArgs, class ...T_Fn_Args>
	struct S_BindArgs<S_Address<R_Type(C_Name::*)(T_Args...),std::tuple<T_DefaultSetArgs...>>, T_Fn_Args...>
	{
		using Start = S_BindArgs<T_Fn_Args...>::Type<S_Address<R_Type(C_Name::*)(T_Args...)>>;

		template<class T_Method, class ...T_DefaultSetArgs>
		using Type = S_BindArgs<T_Fn_Args..., S_Address<T_Method, std::tuple<T_DefaultSetArgs...>>>::Type<S_Address<R_Type(C_Name::*)(T_Args...), T_DefaultSetArgs...>>;
	};


	template<class ...T_Fn_Args>
	struct I_S_BindArgs 
	{
		using Type = S_BindArgs<T_Fn_Args..., std::nullopt_t>::Start;
	};

	template<class ...T_Fn_Args>
	struct I_S_BindArgs<std::tuple<T_Fn_Args...>>
	{
		using Type = S_BindArgs<T_Fn_Args..., std::nullopt_t>::Start;
	
	};

}
