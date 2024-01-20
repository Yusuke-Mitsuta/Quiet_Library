#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple::N_Apply
{
	//仕様
	//配列に要素を追加する。
	template<class T>
	struct S_Array_Create
	{
		T* array_p;

		constexpr S_Array_Create(T* set_array_p) :
			array_p(set_array_p) {}


		//配列への複数の要素を追加
		template<class T_Flont_Args, class... T_Args>
		constexpr void operator()(T_Flont_Args&& flont_Args, T_Args&&... args)
		{
			operator()(std::forward<T_Flont_Args>(flont_Args));
			++array_p;
			this->operator()(std::forward<T_Args>(args)...);
		}

		//配列への要素追加
		template<class T_Flont_Args>
		constexpr void operator()(T_Flont_Args&& flont_Args)
		{
			*array_p = static_cast<T>(flont_Args);
		}

		constexpr void operator()()
		{
			std::cout << "えらー";
		}
	};
}