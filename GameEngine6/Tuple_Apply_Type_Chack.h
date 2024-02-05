#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include"Tuple_Apply_Fn.h"
#include"Tuple_Apply_Array_Set.h"
#include"Tuple_Apply_Request.h"
#include"Tuple_Apply_Class_Create.h"
#include"Tuple_Infinite.h"

namespace N_Tuple::N_Apply
{


	template<class T_Expand, size_t t_point>
	struct S_Conversion_Expand;

	template<class T_Zip, size_t t_point>
	struct S_Conversion_Zip;


	//仕様
	//供給する型のリストから、要求する型のリストに、型の展開を伴い変換を出来るか判定する。
	//
	//補足
	// 型の判定は後ろから実施する。
	template<class T_Request_Types_Tuple,
		class T_Set_Types_Tuple>
	struct I_Apply_Type_Chack
	{

		//仕様
		//型の判定が終了する際に呼び出される
		template<class T_Request_Types_Tuple = invalid_t,
			class T_Conversion_Expand_List = tuple_t<>,
			class T_Conversion_Zip_List = tuple_t<>>
		struct S_Result
		{
			
			using request = T_Request_Types_Tuple;

			using conversion_expand_list = T_Conversion_Expand_List;

			using conversion_zip_list = T_Conversion_Zip_List;

		};


		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class T_Conversion_Expand_List = tuple_t<>,
			class T_Conversion_Zip_List=tuple_t<>
		>
		struct S_Apply_Type_Chack
		{
			using type = S_Result<typename T_Request_Types_Tuple::reverse, T_Conversion_Expand_List, T_Conversion_Zip_List>;
		};


		template<class T_Request_Types_Tuple,
			class T_Set_Types_Tuple,
			class ...T_Conversion_Expand,
			class ...T_Conversion_Zip>
			requires requires
		{
			requires is_invalid_not<typename T_Request_Types_Tuple::type>;
			requires is_invalid_not<typename T_Set_Types_Tuple::type>;
		}
		struct S_Apply_Type_Chack<T_Request_Types_Tuple, T_Set_Types_Tuple, 
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
				U_Reverse<expand<typename T_Types_Tuple::type>>>;


			//仕様
			// 要求する型リストと供給する型リストの先頭の型に対して、以下の判定を実施する。
			// 判定１：供給する型から、要求する型に変換出来るか判定する
			// 判定２：判定１が失敗した場合、供給する引数の型を展開出来るか判定する
			// 判定３：判定２が失敗した場合、要求する引数の型を展開出来るか判定する
			// 判定３が失敗した場合、エラーとして無効値を返す
			template<bool t_constructible_from=convertible_to<set_t,request_t>,
				bool t_Request_Types_Expand = is_invalid_not<expand<request_t>>,
				bool t_Set_Types_Expand= is_invalid_not<expand<set_t>> >
			struct S_Apply_Control
			{
				//エラーの場合は無効値を返す
				using type = S_Result<>;

			};

			//仕様
			//供給する型から、要求する型に変換できる場合
			template<bool t_Request_Types_Expand, bool t_Set_Types_Expand>
			struct S_Apply_Control<true,t_Request_Types_Expand,t_Set_Types_Expand>
			{
				//要求する型、供給する型のリストを次に進め、次の型の判定に移る。
				using type = S_Apply_Type_Chack<
					typename T_Request_Types_Tuple::remove,
					typename T_Set_Types_Tuple::remove,
					tuple_t<T_Conversion_Expand...>,
					tuple_t<T_Conversion_Zip...>
				>::type;

			};

			//仕様
			//供給する引数の型を展開出来る場合
			template<bool t_Request_Types_Expand>
			struct S_Apply_Control<false, t_Request_Types_Expand, true>
			{

				//供給する型を展開し、
				// 展開した型の情報を別途保存する
				using type = S_Apply_Type_Chack<
					T_Request_Types_Tuple,
					select_type_expand<T_Set_Types_Tuple>,
					tuple_t<T_Conversion_Expand...,
						S_Conversion_Expand<set_t,T_Set_Types_Tuple::head_size>>,
					tuple_t<T_Conversion_Zip...>
					>::type;

			};

			//仕様
			//要求する引数の型を展開出来る場合
			template<>
			struct S_Apply_Control<false, true, false>
			{
				//要求する型を展開し、
				// 展開した型の情報を別途保存する
				using type =
					S_Apply_Type_Chack<
					select_type_expand<T_Request_Types_Tuple>,
					T_Set_Types_Tuple,
					tuple_t<T_Conversion_Expand...>,
					tuple_t<T_Conversion_Zip...,S_Conversion_Zip<request_t, T_Request_Types_Tuple::head_size>>
					>::type;
			};

			using type = S_Apply_Control<>::type;

		};

		//型の判定は後ろから実施する為、
		//型リストの並びを反転する
		using type = S_Apply_Type_Chack<
			typename T_Request_Types_Tuple::reverse,
			typename T_Set_Types_Tuple::reverse::create_p>::type;

		using conversion = type;

	};


}
