#pragma once

#include"Core_Storge.h"
#include"Core_Type.h"

namespace N_Core_Control
{
	template<class C_T>
	class Manager;

	class Manager_Origin;

	class Tower
	{
	public:

		Storge* storge;

		Tower* parent_Tower;

		Core<"Core">* this_Core;

		E_Core_Type type;

		Tower* Scene_Tower;

		Tower* Object_Tower;

		Tower* Component_Tower;

	};



}