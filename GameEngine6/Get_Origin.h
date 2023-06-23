#pragma once

#include"Core_Control_Tower.h"



namespace N_Core_Control
{

	class Get_Origin
	{
	protected:

		virtual constexpr Tower*& Get_Tower() = 0;

		Storge*& Get_Storge(E_Core_Type type);

		template<class T>
		T* Search(E_Core_Type type);


	public:
		
		template<class T>
			requires derived_from<T, Scene>
		T* Get_Child();

		template<class T>
			requires derived_from<T, Object>
		T* Get_Child();

		template<class T>
			requires derived_from<T, Component>
		T* Get_Child();

	};

	template<class C_T>
	class Get :
		public Get_Origin{};

	template<class T>
	inline T* Get_Origin::Search(E_Core_Type type)
	{
		for (auto tower : Get_Storge(type)->Get_ChildList())
		{
			T* material = static_cast<T*>(tower->this_Core);

			if (material != nullptr)
			{
				return material;
			}

			material = static_cast<Get_Origin*>(tower->this_Core->Get_Parentage())->Get_Child<T>();

			if (material != nullptr)
			{
				return material;
			}
		}
		return nullptr;
	}

	template<class T>
		requires derived_from<T, Scene>
	inline T* Get_Origin::Get_Child()
	{
		return Search<Scene>(E_Core_Type::Scene);
	}

	template<class T>
		requires derived_from<T, Object>
	inline T* Get_Origin::Get_Child()
	{
		return Search<Object>(E_Core_Type::Object);
	}

	template<class T>
		requires derived_from<T,Component>
	inline T* Get_Origin::Get_Child()
	{
		return Search<Component>(E_Core_Type::Component);
	}
}