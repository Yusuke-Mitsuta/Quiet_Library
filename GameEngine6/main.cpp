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

#include<list>

#include"Message.h"
int main()
{
	auto s= Engine::Get_Engine()->parentage.Add_Child<Scene>();

	s->parentage.Add_Child<Scene>();

	Engine::Get_Engine()->parentage.Get_Child<Scene>();
	
	
	return 0;

}
	