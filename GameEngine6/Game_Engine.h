#pragma once

#include"Core.h"

using Engine = Core<"Engine">;

template<>
class Core<"Engine"> :
	public Core<"Core">
{
private:

	static Core<"Engine"> Game_Engine;

public:

	Core();

	void Start();

	static constexpr Engine* Get_Engine()
	{
		return &Game_Engine;
	}

};
