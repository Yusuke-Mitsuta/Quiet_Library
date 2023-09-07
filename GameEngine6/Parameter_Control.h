#pragma once

#include"Parameter_Element.h"
#include"Parameter_Insert.h"
#include"Parameter_Remove.h"
#include"Parameter_Change.h"
#include"Parameter_Get.h"
#include"Parameter_Merge.h"

template<int n>
struct N
{
	static constexpr int Num = n;
};

template<class T, class T2>
struct N_Sort
{
	static constexpr bool Judge = (T::Num < T2::Num);
};