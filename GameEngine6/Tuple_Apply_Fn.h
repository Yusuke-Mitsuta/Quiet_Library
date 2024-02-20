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


		//ポインターを使用せず関数オブジェクトにアクセスする
		template<class MT_Fn = T_Fn_Action, is_invalid MT_pointer = T_pointer, class... T_Args>
		constexpr auto Apply(T_Args&&... args)
		{
			return fn(args...);
		}

		//ポインターを使用し関数オブジェクトにアクセスする
		template<class MT_Fn = T_Fn_Action, is_invalid_not MT_pointer = T_pointer, class... T_Args>
			requires requires
		{
			requires std::is_member_function_pointer_v<MT_Fn>;
		}
		constexpr auto Apply(T_Args&&... args)
		{
			return (p->*fn)(args...);
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