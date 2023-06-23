#include "Core_Storge.h"

using namespace N_Core_Control;

std::list<Tower*>& Storge::Get_ChildList()
{
    return childList;
}
