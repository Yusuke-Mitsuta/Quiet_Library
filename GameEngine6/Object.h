#pragma once

#include"Core.h"

template<Core_Name ...t_Root>
class Core<"Object",t_Root...>:
	public Core<"Core",t_Root...,"Object">
{
public:
	int aaa=1;
};

