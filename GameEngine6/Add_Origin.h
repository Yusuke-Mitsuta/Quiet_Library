#pragma once

#include"Core_Control_Tower.h"

namespace N_Core_Control
{

	class Add_Origin
	{
	protected:

		virtual constexpr Tower*& Get_Tower() = 0;

		virtual void SetUp_Child(Base* material) {}

	public:

		void Add_Child(Tower* manager_Tower,Base* material,E_Core_Type type);

		template<class T>
			requires derived_from<T,Scene>
		T* Add_Child();

		template<class T>
			requires derived_from<T,Object>
		T* Add_Child();

		template<class T>
			requires derived_from<T, Component>
		T* Add_Child();

	};


	template<class T>
		requires derived_from<T, Scene>
	inline T* Add_Origin::Add_Child()
	{
		T* material = new T();
		Add_Child(Get_Tower()->Scene_Tower,material,E_Core_Type::Scene);
		return material;
	}

	template<class T>
		requires derived_from<T, Object>
	inline T* Add_Origin::Add_Child()
	{
		T* material = new T();
		Add_Child(Get_Tower()->Object_Tower,material, E_Core_Type::Object);
		return material;
	}

	template<class T>
		requires derived_from<T, Component>
	inline T* Add_Origin::Add_Child()
	{
		T* material = new T();
		Add_Child(Get_Tower()->Component_Tower, material,E_Core_Type::Component);
		return material;
	}

	template<class C_T>
	class Add :
		public Add_Origin {};

};
