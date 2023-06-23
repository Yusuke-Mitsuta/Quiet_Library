#include "Get_Origin.h"
#include"Manager_Scene.h"
#include"Manager_Object.h"
#include"Manager_Component.h"
using namespace N_Core_Control;

Storge*& Get_Origin::Get_Storge(E_Core_Type type)
{
	switch (type)
	{
	case E_Core_Type::Scene:
		return Get_Tower()->Scene_Tower->storge;
		break;
	case E_Core_Type::Object:
		return Get_Tower()->Object_Tower->storge;
		break;
	case E_Core_Type::Component:
		return Get_Tower()->Component_Tower->storge;
		break;
	default:
		break;
	}
	return Get_Tower()->storge;
}


