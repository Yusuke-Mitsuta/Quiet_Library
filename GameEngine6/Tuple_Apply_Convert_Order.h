#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"
#include"Tuple_Infinite.h"
#include"If_Type.h"

namespace N_Tuple::N_Apply
{

	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand;

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip;


	//仕様
	//供給する型のリストから、要求する型のリストに、型の展開を伴い変換を出来るか判定し、
	// その過程、結果を返す
	// 
	// using 
	//[type::request]::供給する型リストとの照合の結果、使用しなかった要求する型リスト
	//[type::set]::要求する型リストとの照合の結果、使用しなかった供給する型リスト
	//[type::conversion_expand_list]::供給する型リストの展開命令
	//[type::conversion_zip_list]::供給する型リストの圧縮命令
	// 
	//補足
	// 型の判定は後ろから実施する。
	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Convert_Order
	{

		//仕様
		//型の判定が終了する際に呼び出される
		template<class T_Request_Types_Tuple = invalid_t,
			class T_Set_Types_Tuple = invalid_t,
			class T_Conversion_Expand_List = tuple_t<>,
			class T_Conversion_Zip_List = tuple_t<>>
		struct S_Result
		{
			using type = S_Result;

			//供給する型リストとの照合の結果、使用しなかった要求する型リスト
			using request = T_Request_Types_Tuple;

			//要求する型リストとの照合の結果、使用しなかった供給する型リスト
			using set = T_Set_Types_Tuple;

			//供給する型リストの展開命令
			using conversion_expand_list = T_Conversion_Expand_List;

			//供給する型リストの圧縮命令
			using conversion_zip_list = T_Conversion_Zip_List;

		};


		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class T_Conversion_Expand_List = tuple_t<>,
			class T_Conversion_Zip_List = tuple_t<>
		>
		struct S_Convert_Order
		{
			using type = S_Result<T_Request_Types_Tuple, T_Set_Types_Tuple, T_Conversion_Expand_List, T_Conversion_Zip_List>::type;
		};

		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class ...T_Conversion_Expand,
			class ...T_Conversion_Zip>
			requires requires
		{
			requires same_as_not<tuple_t<>, T_Request_Types_Tuple>;
			requires same_as_not<tuple_t<>, T_Set_Types_Tuple>;
		}
		struct S_Convert_Order<T_Request_Types_Tuple, T_Set_Types_Tuple,
			tuple_t<T_Conversion_Expand...>,
			tuple_t<T_Conversion_Zip...>>
		{

			//仕様
			//要求する型リストが選択している型
			using request_t = T_Request_Types_Tuple::type;

			//仕様
			//供給する型リストが選択している型
			using set_t = T_Set_Types_Tuple::type;

			//仕様
			//互換性のある型に展開する
			// [using tuple}にて定義される型
			template<class T_Tuple>
			using expand = N_Tuple::S_Parameter<T_Tuple>::tuple;


			//仕様
			//選択中のタイプを展開する
			template<class T_Types_Tuple>
			using select_type_expand = N_Tuple::U_Insert_tuple_expand<
				typename T_Types_Tuple::remove,
				expand<typename T_Types_Tuple::type>>;


			//仕様
			// 要求する型リストと供給する型リストの先頭の型に対して、以下の判定を実施する。
			// 判定１：供給する型から、要求する型に変換出来るか判定する
			// 判定２：判定１が失敗した場合、供給する引数の型を展開出来るか判定する
			// 判定３：判定２が失敗した場合、要求する引数の型を展開出来るか判定する
			// 判定３が失敗した場合、エラーとして無効値を返す
			template<
				class T_Request=typename T_Request_Types_Tuple::type,
				class T_Set = typename T_Set_Types_Tuple::type>
			struct S_Apply_Control
			{
				//エラーの場合は無効値を返す
				using type = S_Result<T_Request_Types_Tuple, T_Set_Types_Tuple, tuple_t<T_Conversion_Expand...>, tuple_t<T_Conversion_Zip...>>::type;

			};

			//仕様
			//供給する型から、要求する型に変換できる場合
			template<class T_Request,class T_Set>
				requires requires
			{
				requires convertible_to<T_Set, T_Request>;
			}
			struct S_Apply_Control< T_Request, T_Set>
			{
				//要求する型、供給する型のリストを次に進め、次の型の判定に移る。
				using type = S_Convert_Order<
					typename T_Request_Types_Tuple::remove,
					typename T_Set_Types_Tuple::remove,
					tuple_t<T_Conversion_Expand...>,
					tuple_t<T_Conversion_Zip...>
				>::type;

			};

			//仕様
			//供給する引数の型を展開出来る場合
			template<class T_Request, class T_Set>
				requires requires
			{
				requires !convertible_to<T_Set, T_Request>;
				requires is_invalid_not<expand<T_Set>>;
			}
			struct S_Apply_Control< T_Request, T_Set>
			{

				//供給する型を展開し、
				// 展開した型の情報を別途保存する
				using type = S_Convert_Order<
					T_Request_Types_Tuple,
					select_type_expand<T_Set_Types_Tuple>,
					tuple_t<T_Conversion_Expand..., S_Conversion_Expand<set_t, T_Set_Types_Tuple::size>>,
					tuple_t<T_Conversion_Zip...>
				>::type;

			};

			//仕様
			//要求する引数の型を展開出来る場合
			template<class T_Request, class T_Set>
				requires requires
			{
				requires !convertible_to<T_Set, T_Request>;
				requires is_invalid_not<expand<T_Request>>;
				requires !is_invalid_not<expand<T_Set>>;
			}
			struct S_Apply_Control< T_Request, T_Set>
			{
				//要求する型を展開し、
				// 展開した型の情報を別途保存する
				using type =
					S_Convert_Order<
					select_type_expand<T_Request_Types_Tuple>,
					T_Set_Types_Tuple,
					tuple_t<T_Conversion_Expand...>,
					tuple_t<S_Conversion_Zip<request_t, T_Request_Types_Tuple::size>, T_Conversion_Zip...>
					>::type;
			};


			using type = S_Apply_Control<>::type;

		};




		//型の判定を前から実施する
		using type = S_Convert_Order<
			T_Request_Types_Tuple,
			T_Set_Types_Tuple>::type;

	};



}
