#include "Game_Engine.h"

Engine Engine::Game_Engine;


Engine::Core()
{
	Game_Engine.parentage.Set_Manager(nullptr,E_Core_Type::Engine);

	Game_Engine.parentage.Get_Tower()->this_Core = &Game_Engine;
}


