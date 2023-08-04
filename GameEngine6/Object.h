#pragma once

#include"Core.h"
#include"Constexpr_String.h"
#include"Function_Static.h"

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

	static constexpr Function a = { &Test,3,4 };

	static S_MoveTupleInnerType<FunctionMultiple, std::tuple<decltype(&Test)>>::Type aaa;

	static constexpr FunctionMultipleStatic<&H::Args_3, 3, 5,&H::Message> b = {};

	//static constexpr FUNCTION_MULTIPLE(b, &Test)


	Core()
	{
		b.Execution("Object‚©‚ç‚¾‚æ[");
		b.Execution(3);
		//(this->*(obj.M))(3, 4);

		//b.E(2,4);
		
	}

};

