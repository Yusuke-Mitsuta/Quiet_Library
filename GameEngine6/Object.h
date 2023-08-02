#pragma once

#include"Core.h"
#include"Constexpr_String.h"
#include"Function_Single_Static.h"

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



	//static constexpr FUNCTION_MULTIPLE(b, &Test)


	Core()
	{
		
	}

};
