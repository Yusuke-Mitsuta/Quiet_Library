#pragma once
#include"Function.h"
#include"tuple_Helper.h"
#include"FunctionMultiple_Helper.h"

//仕様
//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
//
//テンプレート
//T_Fns::tupleにラッピングされた複数の[Function]
//関数ポインター、それに対する引数が不適正なら[T_Fns]が[std::nullopt_t]になる
template<not_same_as<std::nullopt_t> T_FlontFn,class ...T_Fns>
class FunctionMultiple
{
	std::tuple<T_FlontFn,T_Fns...> fns;

public:

	//仕様
	//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
	//
	//引数
	//setFns::関数ポインターor[Function]、それに対する引数、次の関数と続く
	//
	//補足
	//関数に対して引数が正しくない場合T_Fnsが[std::nullopt_t]になり生成不可になる
	template<class MT_FlontFn,class ...MT_Fns>
	constexpr FunctionMultiple(MT_FlontFn setfn, MT_Fns... setFns)
		:fns(setfn,setFns...)
	{}
	
	//仕様
	//複数の[Function]から[T_Args...]で呼び出せる関数オブジェクトを実行する
	//
	//引数
	//args::入力する引数
	template<class ...T_Args>
		requires not_same_as<typename N_Function::IS_FunctionMultiple_Helper<std::tuple<T_Args...>,T_FlontFn,T_Fns...>::MethodSearch, std::nullopt_t>
	constexpr auto operator()(T_Args... args)
	{
		return N_Function::IS_FunctionMultiple_Helper<std::tuple<T_Args...>, T_FlontFn, T_Fns...>::MethodSearch::Execution(fns, args...);
	}

};

template<class MT_FlontFn, class ...MT_Fns>
FunctionMultiple(MT_FlontFn setfn, MT_Fns... setFns) -> FunctionMultiple
//<MT_FlontFn, MT_Fns...>;
<typename N_Function::IS_FunctionMultiple_Helper<std::tuple<>,MT_FlontFn, MT_Fns...>::SetJudge, MT_Fns...>;

