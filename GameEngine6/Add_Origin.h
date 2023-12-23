#pragma once

#include"Core_Control_Tower.h"

namespace N_Core_Control
{

	class Add_Origin
	{
		friend class Add_Origin;

	protected:


		virtual constexpr Tower*& Get_Tower() = 0;

		virtual void SetUp_Child(Base* material) {}

		void Add_Child(Tower* manager_Tower,Base* material,E_Core_Type type);

	public:


		template<class T>
			requires derived_from<T,Base> &&
		same_as_not<T,Base>
		T* Add_Child();

	};


	template<class T>
		requires derived_from<T, Base> &&
		same_as_not<T, Base>
	inline T* Add_Origin::Add_Child()
	{
		T* material = new T();
		Add_Child(Get_Tower()->Scene_Tower,material,Select_Core_Type<T>());
		return material;
	}

	template<class C_T>
	class Add :
		public Add_Origin {};

};
