#pragma once

#include<optional>
#include"Concept.h"

template<class T,unsigned int _Index>
struct Tuple_Element
{
	using Type = T;
};



template<class T_Zip>
struct S_Zip
{
};


template<class T_Zip>
struct S_Expand
{
	using type = S_Zip<T_Zip>::type;
};

template<class T_Zip>
concept is_expand = requires
{
	typename S_Zip<T_Zip>::type;
};
