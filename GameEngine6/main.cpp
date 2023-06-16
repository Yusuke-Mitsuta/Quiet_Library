#include"main.h"
#include<iostream>
#include"Constexpr_Array.h"
#include"Constexpr_String.h"
#include<tuple>
#include"Object.h"
#include"Args_Type.h"
#include"Game_Object.h"


#include<list>

#include"Message.h"
int main()
{

	std::list<int> List;

	for (std::list<int>::iterator itr = List.begin(); itr != List.end(); itr++)
	{
		
	}



	Core<"Object"> a;


	Core<"Game_Object"> b;
	constexpr int aa = '\0';


	Core<"Game_Object">* c = new Core<"Game_Object">;


	Core_Name aaaa("aiueo");
	Message<"Test", "Test"> ab;

	

	std::cout << sizeof(ab);
	//std::cout << Core_Name("aiueo").className.Change_stdString();


	//N_Constexpr::String str("Game_Object");

	//A("aiu");
	//aaa.game = 10;

	//arg_type<int, int, int>::Args::Type<0> a;

//	constexpr Core<>::Message<"Game_Object", "Test"> g();
	
	
	
	//constexpr Core<"Game_Object">::Message<"Game_Object", "Test"> n;
	
	//constexpr Message n("Game_Object","Test", 2);
	
	
	//constexpr Core<>::Message<"Object","Test"> b();
	
	
	
	

	//Message_P ap = { a,&aaa };

	//N_Constexpr::String str("Game_Object");


	//aa.Router.Send(a);
	
	//str = str2;
	//a.address
	//constexpr int nn = a.address.p;
	
	//Core<a.address> app;
	
	

	//constexpr int num=6;
	//Core<strr[sizeof(aaaaa)]> aaaa;
	

	//aa.Update();

	//for (int i = 0; i < 8; i++)
	//{
		
		//std::cout << a[i] << std::endl;
	//}

	
//	return 0;

}
	