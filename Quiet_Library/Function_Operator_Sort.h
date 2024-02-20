#pragma once

#include"Tuple.h"

namespace quiet::N_Function
{

	//仕様
	//[Function]に入れた際、[::operator()]が
	// セットした順番通りに表示されるように並び替える
	//
	//テンプレート
	//[T_Operator_Parameters]::[I_Function_Operator_Helper]からのデータを受け取る
	// 
	//補足
	//[ 0, 1 , 2 , 3 , 4 , 5]　とした時、
	//[ 0, 2 , 4 , 5 , 3 , 1]　の順番になる為、
	// 
	//[ 0, 5 , 1 , 4 , 2 , 3]　の順番になる様に並び替えると、
	//[ 0, 1 , 2 , 3 , 4 , 5]　の順番になる
	template<class T_Operator_Parameters>
	struct I_Function_Operator_Sort
	{

		//仕様
		//前と後ろから型を一つずつ取り、[T_Result]に格納して行く
		//	真ん中の型の場合は、その型を[T_Result]に格納する
		//
		//真ん中を超えた場合、格納処理を終了する。
		template<class T_Result = tuple_t<>, 
			class T_Operator_Parameters = T_Operator_Parameters,
			class T_Reverse_Operator_Parameters = typename T_Operator_Parameters::reverse>
		struct S_Function_Operator_Sort
		{
			using type = T_Result;
		};
		
		//仕様
		//真ん中の型の場合は、その型を[T_Result]に格納する
		template<class ...T_Result, class T_Operator_Parameters, class T_Reverse_Operator_Parameters>
			requires requires
		{
			requires T_Operator_Parameters::head_size == T_Operator_Parameters::tail_size;
			requires T_Operator_Parameters::size > 0;
		}
		struct S_Function_Operator_Sort<tuple_t<T_Result...>,T_Operator_Parameters,T_Reverse_Operator_Parameters>
		{
			using type = tuple_t<T_Result...,typename T_Operator_Parameters::type>;
			using type3 = tuple_t<T_Result...,typename T_Operator_Parameters::type>;
			using type4 = T_Operator_Parameters::type;
		};

		//仕様
		//前と後ろから型を一つずつ取り、[T_Result]に格納して行く
		template<class ...T_Result, class T_Operator_Parameters, class T_Reverse_Operator_Parameters>
			requires requires
		{
			requires T_Operator_Parameters::head_size < T_Operator_Parameters::tail_size;
		}
		struct S_Function_Operator_Sort<tuple_t<T_Result...>, T_Operator_Parameters, T_Reverse_Operator_Parameters>
		{
			
			using merge_tuple = tuple_t<T_Result...,
				typename T_Operator_Parameters::type,
				typename T_Reverse_Operator_Parameters::type>;

			using type = S_Function_Operator_Sort<merge_tuple,
				typename T_Operator_Parameters::next,
				typename T_Reverse_Operator_Parameters::next>::type;

			using type2 = S_Function_Operator_Sort<merge_tuple,
				typename T_Operator_Parameters::next,
				typename T_Reverse_Operator_Parameters::next>;
		};
		
		using type = S_Function_Operator_Sort<>::type;
		using type1 = S_Function_Operator_Sort<>;
	};

}