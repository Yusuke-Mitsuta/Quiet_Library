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

#include"Constexpr_Array.h"



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
}
};
template<class T, class U>
void Hoge3(T a, U b)
{
	//C_OUT(a); 
//	C_OUT(b); 
}
template<class _Flom, class _To>
requires std::same_as<std::true_type, typename S_tuple_convertible_to<_Flom, _To>::Type>
void HHH(_Flom t, _To u)
{
}




template<class T>
struct Hoge
{
	T t=1;
};






int main()
{

	N_Constexpr::Array<int, 3> array_3(1,2,3);

	N_Constexpr::Array<int, 7> array_7(1,2,3,4,5,6,7);

	N_Constexpr::Array<int, 10> array_10(array_3,array_7);

	
	N_Function::I_S_BindArgs<decltype(&H::Hoge3), int, int>::Type;

	
	
	//std::tuple<int,int,int,int,int> t1(1,3, 3,5,7);
	std::tuple<int, int> t2(4, 2);
	std::tuple<int, char> t6(4, 2);
	std::tuple t5(t2, t6);
	std::tuple<> t4;
	std::tuple t3(3,t2,t4,3,4,t5);

	//I_S_Function_Select<t6> 
	//Hoge3<std::tuple<int, int>, std::tuple<>>(t2, t4);

	TYPE_ID(
	I_S_TupleUnzip<decltype(t3)>::Type);


	//HHH(t1, t3);

	//b->Receive<"Test">();
	//b->a();
	//b->a(2);
	H h;

		//Message<"Test">::Receive aa(&H::Hoge,&h);






	S_Address aaa(&H::Hoge3, &h,t4);
	
	//S_Function_Select<std::tuple<int>, 0, decltype(&H::Hoge), decltype(&H::Hoge3),decltype(t4), decltype(t4),int>



	//S_tuple_convertible_to_Access<std::tuple<int,i//nt>,std::tuple<int,int,std::tuple<>>>::Type0//::Type1::Type1::Type3::Type5:


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
	