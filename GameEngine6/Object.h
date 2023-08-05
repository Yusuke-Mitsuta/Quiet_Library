#pragma once

#include"Core.h"
#include"Constexpr_String.h"
#include"Function.h"

template<>
class Core<"Object"> :
	public Core<"Core">
{
public:

	void Test(int a, int b)
	{
		C_OUT("TEST");
		C_OUT(a);
		C_OUT(b);
	}

	static constexpr auto TEST = Function::Create<&H::Args_3, 4, 3, 2, &H::Args_3, 3>();

	Core()
	{
		TEST.Execution(3, 4);
	}

};
