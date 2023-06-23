#pragma once

#include"Manager_Origin.h"

namespace N_Core_Control
{

	template<>
	class Manager<Object> :
		public Manager_Origin
	{
		friend class Parentage;
	public:

		Manager<Object>()
		{
			tower = new Tower();
		}

	};

}