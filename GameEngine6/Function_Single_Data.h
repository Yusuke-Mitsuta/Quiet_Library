#pragma once

#include"Function_Core.h"
#include"Tuple.h"
#include"Concept.h"

#include"Function_Args_Chack.h"

template<not_is_invalid T_Fns>
class Function;


namespace N_Function
{

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
			using type = Function_Core<>;
		};

		//仕様
		//共通で使用するポインターの型をセットする
		template<class ...T_Result, class T_Dedicated_Point, class ...T_Fn_Parts>
			requires (std::is_class_v<T_Dedicated_Point>)
		struct S_Function_Data<Function_Core<T_Result...>, T_Dedicated_Point* , T_Fn_Parts...>
		{
			using type = S_Function_Data<Function_Core<T_Result...,
				Parts<"pointer", T_Dedicated_Point>>, T_Fn_Parts...>::type;
		};

		//仕様
		//引数の型をセットする
		template<class ...T_Result, class T_Fn, class ...T_Bind_Args>
		struct S_Function_Data<Function_Core<T_Result...>, T_Fn, T_Bind_Args...>
		{
			using type = S_Function_Data<
				Function_Core<T_Result...,
				Parts<"bind_args", tuple_t<T_Bind_Args...>>>,
				T_Fn>::type;
		};

		//仕様
		//クラスメソッドの型から、各種パラメータをセットする
		template<class ...T_Result, class T_CName, class T_RType, class ...T_Args>
		struct S_Function_Data<Function_Core<T_Result...>, T_RType(T_CName::*)(T_Args...)>
		{
			using fn = T_RType(T_CName::*)(T_Args...);

			using type = S_Function_Data<
				Function_Core<T_Result...,
				Parts<"function",
				Function_Core<Parts<"function", fn>,
				Parts<"request_args", typename tuple_t<T_Args...>::back>,
				Parts<"c_name", T_CName>,
				Parts<"request_pointer", T_CName>,
				Parts<"r_type", T_RType>>>
				>>::type;
		};

		//仕様
		//静的関数の型から、各種パラメータをセットする
		template<class ...T_Result, class T_RType, class ...T_Args>
		struct S_Function_Data<Function_Core<T_Result...>, T_RType(*)(T_Args...)>
		{
			using fn = T_RType(*)(T_Args...);

			using type = S_Function_Data<
				Function_Core<T_Result...,
				Parts<"function",
				Function_Core<Parts<"function", fn>,
				Parts<"request_args", typename tuple_t<T_Args...>::back>,
				Parts<"r_type", T_RType>>>
				>>::type;
		};

		//仕様
		//親となる関数オブジェクトの型をセットする
		template<class ...T_Result, class ...T_Parts>
		struct S_Function_Data<Function_Core<T_Result...>, Function<Function_Core<T_Parts...>>>
		{
			using type = S_Function_Data<
				Function_Core<T_Result...>, Function_Core<T_Parts...>>::type;
		};

		//仕様
		//親となる関数オブジェクトの型をセットする
		template<class ...T_Result, class ...T_Parts>
		struct S_Function_Data<Function_Core<T_Result...>,Function_Core<T_Parts...>>
		{
			using type = S_Function_Data<
				Function_Core<T_Result...,
				Parts<"function", Function_Core<T_Parts...>>
				>>::type;
		};

		//仕様
		//関数オブジェクトの型でない場合、セットしない
		template<class ...T_Result, class T_Fn>
		struct S_Function_Data<Function_Core<T_Result...>, T_Fn>
		{
			using type = Function_Core<>;
		};

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
		//要求する引数をコアから取得する
		//
		//補足
		//関数が纏められている場合、[tuple_t]で纏める
		template<class T_Core>
		struct I_Request_args
		{
			template<class T_Core, class T_Request_Args>
			struct S_Request_args
			{
				using type = T_Request_Args;
			};

			template<class ...T_Parts, N_Tuple::is_Tuple T_Request_Args>
				requires(not_is_invalid<typename U_Parts_Search_InnerType<"bind_args", Function_Core<T_Parts...>>::type>)
			struct S_Request_args<Function_Core<T_Parts...>, T_Request_Args>
			{
				using type = I_Function_Args_Chack<T_Request_Args, typename Function_Core<T_Parts...>::bind_args>::request_args;
			};

			using type = I_Request<S_Request_args, "request_args",T_Core>::type;
		};

		//仕様
		//要求するポインターの型をコアから取得し、
		// 互換性のあるポインターがセットされて入れば要求を取り消す
		//
		//補足
		//関数が纏められている場合、[tuple_t]で纏める
		//必要でない場合、[invalid_t]が返る
		template<class T_Core>
		struct I_Request_pointer
		{
			template<class T_Core, class T_Request_pointer= typename U_Parts_Search_InnerType<"request_pointer", T_Core>::type>
			struct S_Request_pointer
			{
				using type = T_Request_pointer;
			};

			template< class ...T_Parts, class T_Request_pointer>
				requires(convertible_to<typename U_Parts_Search_InnerType<"pointer", Function_Core<T_Parts...>>::type, T_Request_pointer>)
			struct S_Request_pointer<Function_Core<T_Parts...>, T_Request_pointer>
			{
				using type = invalid_t;
			};


			using type = I_Request<S_Request_pointer,"request_pointer",T_Core>::type;

		};


		//仕様
		//要求するポインターの型と引数の型をセットする
		template<class ...T_Result>
		struct S_Function_Data<Function_Core<T_Result...>>
		{
			using core = Function_Core<T_Result...>;

			using type =
				Function_Core<T_Result...,
				Parts<"request_args", typename I_Request_args<core>::type>,
				Parts<"request_pointer", typename I_Request_pointer<core>::type>
				>;
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

		//仕様
		//[Function_Core<>]を[ T_Fn_Parts...]の前に挿入し[S_Function_Data]に接続する
		template<class ...T_Fn_Parts>
		struct S_Function_Data_Access
		{
			using type = S_Function_Data<Function_Core<>, T_Fn_Parts...>::type;
		};

	public:

		using type = typename N_Tuple::I_Expand_Set<S_Function_Data_Access, T_Fn_Parts...>::type::type;

		using function = type::function;
			//typename S_is_Valid_Fn<type>::type;
		
		using request_args = type::request_args;
		
		using request_pointer = type::request_pointer;
		
		using bind_args = type::bind_args;
		
		using c_name = type::c_name;

		//static constexpr size_t fn_count = type::fn_count;

	};

}

