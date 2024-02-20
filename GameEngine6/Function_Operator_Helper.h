#pragma once

#include"Tuple.h"
#include"Function_Superficial_Data.h"

template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function;

namespace quiet::N_Function
{

	//仕様
	//[T_Parts...]から全通りのoperator()を作成する為にデータを整理する。
	//
	//テンプレート
	//[T_Parts...]::[Funcsion]の引数の型
	//
	//using 
	//[::type] 帰ってくるデータは関数１つ１つに対して
	//	引数が一致した時に呼び出す[Funcsion]の引数の番号
	//	要求するポインターの型
	//　要求する引数の型
	//を[tuple_t]で纏め、１つ１つの結果を[tuple_t]で纏める
	template<class ...T_Parts>
	struct I_Function_Operator_Helper
	{
		using fn_multi_data = I_Function_Helper<T_Parts...>;

		using core = Function_Core<Function<T_Parts...>>;


		//仕様
		//[T_Parts...]を元に全通りのoperator()にアクセスする為のデータを作成する。
		//
		//テンプレート
		//[T_access_number]::関数オブジェクト１つ１つの使用する引数の番号を纏めた型
		//[T_request_pointer]::関数オブジェクト１つ１つの要求するポインターの型を纏めた型
		//[T_request_args]::関数オブジェクト１つ１つの要求する引数の型を纏めた型
		// 
		//補足
		//関数オブジェクト１つに対して、複数の関数が纏められている場合、それらを展開し処理をする
		template<
			class T_access_number_List = typename fn_multi_data::access_number,
			class T_request_args_List = typename core::superficial::request_args,
			class T_request_pointer_List = typename core::superficial::request_pointer,
			class T_Result = tuple_t<>>
		struct S_Function_Operator_Helper
		{
			using type = T_Result;
		};

		//仕様
		// [T_access_number],[T_request_args],[T_request_pointer]の全てが[tuple_t]で纏められておらず、
		// 要求する引数が有効な場合、[T_Rusult]にデータを追加する。
		template<class T_access_number, class T_request_args,
			class T_request_pointer, class ...T_Result>
			requires requires
		{
			requires !N_Tuple::same_as_tuple_t<T_access_number>;
			requires !N_Tuple::same_as_tuple_t<T_request_args>;
			requires !N_Tuple::same_as_tuple_t<T_request_pointer>;
			requires is_invalid_not<T_request_args>;
		}
		struct S_Function_Operator_Helper<T_access_number,
			T_request_args, T_request_pointer,tuple_t<T_Result...>>
		{
			using operator_data = tuple_t<
				T_access_number,
				typename T_request_args::remove_p,
				T_request_pointer>;

			using type = tuple_t<T_Result...,operator_data>;
		};

		//仕様
		//[T_access_number_List],[T_request_args_List],[T_request_pointer_List]のうち、いずれか1つ以上が
		// [tuple_t]で纏められている場合、その値が取りうる全パターンを再起テンプレートにより取得する
		//
		//補足
		//[T_access_number_List],[T_request_args_List],[T_request_pointer_List]のうち、
		// いずれかの型が[tuple_t<>]となった時、再起処理を終了する
		template<class T_access_number_List, class T_request_args_List,
			class T_request_pointer_List, class T_Result>
			requires requires
		{
			requires same_as_nor<tuple_t<>,T_access_number_List, T_request_args_List, T_request_pointer_List>;
		}
		struct S_Function_Operator_Helper<T_access_number_List,
			T_request_args_List, T_request_pointer_List, T_Result>
		{


			//仕様
			//[T_Data]が[tuple_t]で纏められている場合は、先頭の要素の取得、除去を実施、
			//纏められていない場合は、そのままの値を返す
			template<class T_Data>
			struct S_Data_Expand
			{
				using remove = T_Data;
				using type = T_Data;
			};

			template<class T_Front_Data,class ...T_Data>
			struct S_Data_Expand<tuple_t<T_Front_Data, T_Data...>>
			{
				using remove = tuple_t<T_Data...>;
				using type = T_Front_Data;
			};

			//仕様
			//[T_access_number_List],[T_request_args_List],[T_request_pointer_List]のうち、
			// [tuple_t]で纏められている値は先頭の要素、
			// 纏められていない場合は、[S_Function_Operator_Helper]と同じ型を用いり、
			// その値で取りうる全パターンを[T_Result]に追加する
			using result = S_Function_Operator_Helper<
				typename S_Data_Expand<T_access_number_List>::type,
				typename S_Data_Expand<T_request_args_List>::type,
				typename S_Data_Expand<T_request_pointer_List>::type,
				T_Result>::type;



			//仕様
			//[T_access_number_List],[T_request_args_List],[T_request_pointer_List]のうち、いずれか1つ以上が
			// [tuple_t]で纏められている場合は、先頭の要素を排除し、纏められていない場合は、
			// [S_Function_Operator_Helper]と同じ型を用いり次の判定を行う。
			using type = S_Function_Operator_Helper<
				typename S_Data_Expand<T_access_number_List>::remove,
				typename S_Data_Expand<T_request_args_List>::remove,
				typename S_Data_Expand<T_request_pointer_List>::remove,
				result>::type;
		};

		using type = S_Function_Operator_Helper<>::type;

	};





}










