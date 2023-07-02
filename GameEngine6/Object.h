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

	//Message<"Test">::Receive<decltype(&Core::Test)> a = {&Core::Test, this};

	Core()
	{

	}

};