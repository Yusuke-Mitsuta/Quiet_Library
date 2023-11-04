#pragma once
//
//#include"Function_Multiple_Helper.h"
//#include"SwapType.h"
//
//namespace N_Function
//{
//	
//	//仕様
//	//[FunctionMultiple]のOperator部分の実装
//	//template
//	//...T_Fns::複数の関数ポインター、及びそれに対する引数
//	//
//	//補足
//	//IS_FunctionMultipleOperatorの実体化は禁止とする
//	//IS_Function_Multiple_Operator::Typeを実体化する事
//	template <class ...T_Fns>
//	struct IS_Function_Multiple_Operator
//	{
//
//		using Fns = typename IS_Function_Multiple_Helper<T_Fns...>::Fns;
//
//		//仕様
//		//複数の[Function_Single]のoperatorを実装する
//		//
//		//TP_Fns::[Function_Single]が複数、格納されてるTuple
//		//t_Even::実装するoperator()()が引数の順番になるようにするフラグ
//		template<class TP_Fns,bool t_Even = !((Fns::Size+TP_Fns::Size) % 2)>
//		struct S_Function_Multiple_Operator;
//
//		template<class T_FlontFn, class ...T_BindArgs,bool t_Even>
//		struct S_Function_Multiple_Operator<S_Parameter<Function_Single<T_FlontFn, T_BindArgs...>>,t_Even> :
//			public Function_Single<T_FlontFn, T_BindArgs...>
//		{
//			using Function_Single<T_FlontFn, T_BindArgs...>::operator();
//
//			template<class T_Fns>
//				requires (S_MethodData<T_Fns>::Method_Type == E_Method_T::Function) ||
//			(S_MethodData<T_Fns>::Method_Type == E_Method_T::Static_Method)
//			constexpr S_Function_Multiple_Operator(T_Fns method, T_BindArgs... args) :
//				Function_Single<T_FlontFn, T_BindArgs...>(method, args...) {}
//
//			template<class T_Common_Pointer, class T_Fns>
//				requires (S_MethodData<T_Fns>::Method_Type == E_Method_T::Function) ||
//			(S_MethodData<T_Fns>::Method_Type == E_Method_T::Static_Method)
//			constexpr S_Function_Multiple_Operator(T_Common_Pointer* common_p, T_Fns method, T_BindArgs... args) :
//				Function_Single<T_FlontFn, T_BindArgs...>(method, args...) {}
//
//			template<class T_Common_Pointer, class T_Fns, class Dedicated_Pointer>	
//				requires (S_MethodData<T_Fns>::Method_Type == E_Method_T::Class_Method)
//			constexpr S_Function_Multiple_Operator(T_Common_Pointer* common_p, Dedicated_Pointer* dedicated_p,T_Fns method,T_BindArgs... args) :
//				Function_Single<T_FlontFn, T_BindArgs...>(dedicated_p, method, args...){}
//
//			template<class T_Common_Pointer, class T_Fns, class ...TP_Fn_Inners>
//				requires (S_MethodData<T_Fns>::Method_Type == E_Method_T::Class_Method)
//			constexpr S_Function_Multiple_Operator(T_Common_Pointer* common_p, T_Fns method, T_BindArgs... args) :
//				Function_Single<T_FlontFn, T_BindArgs...>(common_p, method, args...) {}
//
//		};
//
//
//		template<class T_FlontFn, class ...T_BindArgs, class ...T_Fns,bool t_Even>
//		struct S_Function_Multiple_Operator<S_Parameter<Function_Single<T_FlontFn, T_BindArgs...>, T_Fns...>, t_Even> :
//			public Function_Single<T_FlontFn, T_BindArgs...>,
//			public S_Function_Multiple_Operator<S_Parameter<T_Fns...>>
//		{
//			//仕様
//			//実装するoperator()()が引数の順番になるようにする
//			//総数が偶数かつ、残りの[Function_Single]が偶数、又は総数が奇数かつ、残りの[Function_Single]が奇数ならT_1とT_2を入れ替える
//			using SwapType = typename IS_Swap_Type<
//				S_Function_Multiple_Operator<S_Parameter<T_Fns...>>,
//				Function_Single<T_FlontFn, T_BindArgs...>,
//				t_Even>;
//
//			using SwapType::Type_1::operator();
//			using SwapType::Type_2::operator();
//
//			template<class T_Fns, class ...MT_Fn_Parts>
//				requires (S_MethodData<T_Fns>::Method_Type == E_Method_T::Function) || 
//						 (S_MethodData<T_Fns>::Method_Type == E_Method_T::Static_Method)
//			constexpr S_Function_Multiple_Operator(T_Fns method, T_BindArgs... args, MT_Fn_Parts... fn_Parts) :
//				Function_Single<T_FlontFn, T_BindArgs...>(method, args...),
//				S_Function_Multiple_Operator<S_Parameter<T_Fns...>>(fn_Parts...) {}
//
//			template<class T_Common_Pointer, class T_Fns, class ...MT_Fn_Parts>
//				requires (S_MethodData<T_Fns>::Method_Type == E_Method_T::Function) || 
//						 (S_MethodData<T_Fns>::Method_Type == E_Method_T::Static_Method)
//			constexpr S_Function_Multiple_Operator(T_Common_Pointer* common_p,T_Fns method,T_BindArgs... args, MT_Fn_Parts... fn_Parts) :
//				Function_Single<T_FlontFn, T_BindArgs...>(method, args...),
//				S_Function_Multiple_Operator<S_Parameter<T_Fns...>>(common_p, fn_Parts...) {}
//
//			template<class T_Common_Pointer, class T_Fns, class ...MT_Fn_Parts>
//				requires (S_MethodData<T_Fns>::Method_Type == E_Method_T::Class_Method)
//			constexpr S_Function_Multiple_Operator(T_Common_Pointer* common_p, T_Fns method, T_BindArgs... args, MT_Fn_Parts... fn_Parts) :
//				Function_Single<T_FlontFn, T_BindArgs...>(common_p, method, args...),
//				S_Function_Multiple_Operator<S_Parameter<T_Fns...>>(common_p, fn_Parts...) {}
//
//			template<class T_Common_Pointer, class T_Fns, class Dedicated_Pointer, class ...MT_Fn_Parts>
//				requires (S_MethodData<T_Fns>::Method_Type == E_Method_T::Class_Method)
//			constexpr S_Function_Multiple_Operator(T_Common_Pointer* common_p, Dedicated_Pointer* dedicated_p, T_Fns method, T_BindArgs... args, MT_Fn_Parts... fn_Parts) :
//				Function_Single<T_FlontFn, T_BindArgs...>(dedicated_p,method, args...),
//				S_Function_Multiple_Operator<S_Parameter<T_Fns...>>(common_p, fn_Parts...) {}
//			
//		};
//
//		using Type =S_Function_Multiple_Operator<typename IS_Function_Multiple_Helper<T_Fns...>::Fns>;
//
//	};
//
//
//}