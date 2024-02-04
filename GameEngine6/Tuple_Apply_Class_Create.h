#pragma once


#include"Tuple_Declare.h"

namespace N_Tuple::N_Apply
{
	//仕様
	//生成するクラス[T_Fn]型の変数を生成する。
	// [T_Fn*]の場合はインスタンス生成を実施する。
	template<class T, class T_Request_Args = typename S_Parameter<T>::tuple>
	struct S_Class_Create {};

	template<class T, class ...T_Request_Args>
	struct S_Class_Create<T,tuple_t<T_Request_Args...>>
	{
		constexpr S_Class_Create() {}

		//クラスの生成
		template<class MT_Fn = T, class... T_Args>
		constexpr auto Apply(T_Args&&... args)
		{
			return T{static_cast<T_Request_Args>(args)... };

		}


		//クラスのインスタンス生成
		template<class MT_Fn = T, class... T_Args>
			requires requires
		{
			requires is_pointer<MT_Fn>;
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return new std::remove_pointer_t<T>{ args... };
		}

	};
}