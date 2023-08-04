#pragma once

#include"FunctionMultipleOperator.h"
#include"FunctionMultiple_Static.h"

//仕様
//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
//
//テンプレート
//関数ポインター、それに対する引数が不適正なら[T_FlontFn]が[std::nullopt_t]になる
template<not_same_as<std::nullopt_t> T_FlontFn,class ...T_Fns>
class FunctionMultiple : 
	public N_Function::IS_FunctionMultipleOperator<T_FlontFn, T_Fns...>::Type
{

public:

	using N_Function::IS_FunctionMultipleOperator<T_FlontFn, T_Fns...>::Type::operator();

	//仕様
	//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
	//
	//引数
	//fns::関数ポインターor[Function]、それに対する引数、次の関数と続く
	//
	//補足
	//関数に対して引数が正しくない場合T_Fnsが[std::nullopt_t]になり生成不可になる
	template<class MT_FlontFn,class ...MT_Fns>
	constexpr FunctionMultiple(MT_FlontFn flontFn, MT_Fns... fns):
		N_Function::IS_FunctionMultipleOperator<MT_FlontFn, MT_Fns...>::Type(flontFn,fns...){}

};

template<class MT_FlontFn, class ...MT_Fns>
FunctionMultiple(MT_FlontFn setfn, MT_Fns... setFns) -> FunctionMultiple
<typename N_Function::IS_FunctionMultiple_Helper<MT_FlontFn, MT_Fns...>::Judge, MT_Fns...>;

