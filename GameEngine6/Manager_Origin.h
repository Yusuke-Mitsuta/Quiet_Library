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


		template<N_Constexpr::String t_Address = "", N_Constexpr::String t_Message = "">
			requires requires
		{
			requires !(t_Address == N_Constexpr::String(""));
		}
		void Order();

		template<N_Constexpr::String t_Address = "", N_Constexpr::String t_Message = "">
			requires requires
		{
			requires t_Address == N_Constexpr::String("");
		}
		void Order();

	};

	inline constexpr Tower*& N_Core_Control::Manager_Origin::Get_Tower()
	{
		return tower;
	}


	template<class C_T>
	class Manager {};



	template<N_Constexpr::String t_Address, N_Constexpr::String t_Message>
		requires requires
	{
		requires !(t_Address == N_Constexpr::String(""));
	}
	inline void Manager_Origin::Order()
	{
		auto& addres_List= Get_Childs<Core<t_Address>>();
		
		for (auto material : addres_List)
		{
			
		}

	}

	template<N_Constexpr::String t_Address, N_Constexpr::String t_Message>
		requires requires
	{
		requires (t_Address == N_Constexpr::String(""));
	}
	inline void Manager_Origin::Order()
	{
		auto& addres_List = Get_Childs<Core<t_Address>>();
	}

}