#pragma once

#include"Tuple.h"

template<class T>
struct is_calculation_C:
	std::false_type {};

template<class T>
	requires requires(T t)
{
	{std::get<std::tuple_size_v<T> -1>(t)};
}
struct is_calculation_C<T> :
	std::true_type {};

template<class T>
concept is_calculation = is_calculation_C<T>::value;

template<is_calculation T_Left,class T_Right>
T_Left operator+(const T_Left& l, const T_Right r)
{

}