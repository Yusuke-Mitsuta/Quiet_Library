#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Type.h"
#include<array>

namespace N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	template<class T_Fn, class T_Set_Types>
	struct I_Function_Operator_Search;
};

template<class _Ty1, size_t N>
class Array;

namespace N_Tuple::N_Apply
{
	//仕様
	//関数オブジェクトの引数とポインターの型を取得する.
	// 関数オブジェクト内に関数オブジェクトが複数内包されている場合、
	// 　一番初めに引数と互換性があったものが呼ばれる。
	template<class T,class ...T_Set_Types>
	struct I_Request
	{

		template<class T=T,E_Type t_type = Select_Type_v<T>>
		struct S_Request
		{
			using args = invalid_t;
			using pointer = invalid_t;
		};

		template<class T>
		struct S_Request<T,E_Type::CLASS>
		{
			using args = tuple_t<T>;
			using pointer = invalid_t;
		};

		template<class T>
			requires is_invalid_not<typename S_Parameter<T>::tuple>
		struct S_Request<T, E_Type::CLASS>
		{
			using args = S_Parameter<T>::tuple;
			using pointer = invalid_t;
		};

		template<class T>
		struct S_Request<T,E_Type::CLASS_NEW>:
			S_Request<T,E_Type::CLASS>
		{};

		template<class T,size_t N>
		struct S_Request<T[N], E_Type::ARRAY>
		{
			using args = U_Repeat_Multiple<T, N>;
			using pointer = invalid_t;
		};

		//仕様
		//関数オブジェクトの引数とポインターの型を取得する。
		template<class T>
		struct S_Request<T,E_Type::FN>
		{
			using fn_core = N_Function::Function_Core<T>;
			using args = fn_core::request_args;
			using pointer = fn_core::request_pointer;
		};

		//仕様
		// 関数オブジェクト内に関数オブジェクトが複数内包されている場合、
		// 　一番初めに引数と互換性があったものが呼ばれる。
		template<class ...T_Parts>
		struct S_Request<Function<T_Parts...>,E_Type::FN>
		{
			using operator_search = N_Function::I_Function_Operator_Search<T, tuple_t<T_Set_Types...>>::type;
			using args = U_Select<1, operator_search>::back;
			using pointer = U_Select<2, operator_search>;
		};

		using args = S_Request<>::args;

		using pointer = S_Request<>::pointer;

	};
}