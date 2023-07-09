#pragma once
#include"Function.h"


template<class ...T_Args>
class MultipleFunction
{
public:


//	template<class ...MT_Fns>
	//constexpr ClassFunction(MT_Fns...) {}


};

template<class T, class ...T_Args>
class MultipleFunction<T*,T_Args...>
{
public:
	
	T* p;

	//template<class MT, class ...MT_Fns>
	//constexpr ClassFunction(MT* p, MT_Fns...) {}


};


