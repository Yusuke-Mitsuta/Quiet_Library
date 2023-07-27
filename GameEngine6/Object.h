#pragma once

#include"Core.h"
#include"Constexpr_String.h"

template<>
class Core<"Object"> :
	public Core<"Core">
{
public:

	void Test(int a, int b)
	{
		C_OUT("TEST");
	}

	//static constexpr Function a = {&Test,3,4};

	//static constexpr S_MoveTupleInnerType<FunctionMultiple, std::tuple<decltype(&Test)>>::Type aaa = {&Test};


	//FUNCTION_MULTIPLE(b, &Test)

	Core()
	{
		
	}

};

