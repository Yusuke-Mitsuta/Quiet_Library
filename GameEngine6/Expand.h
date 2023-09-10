#pragma once

#include<optional>
#include"Concept.h"

template<class ...T_Parameters>
struct S_Parameter;

template<class T_Zip>
struct S_Zip
{

};
template<>
struct S_Zip<int>
{
	using Type = S_Parameter<int, int, float>;
};

template<class T_Zip>
struct S_Expand
{
	using Type = typename S_Zip<T_Zip>::Type;
};

template<class T_Zip>
concept is_expand = requires
{
	typename S_Zip<T_Zip>::Type;
};
