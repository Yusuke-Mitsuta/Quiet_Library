#pragma once

#include"Function.h"
#include"FunctionMultiple_Helper.h"
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
	//IS_FunctionMultipleOperator::Typeを実体化する事
	template <class ...T_Fns>
	struct IS_FunctionMultipleOperator
	{
	
		//仕様
		//複数の[Function]のoperatorを実装する
		//
		//T_TupleFns::[Function]が複数、格納されてるTuple
		//t_Even::実装するoperator()()が引数の順番になるようにするフラグ
		template<class T_TupleFns,bool t_Even = !((sizeof...(T_Fns)+std::tuple_size_v<T_TupleFns>) % 2)>
		struct S_FunctionMultipleOperator;

		template<class T_FlontFn, class ...T_BindArgs,bool t_Even>
		struct S_FunctionMultipleOperator<std::tuple<Function<T_FlontFn, T_BindArgs...>>,t_Even> :
			public Function<T_FlontFn, T_BindArgs...>
		{
			using Function<T_FlontFn, T_BindArgs...>::operator();


			constexpr S_FunctionMultipleOperator(T_FlontFn fn, T_BindArgs... args) :
				Function<T_FlontFn, T_BindArgs...>(fn, args...) {}
		};


		template<class T_FlontFn, class ...T_BindArgs, class ...T_Fns,bool t_Even>
		struct S_FunctionMultipleOperator<std::tuple<Function<T_FlontFn, T_BindArgs...>,T_Fns...>,t_Even> : 
			public Function<T_FlontFn, T_BindArgs...>,
			public S_FunctionMultipleOperator<std::tuple<T_Fns...>>
		{
			//仕様
			//実装するoperator()()が引数の順番になるようにする
			//総数が偶数かつ、残りの[Function]が偶数、又は総数が奇数かつ、残りの[Function]が奇数ならT_1とT_2を入れ替える
			using SwapType =typename IS_SwapType<
				S_FunctionMultipleOperator<std::tuple<T_Fns...>>, 
				Function<T_FlontFn, T_BindArgs...>, 
				t_Even>;

			using SwapType::Type_1::operator();
			using SwapType::Type_2::operator();

			template<class ...MT_Fns>
			constexpr S_FunctionMultipleOperator(T_FlontFn fn,T_BindArgs... args,MT_Fns... fns):
				Function<T_FlontFn, T_BindArgs...>(fn,args...),
				S_FunctionMultipleOperator<std::tuple<T_Fns...>>(fns...) {}
		};


		using Type = typename S_FunctionMultipleOperator<typename IS_FunctionMultiple_Helper<T_Fns...>::Fns>;

	};


}