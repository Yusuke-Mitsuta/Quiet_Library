#include "Core_Parentage.h"
#include"Core.h"
#include"Scene.h"

void N_Core_Control::Parentage::Set_Manager(Tower* parent_Tower,E_Core_Type type)
{
	Tower*& scene_Tower = Scene_Tower.Get_Tower();
	Tower*& object_Tower = Object_Tower.Get_Tower();
	Tower*& component_Tower = Component_Tower.Get_Tower();

	switch (type)
	{
	case E_Core_Type::Object:
		Get_Tower() = object_Tower;

		scene_Tower->storge = 
			parent_Tower->Scene_Tower->storge;

		object_Tower->storge = new Storge();

		component_Tower->storge = new Storge();
		break;
	case E_Core_Type::Component:
		Get_Tower() = component_Tower;

		scene_Tower->storge =
			parent_Tower->Scene_Tower->storge;

		object_Tower->storge =
			parent_Tower->Object_Tower->storge;

		component_Tower->storge =
			parent_Tower->Component_Tower->storge;
		break;
	default: //Engine,Scene‚Í‘Sì¬
		Get_Tower() = scene_Tower;

		scene_Tower->storge = new Storge();
		object_Tower->storge = new Storge();
		component_Tower->storge = new Storge();
		break;
	}

	Get_Tower()->type = type;

	Get_Tower()->parent_Tower = parent_Tower;

	Get_Tower()->Scene_Tower = Scene_Tower.Get_Tower();

	Get_Tower()->Object_Tower = Object_Tower.Get_Tower();

	Get_Tower()->Component_Tower = Component_Tower.Get_Tower();

}

