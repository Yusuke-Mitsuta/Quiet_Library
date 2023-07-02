#include"Add_Origin.h"

#include"Manager_Origin.h"
#include"Core_Parentage.h"
#include"Core.h"

using namespace N_Core_Control;

void N_Core_Control::Add_Origin::Add_Child(Tower* manager_Tower, Base* material, E_Core_Type type)
{
	
	material->parentage.Set_Manager(Get_Tower(), type);

	material->parentage.Get_Tower()->this_Core = material;

	manager_Tower->storge->Get_ChildList().emplace_back(
		material->parentage.Get_Tower());

}
