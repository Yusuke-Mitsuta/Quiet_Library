#pragma once

#include"Core.h"

Class_Core(Engine) :
	public Core<"Core">
{
private:

	static Core<"Engine"> Game_Engine;

public:

	Core();

	static constexpr Engine* Get_Engine()
	{
		return &Game_Engine;
	}

};
