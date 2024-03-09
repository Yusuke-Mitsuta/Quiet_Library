/*!
 * Tuple_Apply_Fn.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple::N_Apply
{


	//仕様
	//関数オブジェクトとポインターを取得し、
	//関数オブジェクトによって、適切にポインターを使用する。
	// 
	//補足
	//[T_Fn_Action]が
	//動的関数の場合：ポインターを使用し関数ポインターにアクセスする
	//Functionの場合：ポインターの要求の有無によって使用を判断する
	//静的関数の場合：ポインターを使用せず関数ポインターにアクセスする
	template<class T_Fn_Action, class T_pointer>
	struct S_Fn_Action
	{
		T_Fn_Action fn;

		T_pointer* p;

		constexpr S_Fn_Action(T_Fn_Action set_fn, T_pointer* set_pointer) :
			fn(set_fn), p(set_pointer) {}

		constexpr S_Fn_Action(T_Fn_Action set_fn, T_pointer set_pointer) :
			fn(set_fn), p(&invalid) {}

		//関数実行の際に互換性のある型から要求される型へキャストする
		struct S_Cast_Args
		{
			template<class T_RType, class ...T_Request_Args, class... T_Args>
			static constexpr auto Apply(T_RType(*fn)(T_Request_Args...), T_Args&&... args)
			{
				return fn(static_cast<T_Request_Args>(args)...);
			}

			template<class T_CName, class T_RType, class ...T_Requet_Args, is_invalid_not MT_pointer, class... T_Args>
			static constexpr auto Apply(T_RType(T_CName::*fn)(T_Requet_Args...),MT_pointer* p,T_Args&&... args)
			{
				return (p->*fn)(static_cast<T_Requet_Args>(args)...);
			}

		};

		//ポインターを使用せず関数オブジェクトにアクセスする
		template<class MT_Fn = T_Fn_Action, is_invalid MT_pointer = T_pointer, class... T_Args>
			requires requires
		{
			requires !std::is_class_v<MT_Fn>;
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return S_Cast_Args::Apply(fn, std::forward<T_Args>(args)...);
		}

		//ポインターを使用せず、[Function]にアクセスする
		template<class MT_Fn = T_Fn_Action, is_invalid MT_pointer = T_pointer, class... T_Args>
			requires requires
		{
			requires std::is_class_v<MT_Fn>;
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return fn(args...);
		}

		//関数オブジェクトが[Function*]の場合
		template<class MT_Fn = T_Fn_Action, is_invalid MT_pointer = T_pointer, class... T_Args>
			requires requires
		{
			requires std::is_pointer_v<MT_Fn>;
			requires std::is_class_v<std::remove_pointer_t<MT_Fn>>;
			requires !std::is_member_function_pointer_v<MT_Fn>;
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return fn->operator()(args...);
		}

		//ポインターを使用し関数オブジェクトにアクセスする
		template<class MT_Fn = T_Fn_Action, is_invalid_not MT_pointer = T_pointer, class... T_Args>
			requires requires
		{
			requires std::is_member_function_pointer_v<MT_Fn>;
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return S_Cast_Args::Apply(fn,p,std::forward<T_Args>(args)...);
		}

		//ポインターを引数に追加し、[Function]にアクセスする
		template<class MT_Fn = T_Fn_Action, is_invalid_not MT_pointer = T_pointer, class... T_Args>
			requires requires
		{
			requires same_as_template_type<MT_Fn, Function>;
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return fn(p, args...);
		}

	};
}