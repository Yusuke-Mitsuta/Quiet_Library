#pragma once

#include"Tuple.h"
#include"Function_Superficial_Data.h"

namespace N_Function
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
		using fn_multi_data = I_Function_Multiple_Helper<T_Parts...>;

		using core = Function_Core<typename fn_multi_data::type>;


		template<
			class T_access_number,
			class T_request_pointer,
			class T_request_args,
			class T_request_args_number,
			class T_Next>
		struct S_Function_Operator_Helper_Core;


		//仕様
		// [S_Function_Operator_Helper]で纏められた、１通りのoperator()を呼び出すデータと、
		//次以降のデータにアクセスする
		template<
			size_t ...t_access_number,
			class T_request_pointer,
			class T_request_args,
			size_t ...t_request_args_number,
			class T_Next>
		struct S_Function_Operator_Helper_Core<tuple_v<t_access_number...>,
			T_request_pointer, T_request_args, tuple_v<t_request_args_number...>, T_Next>
		{
			using type = tuple_t<tuple_v<t_access_number...>, T_request_pointer,
				tuple_t<N_Tuple::U_Element_t<t_request_args_number, T_request_args>...>>;

			using next = T_Next;

			constexpr S_Function_Operator_Helper_Core(auto... args) :
				T_Next(args...) {}
		};




		//仕様
		//[T_Parts...]を元に全通りのoperator()にアクセスする為のデータを作成する。
		//
		//テンプレート
		//[T_access_number]::関数オブジェクト１つ１つの使用する引数の番号を纏めた型
		//[T_request_pointer]::関数オブジェクト１つ１つの要求するポインターの型を纏めた型
		//[T_request_args]::関数オブジェクト１つ１つの要求する引数の型を纏めた型
		//
		//using
		//[::type] 1通りのoperator()にアクセスする為のデータと、次以降に処理をさせるデータを持たせた
		// [S_Function_Operator_Helper_Core]を呼び出す。
		// 次に処理するデータがない場合は、[invalid_t]を設定する
		// 
		//補足
		//関数オブジェクト１つに対して、複数の関数が纏められている場合、それらを展開し処理をする
		template<
			class T_access_number = typename fn_multi_data::access_number,
			class T_request_pointer = typename core::request_pointer,
			class T_request_args = typename core::request_args>
		struct S_Function_Operator_Helper
		{
			using type = 
				S_Function_Operator_Helper;
		};
		

		//仕様
		//[T_Parts...]に関数が1つしかない場合
		template<
			class T_access_number,
			class T_request_pointer,
			class T_request_args>
			requires requires
		{
			requires T_access_number::size == 1;
		}
		struct S_Function_Operator_Helper<
			T_access_number,
			T_request_pointer,
			T_request_args>
		{
			using type = S_Function_Operator_Helper_Core<
				typename T_access_number::type,
				T_request_pointer, T_request_args,
				N_Tuple::U_index_sequence<
				N_Tuple::S_Parameter<T_request_args>::head_size
				+not_is_invalid<typename T_request_args::type>
				>,
				invalid_t>;
		};

		//仕様
		//残りの関数が1つしかない場合
		template<
			size_t ...t_access_number,
			class T_request_pointer,
			class T_request_args>
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>>,
			tuple_t<T_request_pointer>,
			tuple_t<T_request_args>> :
			S_Function_Operator_Helper<tuple_t<tuple_v<t_access_number...>>,
			T_request_pointer,T_request_args>{};

		//仕様
		//先頭の関数オブジェクトの使用する引数の番号を纏めた型を使用するデータを纏める
		//
		//補足
		//関数オブジェクト１つに対して、複数の関数が纏められている場合、それらを展開し処理をする為、
		//残りの「関数オブジェクトの使用する引数の番号を纏めた型」と「要求する引数の型」が等しくなるまでは、
		//先頭の引数の番号を使用する関数のデータと見なして処理をする
		template<
			size_t ...t_access_number,
			class ...T_access_number,
			class T_Front_request_pointer,
			class ...T_request_pointer,
			class T_Front_request_args,
			class ...T_request_args >
			requires requires
		{
			requires (sizeof...(T_request_pointer) >= sizeof...(T_access_number));
		}
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>, T_access_number...>,
			tuple_t<T_Front_request_pointer, T_request_pointer...>,
			tuple_t<T_Front_request_args, T_request_args...>>
		{

			using next = S_Function_Operator_Helper<
				tuple_t<tuple_v<t_access_number...>, T_access_number...>,
				tuple_t<T_request_pointer...>,
				tuple_t<T_request_args...>>::type;

			using type = S_Function_Operator_Helper_Core<
				tuple_v<t_access_number...>,
				T_Front_request_pointer, T_Front_request_args,
				N_Tuple::U_index_sequence<
					N_Tuple::S_Parameter<T_Front_request_args>::head_size + not_is_invalid<typename T_Front_request_args::type>>,
				next>;
		};

		//仕様
		//先頭の関数オブジェクトの使用する引数の番号を纏めたデータを使用しない、
		//要求する引数、ポインターの型、の場合、先頭の関数オブジェクトの使用する引数の番号を次に進める
		//
		//補足
		//関数オブジェクトの使用する引数の番号を纏めた型が、要求する引数の型の残り数より多い場合、
		// 先頭の関数オブジェクトの使用する引数の番号を次に進める判定をする
		template<
			size_t ...t_access_number,
			class ...T_access_number,
			class ...T_request_pointer,
			class ...T_request_args >
			requires requires
		{
			requires (sizeof...(T_request_pointer) < sizeof...(T_access_number) + 1);
		}
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>, T_access_number...>,
			tuple_t<T_request_pointer...>,
			tuple_t<T_request_args...>>
		{
			using type = S_Function_Operator_Helper<
				tuple_t<T_access_number...>,
				tuple_t<T_request_pointer...>,
				tuple_t<T_request_args...>>::type;
		};

		//仕様
		//関数オブジェクト１つに対して、複数の関数が纏められている場合、それらを展開する
		template<
			size_t ...t_access_number,
			class ...T_access_number,
			class ...T_request_pointer,
			class ...T_Second_request_pointer,
			class ...T_request_args,
			class ...T_Second_request_args>
			requires requires
		{
			requires (sizeof...(T_request_pointer) >= sizeof...(T_access_number));
		}
		struct S_Function_Operator_Helper<
			tuple_t<tuple_v<t_access_number...>, T_access_number...>,
			tuple_t<tuple_t<T_request_pointer...>, T_Second_request_pointer...>,
			tuple_t<tuple_t<T_request_args...>, T_Second_request_args...>>
		{
			using type = S_Function_Operator_Helper<
				tuple_t<tuple_v<t_access_number...>, T_access_number...>,
				tuple_t<T_request_pointer..., T_Second_request_pointer...>,
				tuple_t<T_request_args..., T_Second_request_args...>>::type;
		};


		//仕様
		//[S_Function_Operator_Helper]から[S_Function_Operator_Helper_Core]を受け取り、
		//１通りのoperator()のデータを[T_Result]に格納、及び次のデータを取得する
		template<class T_Result=tuple_t<> ,class T_Operator_Data =typename S_Function_Operator_Helper<>::type>
		struct S_Function_Operator_Parameter
		{
			using type = T_Result;
		};

		template<class ...T_Result, not_is_invalid T_Operator_Data>
		struct S_Function_Operator_Parameter<tuple_t<T_Result...>, T_Operator_Data>
		{

			//仕様
			//要求する引数の型が無効値なら、データの格納をスキップする
			template<class T_Request_Args = N_Tuple::U_Element_t<2,typename T_Operator_Data::type>>
			struct S_Request_Args_Chack
			{
				using type= S_Function_Operator_Parameter<
					tuple_t<T_Result..., typename T_Operator_Data::type>,
					typename T_Operator_Data::next>::type;
			};

			template<>
			struct S_Request_Args_Chack<invalid_t>
			{
				using type= S_Function_Operator_Parameter<
					tuple_t<T_Result...>,
					typename T_Operator_Data::next>::type;
			};

			using type = S_Request_Args_Chack<>::type;
		};

		using type = S_Function_Operator_Parameter<>::type;

	};


}










