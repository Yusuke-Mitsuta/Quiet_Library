#include"main.h"
#include<iostream>
#include"Constexpr_Array.h"
#include"Constexpr_String.h"
#include"Game_Engine.h"
#include"Object.h"
#include"Args_Type.h"
#include"Game_Object.h"
#include"Scene.h"
#include"Manager_Scene.h"
#include"Timer.h"
#include"tuple_convertible_to.h"
#include<list>

#include"Message.h"
#include"Message_Receive.h"
#include"Function.h"
#include"Tuple_Unzip.h"
#include"FunctionMultiple.h"
#include<type_traits>

#include<tuple>
#include<optional>
#include<utility>
#include"Constexpr_Array.h"
#include"ClassFunction.h"
#include"Function_Bind_Fns.h"

constexpr std::string getLastPathComponent(std::string path) {
	std::string r;
	size_t p = 0;
	for (size_t i = path.size() - 1; i > 0; i--)
	{
		if (path[i] == '\\')
		{
			p = i; break;
		}
	}
	for (int i = p + 1; i < path.size(); i++)
		r.push_back(path[i]);
	return r;
}

struct H
{
	void Args_1(int a)
	{
		C_OUT(a);
	}

	void Args_2(int a,int b)
	{
		C_OUT(a);
		C_OUT(b);
	}

	void Args_3(int a, int b,int c)
	{
		Args_2(a, b);
		C_OUT(c);
	}

	void Args_4(int a, int b, int c,int d)
	{
		Args_3(a, b,c);
		C_OUT(d);

	}

	void Args_5(int a, int b, int c, int d,int e)
	{
		Args_4(a, b,c,d);
		C_OUT(e);
	}
};

int main()
{
	H* h = new H();

	Function _1(&H::Args_1, 3);
	_1.classP = h;
	_1();
	Function a1(&H::Args_5, 5);
	a1.classP = h;
	type_id(a1)
	Function a2(a1,4);
	Function a3(a2,1);


	FunctionMultiple aa1(a1,a1,1,a1,2,2,a1,3,3,3,a1,4,4,4,4);
	//using T = decltype(aa1)::IS_MethodSearch<int>::S_MethodSearch<1,1>::Type::Type
		//:T;
		
	//using T = FunctionMultiple<std::tuple< decltype(a1), int, int, decltype(a1), int>>::IS_MethodSearch<>::Judge;
	//FunctionMultiple<decltype(a1), int, int, decltype(a1), int>::
	aa1(9, 9, 9, 9);
	aa1(9,9,9);
	aa1(9,9);
	aa1(9);
	aa1();
	//TYPE_ID(T)
	//a2(7);
	//a3();

	return 0;

}
