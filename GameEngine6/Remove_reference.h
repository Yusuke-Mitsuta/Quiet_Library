#pragma once

#include<concepts>

namespace N_Type_Control
{
	//�d�l
	//�^[T]����Q�Ƃ�S�Ď��
	template<class T>
	struct remove_reference_all
	{
		using type = T;
	};

	template<class T>
	struct remove_reference_all<T&>
	{
		using type = remove_reference_all<T>::type;
	};

}

//�d�l
//�^[T]����Q�Ƃ�S�Ď��
template<class T>
using remove_reference_all_t = N_Type_Control::remove_reference_all<T>::type;

