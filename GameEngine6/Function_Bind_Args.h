#pragma once
#include"Function_Address.h"
#include<optional>

namespace N_Function
{
	template<class ...T_Fn_Args>
	struct S_BindArgs{};

	template<class C_Name, class R_Type, class ...T_Args, class ...T_Fn_Args>
	struct S_BindArgs<R_Type(C_Name::*)(T_Args...), T_Fn_Args...>
	{
		using Type = S_BindArgs<S_Address
			<R_Type(C_Name::*)(T_Args...), std::tuple<>>,T_Fn_Args...>::Type;
	};

	template<class ...T_Zip_Fn_Args,class ...T_Fn_Args>
	struct S_BindArgs<std::tuple<T_Zip_Fn_Args...>,T_Fn_Args...>
	{
		using Type = S_BindArgs<T_Zip_Fn_Args...,T_Fn_Args...>::Type;
	};

	template< class C_Name, class R_Type, class ...T_Args, class ...T_DefaultSetArgs, class ...T_Fn_Args>
	struct S_BindArgs<S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_DefaultSetArgs...>>,T_Fn_Args...>
	{
		using T_Method = R_Type(C_Name::*)(T_Args...);

		template<class Args, class ...T_Fn_Args>
		struct S_BindArgsExecution{};

		template<class ...T_NewDefaultSetArgs,class ...T_Fn_Args>
			requires tuple_back_part_convertible_to<std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>
		struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>,std::nullopt_t ,T_Fn_Args...>
		{
			using Type = S_BindArgsExecution;
			using Judge = std::true_type;
			using Tuple = std::tuple<T_Fn_Args..., S_Address<T_Method, std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>>>;
		};

		template<class ...T_NewDefaultSetArgs, class ...T_Fn_Args>
		struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, std::nullopt_t, T_Fn_Args...>
		{
			using Type = S_BindArgsExecution;
			using Judge = std::false_type;
			using Tuple = std::tuple<>;
		};

		template<class ...T_NewDefaultSetArgs, class T_SetArgs, class ...T_Fn_Args>
		struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, T_SetArgs, T_Fn_Args...>
		{
			using Type= S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...,T_SetArgs>,T_Fn_Args...>::Type;
		};

		template<class ...T_NewDefaultSetArgs , class C_Name, class R_Type, class ...T_Args, class ...T_Fn_Args>
		struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, R_Type(C_Name::*)(T_Args...), T_Fn_Args...>
		{
			using Type = S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>,
				S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<>>, T_Fn_Args...>::Type;
		};

		template<class ...T_NewDefaultSetArgs, class ...T_Flont_Fn, class ...T_Fn_Args>
			requires tuple_back_part_convertible_to<std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>
		struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>,S_Address<T_Flont_Fn...>, T_Fn_Args...>
		{
			using Type = S_BindArgs<S_Address<T_Flont_Fn...>,T_Fn_Args...,
				S_Address<T_Method, std::tuple<T_NewDefaultSetArgs..., T_DefaultSetArgs...>>>::Type;
		};

		template<class ...T_NewDefaultSetArgs, class ...T_Flont_Fn, class ...T_Fn_Args>
		struct S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, S_Address<T_Flont_Fn...>, T_Fn_Args...>
		{
			using Type = S_BindArgsExecution<std::tuple<T_NewDefaultSetArgs...>, std::nullopt_t>::Type;
		};

		using Type = S_BindArgsExecution<std::tuple<>,T_Fn_Args...>::Type;
	};

	template<class ...T_Fn_Args>
	struct I_S_BindArgs 
	{
		using Type = S_BindArgs<T_Fn_Args..., std::nullopt_t>::Type;
		using TupleType = Type::Tuple;
		using Judge = Type::Judge;

	};

}
