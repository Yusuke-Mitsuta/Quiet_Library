#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple::N_Apply
{
	//�d�l
	//�z��ɗv�f��ǉ�����B
	template<class T>
	struct S_Array_Create
	{
		T* array_p;

		constexpr S_Array_Create(T* set_array_p) :
			array_p(set_array_p) {}


		//�z��ւ̕����̗v�f��ǉ�
		template<class T_Flont_Args, class... T_Args>
		constexpr void operator()(T_Flont_Args&& flont_Args, T_Args&&... args)
		{
			operator()(std::forward<T_Flont_Args>(flont_Args));
			++array_p;
			this->operator()(std::forward<T_Args>(args)...);
		}

		//�z��ւ̗v�f�ǉ�
		template<class T_Flont_Args>
		constexpr void operator()(T_Flont_Args&& flont_Args)
		{
			*array_p = static_cast<T>(flont_Args);
		}

		constexpr void operator()()
		{
			std::cout << "����[";
		}
	};
}