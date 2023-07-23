#pragma once
#include"Function.h"
#include"tuple_Helper.h"
#include"MethodSearch.h"
#include"Function_Bind_Fns.h"

//仕様
//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
//
//テンプレート
//T_FlontFn,T_Fns...::関数ポインター、それに対する引数のTuple
//
//補足
//T_FlontFn,T_Fns...は関数ポインター、それに指定する引数、次の関数ポインター、となるようにする事
//関数ポインター、それに対する引数が不適正なら[T_FlontFn]が[std::nullopt_t]になる
template<not_same_as<std::nullopt_t> T_FlontFn, class ...T_Fns>
class FunctionMultiple
{
	T_FlontFn fns;

public:

	template<class ...MT_Fns>
	constexpr FunctionMultiple(MT_Fns... setFns)
		:fns(N_Function::IS_BindFns(setFns...)) {}
	
	template<class ...MT_Args>
		requires std::same_as <typename N_Function::IS_MethodSearch<T_FlontFn,MT_Args...>::Judge, std::true_type>
	constexpr auto operator()(MT_Args... args)
	{
		return std::get<N_Function::IS_MethodSearch<T_FlontFn,MT_Args...>::MethodNumber>(fns)(args...);
	}

};

template<class ...MT_Fns>
FunctionMultiple(MT_Fns... fns) -> FunctionMultiple<typename N_Function::IS_BindFns<MT_Fns...>::FnsType>;
