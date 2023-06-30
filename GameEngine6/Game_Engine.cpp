#include "Game_Engine.h"
#include"TimeControl.h"
#include"TimerManager.h"
#include"Message.h"

Core<"Engine"> Core<"Engine">::Game_Engine;

Core<"Engine">::Core()
{
	Game_Engine.parentage.Set_Manager(nullptr,E_Core_Type::Engine);

	Game_Engine.parentage.Get_Tower()->this_Core = &Game_Engine;
}

void Core<"Engine">::Start()
{
	//parentage.Add_Child<Time_Control>();

	//parentage.Add_Child<Timer_Manager>();

}