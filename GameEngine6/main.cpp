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
#include"FunctionMultiple_Helper.h"
#include"tuple_Helper.h"
#include"Function_Args.h"

#include"Parameter_Element.h"

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
	for (int i = static_cast<int>(p) + 1; i < path.size(); i++)
		r.push_back(path[i]);
	return r;
}


void H::Args_1(int a)
{
	C_OUT(a);
}

void H::Args_2(int a, int b)
{
	C_OUT(a);
	C_OUT(b);
}

void H::Args_3(int a, int b, int c)
{
	Args_2(a, b);
	C_OUT(c);
}

void H::Args_4(int a, int b, int c, int d)
{
	Args_3(a, b, c);
	C_OUT(d);

}

void H::Args_5(int a, int b, int c, int d, int e)
{
	Args_4(a, b, c, d);
	C_OUT(e);
}

void H::Args_6(int a, int b, int c, int d, int e, int f)
{
	Args_5(a, b, c, d, e);
	C_OUT(f);
}

void H::Args_7(int a, int b, int c, int d, int e, int f, int g)
{
	Args_6(a, b, c, d, e, f);
	C_OUT(g);
}




constexpr Function a1(&H::Args_7);
static FunctionMultiple aa2 = { a1,a1,3 };
int main()
{


	FUNCTION_MULTIPLE(AA, &H::Args_5, 1, 3, 4);

	static constexpr FunctionStatic<&H::Args_5, 3> aaa2;

	static constexpr FunctionStatic<aaa2,9> aaa3;

	FunctionMultipleStatic<
		&H::Args_5, 4, 4, 4,3
		//&H::Args_7, 7, 7, 7, 7, 7, 7, 7
	> bab;

	FunctionMultipleStatic<
		&H::Args_7,7,7,7,7,7,7,7,
		&H::Args_7,6,6,6,6,6,6,
		&H::Args_7,5,5,5,5,5,
		&H::Args_7,4,4,4,4,
		&H::Args_7,3,3,3,
		&H::Args_7,2,2,
		&H::Args_7,1,
		&H::Args_7
	> O;
	

	
		//Bind_Args_Num<0>;

	//aaa3.Execution(99, 33, 55);


	//N_Function::S_MethodData<decltype(aaa2),int>::ParentFn::
	//N_Function::IS_FunctionOperator_Static<aaa3>::Type
	//N_Function::S_MethodData<decltype(aaa2)



	//C_OUT(sizeof(aaa2));


	//Core<"Object"> o;

	//std::tuple<DECLT1(1, 3, 4, 2)> a;

	//using T = decltype(aaa3)::FunctionOperator;



	Function _1(&H::Args_4, 3, 2);


	//_1.classP = h;
	//_1();
	//constexpr Function a1(&H::Args_5, 5);

	Function a2(a1, 1);
	Function a3(a2, 2);
	Function a4(a3, 3);
	Function a5(a4, 4);
	Function a6(a5, 5);
	Function a7(a6, 6);
	Function a8(a7, 7);
	a8();
	//a3(3, 4, 5, 6, 7);
	//	a2(3,4);

		//Function a3(a2,1,3);

		//type_id(a3);

	Function ab(&H::Args_1);
	Function ab2(ab);


	FunctionMultiple aa1(
		a1, 7, 7, 7, 7, 7, 7, 7,
		a1, 6, 6, 6, 6, 6, 6
		, a1, 5, 5, 5, 5, 5
		, a1, 4, 4, 4, 4
		, a1, 3, 3, 3
		, a1, 2, 2
		, a1, 1
		, a1
	);

	C_OUT(sizeof(decltype(a8)));
	C_OUT(sizeof(decltype(aa1)));

	//aa1();
	//aa1(1);
	//aa1(2,2);
	//aa1(3,3,3);
	//aa1(4,4,4,4);
	//aa1(5,5,5,5,5);
	//aa1(6,6,6,6,6,6);
	//aa1(7,7,7,7,7,7,7);

		//5 3 1 0 2 4
	//aa2.Execution();

	//aa3(1, 2, 3, 4);

		//, decltype(a1),int, decltype(a1),int,int>::

	//constexpr FunctionMultiple aa2(a1,a1);
	//using T = decltype(aa1)::IS_MethodSearch<int>::S_MethodSearch<1,1>::Type::Type
		//:T;

	//using T = FunctionMultiple<std::tuple< decltype(a1), int, int, decltype(a1), int>>::IS_MethodSearch<>::Judge;
	//FunctionMultiple<decltype(a1), int, int, decltype(a1), int>::
	//aa1(9, 9, 9, 9);
	//aa1(9,9,9);
	//aa1(9,9);
	//aa1(9);
	//aa1();
	//TYPE_ID(T)
	//a2(7);
	//a3();

	return 0;

}
