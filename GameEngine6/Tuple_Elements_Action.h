#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	//仕様
	//[T_Tuple]の要素を一つずつ取り出し、[TT_Action]の[::type]を実行し、結果を[tuple_t]に纏める
	//
	//テンプレート
	//[TT_Action]::[type]を呼び出すクラステンプレート
	//[T_Tuple]::展開し、各要素で[TT_Action::type]を呼び出す
	//[T_Extra...]::[TT_Action::type]を呼び出す際、追加でセットする型
	//
	//補足
	//[T_Tuple -> tuple_t<T...>] -> [tuple_t<TT_Action<T,T_Extra...>::type...>]となる
	template<template<class...>class TT_Action,class T_Tuple,class ...T_Extra>
	struct I_Elements_Action
	{
	private:
		template<class T_Tuple>
		struct S_Elements_Action
		{
			using type = TT_Action<T_Tuple, T_Extra...>::type;
		};

		template<class ...T>
		struct S_Elements_Action<tuple_t<T...>>
		{
			using type = tuple_t<typename TT_Action<T, T_Extra...>::type...>;
		};
	public:
		using type = S_Tuple_t_Change_Action<S_Elements_Action, T_Tuple>::Return_not_p;

	};

}