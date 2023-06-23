#pragma once

#include"Concept.h"
#include"Core_Base.h"
#include<list>



namespace N_Core_Control
{


	using Base = Core<"Core">;
	using Scene = Core<"Scene">;
	using Object = Core<"Object">;
	using Component = Core<"Component">;


	class Tower;

	class Storge
	{
	protected:

		std::list<Tower*> childList;

	public:

		std::list<Tower*>& Get_ChildList();



	};




}
