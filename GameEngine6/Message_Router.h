#pragma once

#include"Component.h"
#include"main.h"

template<>
class Core<"Routur"> :
	public Core<"Component">
{
public:
	void Execute();
};
