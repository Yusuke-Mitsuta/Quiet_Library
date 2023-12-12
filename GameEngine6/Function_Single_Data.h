#pragma once

#include"Function_Core.h"
#include"Tuple.h"
#include"Concept.h"


template<not_is_invalid T_Fns>
class Function;


namespace N_Function
{
	template<class T_Request_Args, class T_Request_Pointer>
	struct Request_Core;

	template<class T_Fn_Data>
	struct I_Request;

	//仕様
	//関数オブジェクトの型に対して、続く引数の型が有効か判定する。
	//
	//テンプレート
	//[T_Fn_Parts...]::
	// 第一引数は第二引数の呼び出しに使用するクラスポインターの型である。クラスポインターの型を判定しない場合は指定不要である。静的メソッド、クラスポインターの型を指定済み、の場合は指定不可である。
	// 第二引数は関数の型、若しくは、引数をbindした型[Function_Core],[Method_Core]とする
	// 第三引数以降は、第二引数の関数オブジェクトの引数に指定する型リスト
	template<class ...T_Fn_Parts>
	struct I_Function_Single_Data
	{

		//仕様
		//関数オブジェクトが[T_Fn_Parts...]内に存在しない場合
		template<class ...T_Fn_Parts>
		struct S_Function_Data
		{
			using function = invalid_t;
			using bind_args = invalid_t;
			using pointer = invalid_t;
			using c_name = invalid_t;
			using request = Request_Core<invalid_t,invalid_t>;
			using r_type = invalid_t;





		};

		//仕様
		//共通で使用するポインターの型をセットする
		template<class T_Dedicated_Point, class ...T_Fn_Parts>
			requires (std::is_class_v<T_Dedicated_Point>)
		struct S_Function_Data<T_Dedicated_Point*, T_Fn_Parts...> :
			S_Function_Data<T_Fn_Parts...>
		{
			using pointer = T_Dedicated_Point;
		};

		//仕様
		//引数の型をセットする
		template<class T_Fn, class ...T_Bind_Args>
		struct S_Function_Data<T_Fn,T_Bind_Args...> :
			S_Function_Data<T_Fn>
		{
			using bind_args = tuple_t<T_Bind_Args...>;
		};


		//仕様
		//クラスメソッドの型から、各種パラメータをセットする
		template<class T_CName, class T_RType, class ...T_Args>
		struct S_Function_Data<T_RType(T_CName::*)(T_Args...)> :
			S_Function_Data<>
		{
			using function = T_RType(T_CName::*)(T_Args...);

			using c_name = T_CName;

			using request = Request_Core<
				typename tuple_t<T_Args...>::reverse,
				c_name>;

			using r_type = T_RType;
		};

		//仕様
		//静的関数の型から、各種パラメータをセットする
		template<class T_RType, class ...T_Args>
		struct S_Function_Data<T_RType(*)(T_Args...)> :
			S_Function_Data<>
		{
			using function = T_RType(*)(T_Args...);

			using request = Request_Core<
				typename tuple_t<T_Args...>::reverse,
			invalid_t
			>;

			using r_type = T_RType;
		};


		//仕様
		//親となる関数オブジェクトの型をセットする
		template<class ...T_Parts>
		struct S_Function_Data<Function<Function_Core<T_Parts...>>> :
			S_Function_Data<Function_Core<T_Parts...>>
		{};

		//仕様
		//親となる関数オブジェクトの型をセットする
		template<class ...T_Parts>
		struct S_Function_Data<Function_Core<T_Parts...>> :
			S_Function_Data<>
		{
			using function = Function_Core<T_Parts...>;

			using request = I_Request<I_Function_Single_Data>::type;
		};

		template<class ...T_Fns>
		struct S_Function_Data<tuple_t<T_Fns...>> :
			S_Function_Data<>
		{
			using function = tuple_t<T_Fns...>;

			using request = I_Request<I_Function_Single_Data>::type;
		};

		//仕様
		//関数オブジェクトの型でない場合、セットしない
		template<class T_Fn>
		struct S_Function_Data<T_Fn> :
			S_Function_Data<>
		{};


		//仕様
		//[Function_Core<>]を[ T_Fn_Parts...]の前に挿入し[S_Function_Data]に接続する
		template<class ...T_Fn_Parts>
		struct S_Function_Data_Access
		{
			using type = S_Function_Data<T_Fn_Parts...>;
		};


		using type = typename N_Tuple::I_Expand_Set<S_Function_Data_Access, T_Fn_Parts...>::type::type;


		//仕様
		//[TT_Action][t_parts_name]で要求する要素をT_Coreから抽出する
		//
		//テンプレート
		//[TT_Action]:第一引数にコア、第二引数に対して、コアの値で処理をする値
		//[t_parts_name]:要求するコアの要素名
		//
		//補足
		//[TT_Action]の第二引数は[T_Core]に複数の関数が纏められている場合、一つずつ処理をする
		template<template<class...>class TT_Action, N_Constexpr::String t_parts_name, class T_Core>
		struct I_Request
		{

			template<class T_Fn = typename T_Core::function,
				class T_request = typename U_Parts_Search_InnerType<t_parts_name, T_Fn>::type>
			struct S_Request
			{
				using type = TT_Action<T_Core, T_request>::type;
			};

			template<class T_Fn, class ...T_request>
			struct S_Request<T_Fn, tuple_t<T_request...>>
			{
				using type = tuple_t<typename S_Request<T_Fn, T_request>::type...>;
			};

			template<class ...T_Fns, class T_request>
			struct S_Request<Function_Core<tuple_t<T_Fns...>>, T_request>
			{
				using type = tuple_t<typename S_Request<T_Fns>::type...>;
			};

			using type = S_Request<>::type;

		};



		//仕様
		//バインド済み引数が無効の場合、[function]を無効値に変更する
		template<class T_Core, class T_Args_Chack = typename T_Core::request_args>
		struct S_is_Valid_Fn
		{
			using type = T_Core;
		};

		template<class T_Parent>
		struct S_is_Valid_Fn<T_Parent, invalid_t>
		{
			using type = invalid_t;
		};

	public:

		using function = type;

			//typename S_is_Valid_Fn<type>::type;
		
		//using request_args = type::request_args;
		
		//using request_pointer = type::request_pointer;
		
		//using bind_args = type::bind_args;
		
		//using c_name = type::c_name;

		//static constexpr size_t fn_count = type::fn_count;

	};

}

