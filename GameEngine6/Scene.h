#pragma once

#include "Core.h"


using Scene = Core<"Scene">;

template<>
class Core<"Scene">:
    public Core<"Core">
{
public:

    Core<"Scene">()
    {
    
    }

};