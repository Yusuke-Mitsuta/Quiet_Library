#pragma once

#include"Tuple.h"
#include"Concept.h"

template<class T_Flont_Parts, class ...T_Parts>
class Function;

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	//仕様
	//関数オブジェクトの型に対して、続く引数の型が有効か判定する。
	//
	//テンプレート
	//[T_Fn_Parts...]::
	// 第一引数は第二引数の呼び出しに使用するクラスポインターの型である。クラスポインターの型を判定しない場合は指定不要である。静的メソッド、クラスポインターの型を指定済み、の場合は指定不可である。
	// 第二引数は関数の型、若しくは、引数をbindした型[Function_Core],[Method_Core]とする
	// 第三引数以降は、第二引数の関数オブジェクトの引数に指定する型リスト
	template<class ...T_Fn_Parts>
	struct I_Function_Base_Data
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

			using r_type = T_RType;
		};

		//仕様
		//静的関数の型から、各種パラメータをセットする
		template<class T_RType, class ...T_Args>
		struct S_Function_Data<T_RType(*)(T_Args...)> :
			S_Function_Data<>
		{
			using function = T_RType(*)(T_Args...);

			using r_type = T_RType;
		};


		//仕様
		//親となる関数オブジェクトの型をセットする
		template<class ...T_Parts>
		struct S_Function_Data<Function<T_Parts...>> 
			:S_Function_Data<typename I_Function_Multiple_Helper<T_Parts...>::type>
		{


		};

		

		//仕様
		//親となる関数オブジェクトの型をセットする
		template<class ...T_Parts>
		struct S_Function_Data<Function_Core<T_Parts...>> :
			S_Function_Data<>
		{
			using function = Function_Core<T_Parts...>;
		};

		template<class ...T_Fns>
		struct S_Function_Data<tuple_t<T_Fns...>> :
			S_Function_Data<>
		{
			using function = tuple_t<T_Fns...>;
		
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


	public:

		using type = typename N_Tuple::I_Expand_Set<S_Function_Data_Access, T_Fn_Parts...>::type::type;

	};

}

