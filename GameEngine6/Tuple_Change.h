#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	//仕様
	//[T_Tuple_p]の[t_Change_Point]の値を[T_Change]に変更する
	// 
	//[t_Change_Point]::[T_Tuple_p]の変更する要素番号、指定しない場合は、現在の選択位置が仕様される
	template<class T_Tuple_p,class T_Change,size_t t_Change_Point=S_Parameter<T_Tuple_p>::Size_Head>
	struct I_Change
	{
	private:

		template<class T_Tuple_p>
		struct S_Change
		{
			using type = T_Tuple_p;
		};

		template<class T_Head,not_is_nullopt T,class T_Tail>
			requires (S_Parameter<T_Tuple_p>::Size_Head == t_Change_Point)
		struct S_Change<Tuple_tp<T_Head,T,T_Tail>>
		{
			using type = Tuple_tp<T_Head, T_Change, T_Tail>;
		};

		template<class T_Head, not_is_nullopt T, class T_Tail>
			requires (S_Parameter<T_Tuple_p>::Size_Head != t_Change_Point)
		struct S_Change<Tuple_tp<T_Head, T, T_Tail>>
		{
			using Change_Tuple = typename S_Change<U_Select<t_Change_Point, Tuple_tp<T_Head, T, T_Tail>>>::type;

			using type = U_Select<S_Parameter<T_Tuple_p>::Size_Head, Change_Tuple>;
		};

	public:

		using type = S_Action_Tuple_tp<S_Change, T_Tuple_p>::type;

	};

}