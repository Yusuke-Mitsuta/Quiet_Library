#pragma once

#include<optional>

namespace N_Function
{
	template<class T_Mtehod, class ...TP_Args>
	struct IS_Function_Single_Helper;

	template<class T_FlontFn, class ...T_Fn_Args>
	struct IS_Function_Multiple_Helper;

	template<class T_Method, class ...T_Args>
	struct S_MethodData;
}

class Function
{
public:

	template<not_same_as<std::nullopt_t> T_Method, class ...TP_Args>
	class Single;

	template<class T_Method, class ...TP_Args>
	Single(T_Method meth, TP_Args ...args) ->Single<typename N_Function::IS_Function_Single_Helper<T_Method, TP_Args...>::Judge, TP_Args...>;

	template<auto t_Method, auto ...tP_Args>
		requires not_same_as<typename N_Function::IS_Function_Single_Helper<std::remove_const_t<decltype(t_Method)>, decltype(tP_Args)...>::Judge, std::nullopt_t>
	class Single_Static;

	template<not_same_as<std::nullopt_t> T_FlontFn, class ...T_Fns>
	class Multiple;

	template<class MT_FlontFn, class ...MT_Fns>
	Multiple(MT_FlontFn setfn, MT_Fns... setFns) -> Multiple
		<typename N_Function::IS_Function_Multiple_Helper<MT_FlontFn, MT_Fns...>::Judge, MT_Fns...>;

	template<auto ...t_Fns>
		requires not_same_as<typename N_Function::IS_Function_Multiple_Helper<std::remove_const_t<decltype(t_Fns)>...>::Judge, std::nullopt_t>
	class Multiple_Static;

	template<class ...TP>
	static constexpr bool Check_Single = not_same_as<typename N_Function::IS_Function_Single_Helper<TP...>::Judge, std::nullopt_t>;

	template<class ...TP>
	static constexpr bool Check_Multiple = not_same_as<typename N_Function::IS_Function_Multiple_Helper<TP...>::Judge, std::nullopt_t>;

	//template<class ...TP_Fn>
	//	requires (Check_Single<TP_Fn...>) && (Check_Multiple<TP_Fn...>)
	//static constexpr auto Create(TP_Fn... fn);

	//template<class ...TP_Fns>
	//	requires (!(Check_Single<TP_Fns...>)) && (Check_Multiple<TP_Fns...>)
	//static constexpr auto Create(TP_Fns... fns);

	//template<class ...TP_Fn>
	//	requires (Check_Single<TP_Fn...>) && (Check_Multiple<TP_Fn...>)
	//static constexpr auto Create() {}

	//template<class ...TP_Fns>
	//	requires (!Check_Single<TP_Fns...>) && (Check_Multiple<TP_Fns...>)
	//static constexpr auto Create();

};

//template<class ...TP_Fn>
//	requires (Function::Check_Single<TP_Fn...>) && (Function::Check_Multiple<TP_Fn...>)
//constexpr auto Function::Create(TP_Fn ...fn)
//{
//	return Function::Single(fn...);
//}
//
//template<class ...TP_Fns>
//	requires (!(Function::Check_Single<TP_Fns...>)) && (Function::Check_Multiple<TP_Fns...>)
//static constexpr auto Create(TP_Fns... fns)
//{
//	return Function::Multiple(fns...);
//}

//template<class ...TP_Fn>
//	requires (Function::Check_Single<TP_Fn...>) && (Function::Check_Multiple<TP_Fn...>)
//constexpr auto Function::Create()
//{
//	return Function::Single_Static<TP_Fn...>();
//}
//
//template<class ...TP_Fns>
//	requires (!Function::Check_Single<TP_Fns...>) && (Function::Check_Multiple<TP_Fns...>)
//static constexpr auto Create()
//{
//	return Function::Multiple_Static<TP_Fns...>();
//}

