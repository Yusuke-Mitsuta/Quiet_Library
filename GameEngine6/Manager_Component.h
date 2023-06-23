#pragma once

#include"Manager_Origin.h"

namespace N_Core_Control
{

	template<>
	class Manager<Component> :
		public Manager_Origin
	{
		friend class Parentage;
	public:

		Manager<Component>()
		{
			tower = new Tower();
		}
	};

}