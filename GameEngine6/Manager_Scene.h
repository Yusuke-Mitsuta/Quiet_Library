#pragma once

#include"Manager_Origin.h"
#include"Add_Scene.h"
#include"Get_Scene.h"

namespace N_Core_Control
{

	template<>
	class Manager<Scene> :
		public Manager_Origin
	{
		friend class Parentage;
	public:

		Manager<Scene>()
		{
			tower = new Tower();
		}

	};
}