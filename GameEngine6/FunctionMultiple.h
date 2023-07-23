#pragma once
#include"Function.h"
#include"tuple_Helper.h"
#include"MethodSearch.h"
#include"Function_Bind_Fns.h"

//仕様
//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
//
//テンプレート
//T_Fns::tupleにラッピングされた複数の[Function]
//関数ポインター、それに対する引数が不適正なら[T_Fns]が[std::nullopt_t]になる
template<not_same_as<std::nullopt_t> T_Fns>
class FunctionMultiple
{
	T_Fns fns;

public:
	//仕様
	//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
	//
	//引数
	//setFns::関数ポインターor[Function]、それに対する引数、次の関数と続く
	//
	//補足
	//関数に対して引数が正しくない場合T_Fnsが[std::nullopt_t]になり生成不可になる
	template<class ...MT_Fns>
	constexpr FunctionMultiple(MT_Fns... setFns)
		:fns(N_Function::IS_BindFns(setFns...)) {}
	
	//仕様
	//複数の[Function]から[T_Args...]で呼び出せる関数オブジェクトを実行する
	//
	//引数
	//args::入力する引数
	template<class ...T_Args>
		requires std::same_as<typename N_Function::IS_MethodSearch<T_Fns,T_Args...>::Judge, std::true_type>
	constexpr auto operator()(T_Args... args)
	{
		return std::get<N_Function::IS_MethodSearch<T_Fns,T_Args...>::MethodNumber>(fns)(args...);
	}

};

template<class ...MT_Fns>
FunctionMultiple(MT_Fns... fns) -> FunctionMultiple<typename N_Function::IS_BindFns<MT_Fns...>::FnsType>;
