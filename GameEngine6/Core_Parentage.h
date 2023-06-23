#pragma once


#include"Manager_Origin.h"
#include"Manager_Scene.h"
#include"Manager_Object.h"
#include"Manager_Component.h"

namespace N_Core_Control
{
	
	class Parentage :
		public Manager_Origin
	{
		friend class Add_Origin;
		friend class Core<"Engine">;

	private:

		void Set_Manager(Tower* parent_Tower,E_Core_Type type);

	public:

		Manager<Scene> Scene_Tower;

		Manager<Object> Object_Tower;

		Manager<Component> Component_Tower;

		


	};

}