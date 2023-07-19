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

std::string getLastPathComponent(std::string path) {
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

class H
{
public:

	void Hoge()
	{
		C_OUT('aa');
	//	C_OUT(b); 
	}

	//template<class C_Name, class R_Type, class ...T_Args>
	//template<class T>
	void Hogege( void(H::*P)()) 
	{
		//TYPE_ID(P)
	}

	void Hoge4(int a)
	{
	}


	void Hoge3(int a, int b)
	{
		C_OUT('b');
	}


	void Hoge1(int a)
	{
		C_OUT('a');

	}
	void Hoge5(int a,int b,int c,int d,int e)
	{
		C_OUT(a);
		C_OUT(b);
		C_OUT(c);
		C_OUT(d);
		C_OUT(e);

	}



};
template<class T, class U>
void Hoge3(T a, U b)
{
	//C_OUT(a); 
//	C_OUT(b); 
}

template<class _Flom, class _To>
	requires tuple_back_part_convertible_to<_Flom, _To>
void HHH()
{
}


template<class ...T>
class Ho
{

public:

	template<class ...U>
	Ho(U&&... num)
	{
		C_OUT(num);
		type_id(num);
	}
};
template<class ...U>
Ho(U&&... a) -> Ho<U&&...>;

template<class T>
using Fn = Function<std::tuple<T, H>>;

int main()
{
	//TYPE_ID(decltype(&H::Hoge3));
	std::tuple<int, int> Int(3,7);
	std::tuple<float,char> Intt(3,'8');
	std::tuple abcd(Int,Intt);

	//HHH<std::tuple<int, int>, std::tuple<int, int>>();

	//Function<decltype(&H::Hoge3), int, int, int,int> b;
	
	std::tuple m(&H::Hoge3, 13,30);

	int i = 9;

	//N_Function::IS_BindFns<decltype(&H::Hoge3),int,int,int>::Judge
	//FunctionMultiple ff1(&H::Hoge3, 22,3,&H::Hoge);

	Function f0(&H::Hoge3, 13,3);
	Function f1(m);
	Function f2(&H::Hoge4, 1);
	Function f3(&H::Hoge);
	//constexpr int aa =
		//N_Function::IS_BindFns<decltype(&H::Hoge), decltype(&H::Hoge3), int, int>::Type;

//	N_Function::IS_BindFn<decltype(&H::Hoge3), int>::Type::Judge


//N_Function::IS_BindFns<decltype(&H::Hoge), decltype(&H::Hoge3), int, int, int>::Type
	//C_OUT(typeid(
	//IS_tuple_convertible_to<std::tuple<int,int,int,int>,std::tuple<int,int>>::BackPart::value).nam//e()
		//int).name()

	//bool bo = IS_tuple_convertible_to<std::tuple<int, int>, std::tuple<int, int, int>>::BackPart::value;
	

	//N_Function::IS_BindFn<decltype(&H::Hoge3), int, int, int>::Type::Judge;

	/*C_OUT(typeid(
		N_Function::IS_BindFns<
		decltype(&H::Hoge3), int, int,
		decltype(&H::Hoge),0
		decltype(&H::Hoge3), int,int,int

		>::Type
	).name());*/


	FunctionMultiple aaa(f0,f2);

	//auto NNN = IS_TupleUnzip<int, int>::I_TupleUnzip(2, 1);

	//Function fn(&H::Hoge3, 2, 7);
	
	//N_Function::IS_BindFn<decltype(&H::Hoge3), int, int>::Type::FnType

	//C_OUT(typeid(decltype(NNN)).name())
			//N_Function::IS_BindFn<decltype(&H::Hoge3), int, int>::Type::FnType).name()

	
	//HHH<std::tuple<int, int,int>, std::tuple<int, int>>();


	//IS_tuple_convertible_to<std::tuple<int, int,int>, std:


	IS_TupleUnzip t(abcd, abcd);

	type_id(t.tuple);
	std::tuple  tu(&H::Hoge3, 2, 3, &H::Hoge3, 5, 9);

	
	Function b(&H::Hoge5,1.0);
	Function ab(&H::Hoge3,Int);

	using tupleInt = std::tuple<int>;

	//template<class T>
	//using Fn = Function<std::tuple<T, int>>;

	H* h = new H();

	Function _1(&H::Hoge5,5);



	_1.classP = h;

	//_1.operator()();
	//_1.operator()(1,2,3);
	_1.operator()(1,2,3,4);
	//_1.operator()(1,2,3,4,5);
	Function _2(_1, 2);
	Function _3(_2, 3);
	Function _4(_3, 2);
	Function _5(_4, 1);
	_5();
	//IS_tuple_convertible_to<typename IS_TupleUnzip<int,int,int,int,int>::Type, std::tuple<int, int, int,int>>::

	//C_OUT(nnn);
	return 0;

}
