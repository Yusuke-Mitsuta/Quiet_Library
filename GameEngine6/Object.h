#pragma once

#include"Core.h"
#include"Constexpr_String.h"

template<>
class Core<"Object">:
	public Core<"Core">
{
public:

	void Test(int a,int b)
	{
		C_OUT("TEST");
	}

	static constexpr Function a = {&Test,3,4 };

	static constexpr FunctionMultiple b ={&Test,3,45 };

	Core()
	{
	}

};