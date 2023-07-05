#pragma once

#include"main.h"
#include"Add_Origin.h"
#include"Get_Origin.h"


namespace N_Core_Control
{

	class Manager_Origin :
		public Add_Origin,
		public Get_Origin
	{
		friend class Add_Origin;
		friend class Get_Origin;
	protected:

		Tower* tower = nullptr;

		constexpr Tower*& Get_Tower();

	public:

		DONT_COPY(Manager_Origin)
		Manager_Origin() {}

	};

	inline constexpr Tower*& N_Core_Control::Manager_Origin::Get_Tower()
	{
		return tower;
	}


	template<class C_T>
	class Manager {};




}