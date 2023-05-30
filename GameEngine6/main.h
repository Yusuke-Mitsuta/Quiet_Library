#pragma once


#include"Constexpr_Array.h"
#include"Constexpr_String.h"

template<N_Constexpr::String str>
class T
{

public:
	int a;
};

template<>
class T<"aiu">
{
public:
	int aa;
};