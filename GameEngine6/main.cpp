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

class H
{
public:

void Hoge() 
{ 
	//C_OUT(a); 
//	C_OUT(b); 
}
void Hoge3(int a,int b)
{
	//C_OUT(a); 
//	C_OUT(b); 
}
};

template<class _Flom, class _To>
requires std::same_as<std::true_type, typename S_tuple_convertible_to<_Flom, _To>::Type>
void HHH(_Flom t, _To u)
{
}

int main()
{
	

	//std::tuple<int,int,int,int,int> t1(1,3, 3,5,7);
	std::tuple<int, int> t2(4, 2);
	std::tuple<> t4();
	std::tuple t3(3,t2,3,4);


	//HHH(t1, t3);

	Core<"Object">* b = new Core<"Object">();
	//b->Receive<"Test">();
	//b->a();
	//b->a(2);
	H h;

		//Message<"Test">::Receive aa(&H::Hoge,&h);


	Function_Address aaa(&H::Hoge3, &h,t4);
	
	S_Function_Select<std::tuple<int>, 0, decltype(&H::Hoge), decltype(&H::Hoge3),decltype(t4), decltype(t4),int>::Type6::Type1:



	//S_tuple_convertible_to_Access<std::tuple<int,i//nt>,std::tuple<int,int,std::tuple<>>>::Type0//::Type1::Type1::Type3::Type5:


	//aaa.operator()();
	C_OUT(typeid(

		S_Function_Select<std::tuple<int>, 0, decltype(&aaa)>:
	
	).name());

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
	