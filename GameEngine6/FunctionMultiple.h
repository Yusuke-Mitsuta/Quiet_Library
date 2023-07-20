#pragma once
#include"FunctionMultiple.h"
#include"Function.h"
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
template<class T_FlontFn, class ...T_Fns>
	requires not_same_as<T_FlontFn, std::nullopt_t>
class FunctionMultiple
{
public:

	std::tuple<T_FlontFn, T_Fns...> fns;

	template<class ...MT_Fns>
	constexpr FunctionMultiple(MT_Fns... setFns)
		:fns(N_Function::IS_BindFns(setFns...)) {}
	

};

template<class ...MT_Fns>
FunctionMultiple(MT_Fns... fns) -> FunctionMultiple<typename N_Function::IS_BindFns<MT_Fns...>::FnsType>;
