#pragma once

#include "Core.h"
#include "Game_Engine.h"


using Scene = Core<"Scene">;

template<>
class Core<"Scene">:
    public Core<"Core">
{
public:

    Core()
    {
    
    }

};