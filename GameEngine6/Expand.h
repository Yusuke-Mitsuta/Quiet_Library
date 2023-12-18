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

template<class T_Zip, size_t number>
struct S_Zip_Search;



template<class T_Zip, size_t number = 0>
	requires requires
{
	requires number == 0;
} ||
	requires
{
	requires number != 0;
	requires not_is_invalid<typename S_Zip_Search<T_Zip, number>::type>;
}
struct S_Zipa
{
	using type = invalid_t;
};

template<class T_Zip,size_t number>
struct S_Zip_Search
{
	using type = S_Zipa<T_Zip, number - 1>::type;
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
