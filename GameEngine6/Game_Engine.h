#pragma once

#include"Core.h"

template<>
class Core<"Game_Engine"> :
	public Core<"Core">
{
private:

	static Core<"Game_Engine"> Game_Engine;

public:

	static Core<"Game_Engine">* Get_GameEngine();

};
