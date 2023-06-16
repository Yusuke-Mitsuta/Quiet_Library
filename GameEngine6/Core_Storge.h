#pragma once

#include"Core_Name.h"
#include"Concept.h"
#include<list>



template<Core_Name className>
class Core;


namespace N_Core_Control
{
	using Base = Core<"Base">;
	using Scene = Core<"Scene">;
	using Object = Core<"Object">;
	using Conponent = Core<"Component">;

	class Storge
	{
	protected:


		std::list<Base> childList;

	public:





	};


}
