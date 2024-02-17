#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple::N_Apply
{
	//�d�l
	//�z��ɗv�f��ǉ�����B
	template<class T>
	struct S_Array_Create
	{};

	template<class T,size_t N>
	struct S_Array_Create<T[N]>
	{
		T* array_p;

		constexpr S_Array_Create(T* set_array_p) :
			array_p(set_array_p) {}


		//�z��ւ̕����̗v�f��ǉ�
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

		//�z��֒ǉ�����v�f���Ȃ��Ȃ����ꍇ�A�f�t�H���g�ō\�z����
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