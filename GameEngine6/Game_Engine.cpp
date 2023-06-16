#include "Game_Engine.h"

Core<"Game_Engine"> Core<"Game_Engine">::Game_Engine;

Core<"Game_Engine">* Core<"Game_Engine">::Get_GameEngine()
{
	return &Game_Engine;
}
