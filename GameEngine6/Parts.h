#pragma once
#include"Parts_Search.h"

template<N_Constexpr::String t_Parts_Name, class T>
struct Parts :
	public T
{
	using type = T;
};