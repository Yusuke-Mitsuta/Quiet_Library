#pragma once

#include"Core.h"
#include"Constexpr_String.h"

template<>
class Core<"Object"> :
	public Core<"Core">
{
public:

	void object() {}

};

