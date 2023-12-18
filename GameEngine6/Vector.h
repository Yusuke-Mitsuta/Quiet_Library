#pragma once

#include"Expand.h"
#include"Tuple.h"

template<class X,class Y,class Z>
struct Vector3
{

	Vector3(X x, Y y,Z z)
	{

	}
};

template<class X, class Y, class Z>
struct S_Zip<Vector3<X, Y, Z>>
{
	using type = tuple_t<X, Y, Z>;
};
