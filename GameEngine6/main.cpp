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
#include<list>

#include"Message.h"


int main()
{
	Core<"Core">* b = new Core<"Core">();
	//b->Receive<"Test">();

	static_cast<Core<"Base">*>(b)->Receive<"Update">();

	Engine::Get_Engine()->Start();


	auto s = Engine::Get_Engine()->parentage.Add_Child<Scene>();
	auto ss= s->parentage.Add_Child<Scene>();
	auto sss= ss->parentage.Add_Child<Scene>();
	auto ssss= sss->parentage.Add_Child<Scene>();

	auto list = Engine::Get_Engine()->parentage.Get_Childs<Scene>();

	
	return 0;

}
	