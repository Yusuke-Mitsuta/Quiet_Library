#pragma once

#include<concepts>

namespace N_Type_Control
{
	//仕様
	//型[T]から参照を全て取る
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

//仕様
//型[T]から参照を全て取る
template<class T>
using remove_reference_all_t = N_Type_Control::remove_reference_all<T>::type;

