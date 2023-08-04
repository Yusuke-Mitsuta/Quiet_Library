#pragma once

#include"Function_Multiple_Helper.h"
#include"Function_Multiple_Operator.h"


namespace N_Function
{

	//仕様
	//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
	//
	//テンプレート
	//関数ポインター、それに対する引数が不適正なら[T_FlontFn]が[std::nullopt_t]になる
	template<not_same_as<std::nullopt_t> T_FlontFn, class ...T_Fns>
	class Function_Multiple :
		public N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type
	{

	public:

		using N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type::operator();

		//仕様
		//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
		//
		//引数
		//fns::関数ポインターor[Function_Single]、それに対する引数、次の関数と続く
		//
		//補足
		//関数に対して引数が正しくない場合T_Fnsが[std::nullopt_t]になり生成不可になる
		template<class MT_FlontFn, class ...MT_Fns>
		constexpr Function_Multiple(MT_FlontFn flontFn, MT_Fns... fns) :
			N_Function::IS_Function_Multiple_Operator<MT_FlontFn, MT_Fns...>::Type(flontFn, fns...) {}

	};

	template<class MT_FlontFn, class ...MT_Fns>
	Function_Multiple(MT_FlontFn setfn, MT_Fns... setFns) -> Function_Multiple
		<typename N_Function::IS_Function_Multiple_Helper<MT_FlontFn, MT_Fns...>::Judge, MT_Fns...>;

}