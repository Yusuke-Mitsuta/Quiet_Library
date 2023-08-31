#pragma once

#include"Function_Multiple_Helper.h"
#include"SwapType.h"

namespace N_Function
{
	
	//仕様
	//[FunctionMultiple]のOperator部分の実装
	//template
	//...T_Fns::複数の関数ポインター、及びそれに対する引数
	//
	//補足
	//IS_FunctionMultipleOperatorの実体化は禁止とする
	//IS_Function_Multiple_Operator::Typeを実体化する事
	template <class ...T_Fns>
	struct IS_Function_Multiple_Operator
	{



		//template<class T_Methods>
		//struct S_Function_Multiple_Chip;
		//
		//template<class T_Method,class ...TP_BindArgs,class T_Methods>
		//struct S_Function_Multiple_Chip<Function_Single<T_Method,TP_BindArgs...>> :
		//	public S_Function_Multiple_Chip
		//{











		//};












	
		//仕様
		//複数の[Function_Single]のoperatorを実装する
		//
		//T_TupleFns::[Function_Single]が複数、格納されてるTuple
		//t_Even::実装するoperator()()が引数の順番になるようにするフラグ
		template<class T_TupleFns,bool t_Even = !((sizeof...(T_Fns)+std::tuple_size_v<T_TupleFns>) % 2)>
		struct S_Function_Multiple_Operator;

		template<class T_FlontFn, class ...T_BindArgs,bool t_Even>
		struct S_Function_Multiple_Operator<std::tuple<Function_Single<T_FlontFn, T_BindArgs...>>,t_Even> :
			public Function_Single<T_FlontFn, T_BindArgs...>
		{
			using Function_Single<T_FlontFn, T_BindArgs...>::operator();

			constexpr S_Function_Multiple_Operator(T_FlontFn fn, T_BindArgs... args) :
				Function_Single<T_FlontFn, T_BindArgs...>(fn, args...) {}
		};


		template<class T_FlontFn, class ...T_BindArgs, class ...T_Fns,bool t_Even>
		struct S_Function_Multiple_Operator<std::tuple<Function_Single<T_FlontFn, T_BindArgs...>,T_Fns...>,t_Even> : 
			public Function_Single<T_FlontFn, T_BindArgs...>,
			public S_Function_Multiple_Operator<std::tuple<T_Fns...>>
		{
			//仕様
			//実装するoperator()()が引数の順番になるようにする
			//総数が偶数かつ、残りの[Function_Single]が偶数、又は総数が奇数かつ、残りの[Function_Single]が奇数ならT_1とT_2を入れ替える
			using SwapType =typename IS_Swap_Type<
				S_Function_Multiple_Operator<std::tuple<T_Fns...>>, 
				Function_Single<T_FlontFn, T_BindArgs...>, 
				t_Even>;

			using SwapType::Type_1::operator();
			using SwapType::Type_2::operator();

			template<class ...MT_Fns>
			constexpr S_Function_Multiple_Operator(T_FlontFn fn,T_BindArgs... args,MT_Fns... fns):
				Function_Single<T_FlontFn, T_BindArgs...>(fn,args...),
				S_Function_Multiple_Operator<std::tuple<T_Fns...>>(fns...) {}
		};


		using Type = typename S_Function_Multiple_Operator<typename IS_Function_Multiple_Helper<T_Fns...>::Fns>;

	};


}