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
#include"MethodData.h"
#include<type_traits>
#include"Quick_Sort.h"

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
struct H2:
	public H
{
	static void Args_H2() {
		C_OUT("test");
	}
};
struct H3 :
	public H2
{

};

H2* h2 = new H2();
H3* h3 = new H3();
auto Ho()
{




	N_Function::Function_Single mt(h2, &H::Args_7, 7, 6, 5, 4, 3, 2);


	N_Function::Function_Single mt2(mt, 3);
	return mt2;
}


template<int n>
struct N
{
	static constexpr int Num = n;
};

template<class T,class T2>
struct N_Sort
{
	static constexpr bool Judge = (T::Num < T2::Num);
};

int main()
{
	TYPE_ID(&H2::Args_H2);
	TYPE_ID(&H2::Args_2);

	N_Function::Function_Single ttt(&H2::Args_H2);

	auto s = &H2::Args_H2;

	s();

	using T = S_Parameter<int, int, char>;

	using Sort = IS_Quick_Sort<N_Sort, S_Parameter<N<2>, N<5>, N<7>>>::Type::Type;

	TYPE_ID(Sort);

	T aaa(2, 5, 'a');

	T aaaa(3, 6, 'b');

	S_Parameter ma(aaa, aaaa);
	S_Parameter maa(aaa, aaaa,ma,ma,aaaa);

	IS_Remove_Parameters<T, 2,1> ;
	//using t = U_Element_t<2, int, int, char, int, int, char>;

	//IS_Parameter_Element_Type<1,int, float, char>::Next::Next::

	//Function::Single mt(&H::Args_5, 1,3,54,2);

	//TYPE ab;

	//N_Function::Function_Single mt2(h,&H::Args_3);
	//using T = N_Function::IS_Function_Single_Helper<H*, decltype(&H::Args_3), int>::Judge;
	//TYPE_ID(T);


	auto mt2 = Ho();

	//mt(1, 2, 3);
	mt2();

	//N_Function::S_MethodData<decltype(&H::Args_3),int>::
	//mt2(2, 4);
	//auto mt3= AUTO();

	//mt3();

	//Function::Single mt2(ab.mt);
	//mt2();
//	mt2();


	C_OUT(sizeof(mt2));
	//C_OUT(sizeof(ab));



	//for (int i = 0; i < ma.Size; i++)
	//{
	//	C_OUT(ma[i]);
	//}
	
	




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
