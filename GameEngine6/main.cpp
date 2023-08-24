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
#include"Parameter.h"
#include<list>

#include<type_traits>

#include<tuple>
#include<optional>
#include<utility>

#include"Function.h"

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

struct TYPE
{
	N_Function::Function_Single<decltype(&H::Args_5),int,int,int,int> mt = {h,&H::Args_5, 1, 3, 54,4};
};

auto AUTO()
{

	TYPE* ab=new TYPE();
	TYPE abb;
	N_Function::Function_Single mt2(abb.mt, 3);
	return mt2;
}


int main()
{

	using T = S_Parameter<int, int, char>;


	T aaa(2, 5, 'a');

	T aaaa(3, 6, 'b');

	S_Parameter ma(aaa, aaaa);
	S_Parameter maa(aaa, aaaa,ma,ma,aaaa);

	using t = S_Parameter_Element_t<2, int, int, char, int, int, char>;

	//IS_Parameter_Element_Type<1,int, float, char>::Next::Next::

	//Function::Single mt(&H::Args_5, 1,3,54,2);

	TYPE ab;

	N_Function::Function_Single mt2(ab.mt,3);

	auto mt3= AUTO();

	mt3();

	//Function::Single mt2(ab.mt);
	//mt2();
//	mt2();

	int n = 5;
	int* np = new int(3);
	int& nn = *np;
	int& nnp = *np;


	C_OUT(sizeof(mt2));
	C_OUT(sizeof(ab));

	C_OUT(ma.Size);
	C_OUT(aaa.Size);
	C_OUT(maa.Size);


	//for (int i = 0; i < ma.Size; i++)
	//{
	//	C_OUT(ma[i]);
	//}
	
	using TT = S_Parameter_Element_t<1, T>;
	




	//Function::Single b(&H::Args_2, 1);
	//Function::Single c(b,6);
	//
	////c();
	//static constexpr Function::Single_Static<&H::Args_2, 1> bb;

	//Function::Single_Static<bb,2> cc;
	//cc();

	
	
	//
	//static constinit auto BB = Function::Create<&H::Args_4, 9999>();
	//static constexpr N_Function::Function_Single_Static<&H::Args_3,1> aa = {};

	//static constexpr N_Function::Function_Multiple_Static<aa,aa,2,aa,2,3> aa = {};


	//static constexpr N_Function::Function_Single_Static<aa, 2> aaa = {};


	//


	//

	//auto B = Function::Create<&H::Args_2, 3, 4, &H::Args_2, 3>();

	//B(3);
	//


	//Function::Multiple a(&H::Args_3, 1, 2, &H::Args_3, 1);

	//a(33,2);
	//Function::Single b(&H::Args_3, 1, 2);
	_CrtDumpMemoryLeaks();
	return 0;

}
