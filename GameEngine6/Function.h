#pragma once

#include"Function_Single.h"
#include"Function_Single_Static.h"
#include"Function_Multiple.h"
#include"Function_Multiple_Static.h"


#include"Concept.h"

class Function
{
public:

	template<not_same_as<std::nullopt_t> T_Method, class ...TP_Args>
	struct Single;

	template<class T_Method, class ...TP_Args>
	Single(T_Method meth, TP_Args ...args) -> Single<typename N_Function::IS_Function_Single_Helper<T_Method, TP_Args...>::Judge, TP_Args...>;

	template<auto t_Method, auto ...tP_Args>
		requires constructible_from<N_Function::Function_Single_Static<t_Method,tP_Args...>>
	struct Single_Static :
		public N_Function::Function_Single_Static<t_Method, tP_Args...> {};

	template<not_same_as<std::nullopt_t> T_FlontFn, class ...T_Fns>
	struct Multiple;

	template<class MT_FlontFn, class ...MT_Fns>
	Multiple(MT_FlontFn setfn, MT_Fns... setFns) -> Multiple
		<typename N_Function::IS_Function_Multiple_Helper<MT_FlontFn, MT_Fns...>::Judge, MT_Fns...>;

	template<auto ...t_Fns>
		requires constructible_from<N_Function::Function_Multiple_Static<t_Fns...>>
	struct Multiple_Static :
		public N_Function::Function_Multiple_Static<t_Fns...> {};

private:

	template<class ...TP>
	static constexpr bool Check_Single = not_same_as<typename N_Function::IS_Function_Single_Helper<TP...>::Judge, std::nullopt_t>;

	template<class ...TP>
	static constexpr bool Check_Multiple = not_same_as<typename N_Function::IS_Function_Multiple_Helper<TP...>::Judge, std::nullopt_t>;

public:
	template<class ...TP_Fn>
		requires (Check_Single<TP_Fn...>) && (Check_Multiple<TP_Fn...>)
	static constexpr auto Create(TP_Fn... fn);

	template<class ...TP_Fns>
		requires (!(Check_Single<TP_Fns...>)) && (Check_Multiple<TP_Fns...>)
	static constexpr auto Create(TP_Fns... fns);

	template<auto ...tP_Fn>
		requires (Check_Single<decltype(tP_Fn)...>) && (Check_Multiple<decltype(tP_Fn)...>)
	static constexpr auto Create();

	template<auto ...tP_Fns>
		requires (!Check_Single<decltype(tP_Fns)...>) && (Check_Multiple<decltype(tP_Fns)...>)
	static constexpr auto Create();

};

template<not_same_as<std::nullopt_t> T_Method, class ...TP_Args>
struct Function::Single :
	public N_Function::Function_Single<T_Method, TP_Args...>
{
	template<class T_Method, class ...TP_Args>
	Single(T_Method meth, TP_Args ...args) :
		N_Function::Function_Single<T_Method, TP_Args...>(meth, args...) {}
};

template<not_same_as<std::nullopt_t> T_FlontFn, class ...T_Fns>
struct Function::Multiple :
	public N_Function::Function_Multiple<T_FlontFn,T_Fns...>
{
	template<class MT_FlontFn, class ...MT_Fns>
	constexpr Multiple(MT_FlontFn flontFn, MT_Fns... fns) :
		N_Function::IS_Function_Multiple_Operator<MT_FlontFn, MT_Fns...>::Type(flontFn, fns...) {}
};


template<class ...TP_Fn>
	requires (Function::Check_Single<TP_Fn...>) && (Function::Check_Multiple<TP_Fn...>)
constexpr auto Function::Create(TP_Fn ...fn)
{
	return Function::Single(fn...);
}

template<class ...TP_Fns>
	requires (!(Function::Check_Single<TP_Fns...>)) && (Function::Check_Multiple<TP_Fns...>)
static constexpr auto Function::Create(TP_Fns... fns)
{
	return Function::Multiple(fns...);
}

template<auto ...tP_Fn>
	requires (Function::Check_Single<decltype(tP_Fn)...>) && (Function::Check_Multiple<decltype(tP_Fn)...>)
constexpr auto Function::Create()
{
	return Function::Single_Static<tP_Fn...>();
}

template<auto ...tP_Fns>
	requires (!Function::Check_Single<decltype(tP_Fns)...>) && (Function::Check_Multiple<decltype(tP_Fns)...>)
constexpr auto Function::Create()
{
	return Function::Multiple_Static<tP_Fns...>();
}

