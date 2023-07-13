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
#include"Function_Bind_Args.h"
#include<type_traits>

#include<tuple>
#include<optional>
#include<utility>
#include"Constexpr_Array.h"
#include"ClassFunction.h"

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
		//C_OUT(a); 
	//	C_OUT(b); 
	}

	//template<class C_Name, class R_Type, class ...T_Args>
	//template<class T>
	void Hogege( void(H::*P)()) 
	{
		//TYPE_ID(P)
	}


	void Hoge3(int a, int b)
	{
		Hogege(&H::Hoge);
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


int main()
{
	//TYPE_ID(decltype(&H::Hoge3));
	std::tuple<int, int> Int(3,7);
	std::tuple<float,char> Intt(3,'8');
	std::tuple abcd(Int,Intt);

	HHH<std::tuple<int, int>, std::tuple<int, int>>();

	
	int i = 9;
	//auto NNN = IS_TupleUnzip<int, int>::I_TupleUnzip(2, 1);

	//Function fn(&H::Hoge3, 2, 7);
	
	//N_Function::IS_BindFn<decltype(&H::Hoge3), int, int>::Type::FnType

	//C_OUT(typeid(decltype(NNN)).name())
			//N_Function::IS_BindFn<decltype(&H::Hoge3), int, int>::Type::FnType).name()

	
	//HHH<std::tuple<int, int,int>, std::tuple<int, int>>();


	//IS_tuple_convertible_to<std::tuple<int, int,int>, std::tuple<H(),int>>::

	//IS_TupleUnzip<decltype(abcd), decltype(abcd)>::Type t;

	IS_TupleUnzip t(abcd, abcd);

	//TYPE_ID(IS_TupleUnzip<decltype(abcd)>::Type);
	type_id(t)

		//Type0::Type1::Type2::Type2::Type3b::Bind3t::Type1::Type2::Type2::Type5e::End3e::End1
	std::tuple  tu(&H::Hoge3, 2, 3, &H::Hoge3, 5, 9);
	//IS_TupleUnzip tuo(3,Num);
	
	//IS_TupleUnzip a(3,4,i);


	
	Function b(&H::Hoge3,5,5);
	Function ab(&H::Hoge3,Int);

	//N_Function::IS_BindFns<std::tuple<decltype(&H::Hoge3),
	//	int, int, decltype(&H::Hoge3), int, int>>::Type::
	//C_OUT(
		//typeid(
		//N_Function::IS_BindFns<std::tuple<decltype(&H::Hoge3),
		//int, int, decltype(&H::Hoge3), int, int>>::Type::Fns).name())
	//N_Function::IS_BindFns aaaa(tu);

			

	//C_OUT(typeid(IS_tuple_convertible_to<
	//	std::tuple<int, int>, std::tuple<int, int,int>>::BackPart
	//	
	//	).name())



	//std::tuple<int,int,int,int,int> t1(1,3, 3,5,7);
	//std::tuple<int, int> t2(4, 2);
	//std::tuple<int, char> t6(4, 2);
	//std::tuple t5(t2, t6);
	//std::tuple<> t4;
	//std::tuple t3(3,t2,t4,3,4,t5);

	//I_S_Function_Select<t6> 
	//Hoge3<std::tuple<int, int>, std::tuple<>>(t2, t4);

	//TYPE_ID(std::make_index_sequence<5>);
//	IS_TupleUnzip<decltype(t3)>::Type);


	//HHH(t1, t3);

	//b->Receive<"Test">();
	//b->a();
	//b->a(2);
	H h;

	//Message<"Test">::Receive aa(&H::Hoge,&h);






//	S_Address aaa(&H::Hoge3, &h,t4);

	//S_Function_Select<std::tuple<int>, 0, decltype(&H::Hoge), decltype(&H::Hoge3),decltype(t4), decltype(t4),int>



	//IS_tuple_convertible_to<std::tuple<int,i//nt>,std::tuple<int,int,std::tuple<>>>::Type0//::Type1::Type1::Type3::Type5:


	//aaa.operator()();
	//C_OUT(typeid(

	//	S_Function_Select<std::tuple<int>, 0, decltype(&aaa)>:
	//
	//).name());

	//aaa.ffn(2);

	//aa.ffn(3);

//	aa.ffn();

	//static_cast<Core<"Base">*>(b)->Order<"a">();

	//Engine::Get_Engine()->SC_tart();


	//auto s = Engine::Get_Engine()->parentage.Add_Child<Scene>();
	//auto ss= s->parentage.Add_Child<Scene>();
	//auto sss= ss->parentage.Add_Child<Scene>();
	//auto ssss= sss->parentage.Add_Child<Scene>();

	//auto list = Engine::Get_Engine()->parentage.Get_Childs<Scene>();


	return 0;

}
