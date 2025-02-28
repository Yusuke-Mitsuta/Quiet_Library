/*!
 * Tuple_Apply.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Apply_Action.h"

namespace N_Function
{
	template<class T_Fn, class T_Set_Types>
	struct I_Function_Operator_Search;
}

namespace quiet::N_Tuple
{

	//仕様
	//[Function< ... >()]を呼び出す
	template<class T_Fn, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN_OBJECT>;
		requires is_invalid_not<typename N_Function::I_Function_Operator_Search<T_Fn, tuple_t<T_Args...>>::type>;
	}
	static constexpr auto Apply(T_Fn&& fn, T_Args&&... args)
	{
		return std::forward<T_Fn>(fn)->operator()(std::forward<T_Args>(args)...);
	}

	//仕様
	//関数[fn]に対して、
	// [args...]の中身を適切に展開し、実行する
	template<class T_Fn, class ...T_Args>
		requires requires(T_Fn fn,T_Args... args)
	{
		requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>;
		requires N_Apply::Chack<T_Fn, T_Args...>();
	}
	static constexpr auto Apply(T_Fn&& fn, T_Args&&... args)
	{
		return I_Apply_Action<T_Fn, T_Args...>::Apply(
			std::forward<T_Fn>(fn),
			std::forward<T_Args>(args)...);
	}


	//仕様
	//関数[fn]に対して、
	//ポインタ[p]を用いて、[args...]の中身を適切に展開し、実行する
	template<class T_Fn, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>;
		requires N_Apply::Chack<T_Fn, T_Args...>();
	}
	static constexpr auto Apply(T_Fn&& fn, auto* p, T_Args&&... args)
	{
		return I_Apply_Action<T_Fn, T_Args...>::Apply(
			std::forward<T_Fn>(fn),p,
			std::forward<T_Args>(args)...);
	}


	//仕様
	//クラス[T_Request_Order]のコンストラクタに対して、
	//[args...]の中身を適切に展開し、実行する
	template<class T, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T,N_Apply::E_Type::CLASS>;
		requires N_Apply::Chack<T, T_Args...>();
	}
	static constexpr auto Apply(T_Args&&... args)
	{
		return I_Apply_Action<T, T_Args...>::Apply(
			std::forward<T_Args>(args)...);
	};

	//仕様
	//クラス[T_Request_Order]のコンストラクタに対して、
	//[args...]の中身を適切に展開し、Newする
	template<class T, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T, N_Apply::E_Type::CLASS_NEW>;
		requires N_Apply::Chack<T, T_Args...>();
	}
	static constexpr auto Apply(T_Args&&... args)
	{
		return I_Apply_Action<T, T_Args...>::Apply(
			std::forward<T_Args>(args)...);
	}


	//仕様
	//配列型の参照に[array_ref]に[args...]の中身を適切に展開し、追加する。
	// 
	// 引数
	// [array_ref]：要素を格納する配列の参照
	// [args...]：tupleにより適切に変換され、配列に格納する変数
	template<class T_Array, size_t N, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T_Array[N], N_Apply::E_Type::ARRAY>;
		requires N_Apply::Chack<T_Array, T_Args...>();
	}
	static constexpr void Apply(T_Array(&array_ref)[N], T_Args&&... args)
	{
		I_Apply_Action<T_Array[N],T_Args...>::Apply(&array_ref,std::forward<T_Args>(args)...);
	}

	//仕様
	//特定の要素を指す、配列型のポインター[array_p]に[set_Num]の数だけ[args...]の中身を適切に展開し、追加する。
	//
	//テンプレート
	//[set_Num]：要素を追加する総数
	// 
	// 引数
	// [array_p]：配列の特定の要素を指すポインター
	// [args...]：tupleにより適切に変換され、配列に格納する変数
	// 
	//補足
	// [array_p] について
	// [int n[5] ]という配列がある時
	// [int* p = &n[2]; ]pが特定の要素数(二番目)を指す事になる。
	template<size_t set_Num, class T_Array, class ...T_Args>
		requires requires
	{
		requires N_Apply::is_apply_type<T_Array[set_Num], N_Apply::E_Type::ARRAY>;
		requires N_Apply::Chack<T_Array[set_Num], T_Args...>();
	}
	static constexpr void Apply(T_Array* array_p, T_Args&&... args)
	{
		I_Apply_Action<T_Array[set_Num], T_Args...>::Apply(array_p,
			std::forward<T_Args>(args)...);
	}

}

namespace quiet
{
	using N_Tuple::Apply;
}
