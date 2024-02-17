#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple::N_Apply
{
	//仕様
	//配列に要素を追加する。
	template<class T>
	struct S_Array_Create
	{};

	template<class T,size_t N>
	struct S_Array_Create<T[N]>
	{
		T* array_p;

		constexpr S_Array_Create(T* set_array_p) :
			array_p(set_array_p) {}


		//配列への複数の要素を追加
		template<size_t I = 0, class T_Flont_Args, class... T_Args>
			requires requires
		{
			requires I < N;
		}
		constexpr void Apply(T_Flont_Args&& flont_Args, T_Args&&... args)
		{
			*array_p = static_cast<T>(std::forward<T_Flont_Args>(flont_Args));
			++array_p;
			this->Apply<I + 1>(std::forward<T_Args>(args)...);
		}

		//配列へ追加する要素がなくなった場合、デフォルトで構築する
		template<size_t I = 0>
			requires requires
		{
			T{};
			requires I < N;
		}
		constexpr void Apply()
		{
			*array_p = {};
			++array_p;
			this->Apply<I + 1>();
		}

		template<size_t I = 0>
		constexpr void Apply()
		{}
	};
}