/*!
 * Tuple_Apply_Class_Create.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once


#include"Tuple_Declare.h"

namespace quiet::N_Tuple::N_Apply
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

		
		template<size_t N,
			class T_Args_Number = N_Tuple::U_index_sequence<N>>
			struct S_Apply {};

		//仕様
		//要求する引数の数と供給する引数の数が一致しない場合、
		// 供給する型の数に合わせて、キャストする
		template<size_t N,size_t ...t_Args_Number>
		struct S_Apply<N, tuple_v<t_Args_Number...>>
		{
			template<class... T_Args>
			static constexpr auto Apply(T_Args&&... args)
			{
				return T{ static_cast<U_Element_t<t_Args_Number,tuple_t<T_Request_Args...>>>(args)... };
			}
		};

		//要求する引数の数と供給する引数の数が一致しない場合、
		template<class MT_Fn = T, class... T_Args>
			requires requires
		{
			requires sizeof...(T_Args) != sizeof...(T_Request_Args);
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return S_Apply<sizeof...(T_Args)>::Apply(std::forward<T_Args>(args)...);
		}

		//クラスを作成
		template<class MT_Fn = T, class... T_Args>
		constexpr auto Apply(T_Args&&... args)
		{
			return T{ static_cast<T_Request_Args>(args)... };
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