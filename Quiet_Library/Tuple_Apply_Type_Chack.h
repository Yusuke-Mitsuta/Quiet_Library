/*!
 * Tuple_Apply_Type_Chack.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"
#include"Tuple_Infinite.h"
#include"SwapType.h"

namespace quiet::N_Tuple::N_Apply
{

	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand;

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip;

	//仕様
	//供給する型のリストから、要求する型のリストに、型の展開を伴い変換を出来るか判定する。
	//
	//テンプレート
	//[T_Result_Request_Types_Tuple]::[tuple_t<...>]で定義された要求する型リスト
	//[T_Result_Set_Types_Tuple]::[tuple_t<...>]で定義された供給する型リスト
	// 
	//変数
	//[value]::判定の結果
	//	[ value < 0 ] -> 変換失敗
	//	[ value == 0 ] -> 変換成功
	//	[ value >= 0 ] -> 変換成功の上、可変長引数の数を返す
	// 
	//補足
	//供給する型リストに可変長引数を定義する際
	// [N_Tuple::N_Apply::S_Infinite_Args< T_Request_Order >]をリストの最後に定義する事。
	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Type_Chack
	{
	private:
		using request_expand = U_Expand_All<T_Request_Types_Tuple>;

		using set_expand = U_Expand_All<T_Set_Types_Tuple>;

		//仕様
		//[T_Result_Request_Types_Tuple,T_Result_Set_Types_Tuple]リスト内の[tuple]と互換性がある型を全て展開し、
		// 型の互換性があるか判定する
		// 
		//テンプレート
		//[T_Expand_Number]::[T_Result_Request_Types_Tuple]を展開した際の要素に対応する
		// 番号のリスト
		// ※std::index_sequence< 要素数 >の中身を[tuple_v]で定義した型
		// 
		//補足
		//供給する型リストに可変長引数を定義されている場合、
		// 可変長引数を除いた型を判定し、可変長引数の判定に移行する
		template<class T_Expand_Number =
			U_index_sequence<request_expand::size - is_Infinite_Args<typename T_Request_Types_Tuple::back_t>>>
		struct S_Type_Chack
		{
			using type = S_Type_Chack;
			static constexpr int value = -1;
		};
		
		//仕様
		//可変長引数が定義されて無く、型リスト同士の判定が成功の場合
		template<size_t ...t_Expand_Number>
			requires ((convertible_to<
				U_Element_t<t_Expand_Number, set_expand>,
				U_Element_t<t_Expand_Number, request_expand>> && ...) &&
				(request_expand::size == sizeof...(t_Expand_Number)) &&
				(set_expand::size== sizeof...(t_Expand_Number)))
		struct S_Type_Chack<tuple_v<t_Expand_Number...>>
		{
			using type = S_Type_Chack;
			static constexpr int value = 0;
		};
		
		//仕様
		//可変長引数が定義されてるかつ、可変長引数の定義を除いた型リスト同士の判定が成功の場合
		template<size_t ...t_Expand_Number>
			requires ((convertible_to<
				U_Element_t<t_Expand_Number, set_expand>,
				U_Element_t<t_Expand_Number, request_expand>> && ...) &&
				(request_expand::size != sizeof...(t_Expand_Number)) &&
				(set_expand::size >= sizeof...(t_Expand_Number)))
		struct S_Type_Chack<tuple_v<t_Expand_Number...>>
		{
			//可変長引数が定義されている型に対して、[tuple]と互換性がある型を全て展開した型
			using infinite_args_expand = U_Expand_All<typename T_Request_Types_Tuple::back_t::constructor_args>;

			//可変長引数を除いて判定を実施した型を除外
			using set_expand_rest = U_Range<set_expand, sizeof...(t_Expand_Number), set_expand::size>;

			//[infinite_args_expand]の要素数に対応する型の番号リスト
			using infinite_args_expand_number = U_index_sequence<infinite_args_expand::size>;

			
			//仕様
			//[infinite_args_expand]と
			// [set_expand_rest]の
			// 　[t_infinite_args_Num * infinite_args_expand::size ]番目からを
			//	 [infinite_args_expand::size]だけ判定する
			// 
			//補足
			// 判定が成功すれば[t_infinite_args_Num]を一つ進め、再度判定を実施する
			// 最後まで判定が成功すれば、必要な可変長引数の数として、[t_infinite_args_Num]を出力する。
			template<class T_Infinite_Args_Expand_Number, size_t t_infinite_args_Num = 0>
			struct S_Infinite_Args_Chack
			{
				using type = S_Infinite_Args_Chack;
				static constexpr int value = -1;
			};

			template<size_t ...t_Infinite_Args_Expand_Number, size_t t_infinite_args_Num>
				requires (convertible_to<
					U_Element_t<t_Infinite_Args_Expand_Number + (infinite_args_expand::size *t_infinite_args_Num), set_expand_rest>,
					U_Element_t<t_Infinite_Args_Expand_Number, infinite_args_expand>> && ...)
			struct S_Infinite_Args_Chack<tuple_v<t_Infinite_Args_Expand_Number...>, t_infinite_args_Num>
			{

				using type = S_Infinite_Args_Chack<
					tuple_v<t_Infinite_Args_Expand_Number...>, t_infinite_args_Num + 1>::type;
			};

			template<class T_Infinite_Args_Expand_Number,size_t t_infinite_args_Num>
				requires (infinite_args_expand_number::size* t_infinite_args_Num == set_expand_rest::size)
			struct S_Infinite_Args_Chack<T_Infinite_Args_Expand_Number, t_infinite_args_Num>
			{
				using type = S_Infinite_Args_Chack;
				static constexpr int value = t_infinite_args_Num;

			};

			//仕様
			//残っている型の型[set_expand_rest::size]が
			// 可変長引数が要求する型の数[infinite_args_expand::size]で割り切るか判定する
			//
			//補足
			// 割り切た場合、型の判定に移行する
			// 割り切れない場合は、判定失敗になる
			template<bool t_size_chack
				= !static_cast<bool>(set_expand_rest::size % infinite_args_expand::size)>
			struct S_Infinite_Args_Size_Chack
			{
				using type =S_Infinite_Args_Size_Chack;
				static constexpr int value = -1;
			};

			template<>
			struct S_Infinite_Args_Size_Chack<true>
			{
				using type = S_Infinite_Args_Chack<infinite_args_expand_number>::type;
			};

			using type = S_Infinite_Args_Size_Chack<>::type;

		};
	public:

		using type = S_Type_Chack<>::type;

		static constexpr int value = type::value;

	};

	//仕様
	//供給する型リストから、要求する型リストに定義されている可変長引数の要素数を割り出し、
	//可変長引数と同等の型に置き換える。
	//
	// 補足
	// 可変長引数は[N_Tuple::N_Apply::S_Infinite_Args< T_Request_Order >]型であり、
	// リストの最後に定義される。
	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct S_Infinite_Args_Conversion
	{
		using type = T_Request_Types_Tuple;
	};


	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
		requires requires
	{
		requires is_Infinite_Args<typename T_Request_Types_Tuple::back_t>;
		requires I_Type_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple>::value >= 0;
	}
	struct S_Infinite_Args_Conversion< T_Request_Types_Tuple, T_Set_Types_Tuple>
	{
		using type =
			U_Merge_tuple_expand<
			typename T_Request_Types_Tuple::back::remove,
			U_Repeat_Multiple<
				typename T_Request_Types_Tuple::back_t::type,
				I_Type_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple>::value>
			>::remove_p;

	};


}