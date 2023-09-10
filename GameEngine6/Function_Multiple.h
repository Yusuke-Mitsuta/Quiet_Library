#pragma once

//#include"Function_Multiple_Helper.h"
//#include"Function_Multiple_Operator.h"


//namespace N_Function
//{
//
//	//仕様
//	//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
//	//
//	//テンプレート
//	//関数ポインター、それに対する引数が不適正なら[T_FlontFn]が[std::nullopt_t]になる
//	template<not_same_as<std::nullopt_t> T_FlontFn, class ...T_Fns>
//	class Function_Multiple :
//		public N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type
//	{
//
//		using Parent = N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type;
//
//	public:
//
//		using N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type::operator();
//
//		template<int function_Number>
//		using N_Function::IS_Function_Multiple_Operator<T_FlontFn, T_Fns...>::Type::Select<function_Number>();
//
//
//		//仕様
//		//複数の関数ポインター、及びそれに対する引数の値が正しいか、後方一致で判定する
//		//
//		//引数
//		//[MT_Fn_Parts...]::(共通で使用するクラスポインター , 関数ポインターor関数オブジェクト , それに対する引数 , 次で使用するクラスポインター . 関数ポインターor関数オブジェクト ...)
//		//
//		//静的な関数ポインター and 関数Objectはクラスポインターの設定不可
//		//
//		//共通で使用するクラスのポインターはクラスポインターが設定されていない関数ポインターを呼び出すのに使用する
//		//
//		//共通で使用するクラスポインターは全ての関数ポインターが呼び出せる場合設定不要
//		// 
//		//補足
//		//関数に対して引数が正しくない場合T_Fnsが[std::nullopt_t]になり生成不可になる
//		template<class ...MT_Fn_Parts>
//		constexpr Function_Multiple(MT_Fn_Parts... fn_Parts) :
//			N_Function::IS_Function_Multiple_Operator<MT_Fn_Parts...>::Type(fn_Parts...) {}
//
//	};
//
//	template<class MT_Flnot_Fn_Parts, class ...MT_Fn_Parts>
//	Function_Multiple(MT_Flnot_Fn_Parts flnot_Fn_Parts, MT_Fn_Parts... fn_Parts) -> Function_Multiple
//		<typename N_Function::IS_Function_Multiple_Helper<MT_Flnot_Fn_Parts, MT_Fn_Parts...>::Judge, MT_Fn_Parts...>;
//
//}