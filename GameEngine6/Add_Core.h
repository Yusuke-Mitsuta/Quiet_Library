#pragma once

#include"Core_Control_Tower.h"

namespace N_Core_Control
{


	template<class C_T,bool t_Core=0>
	class Add
	{
	protected:

		Tower<C_T>* tower = nullptr;

	public:

		template<class T>
			requires convertible_to<T,C_T> &&
		not_same_as<C_T,Base>
		T* Add_Child();

		template<class T>
			requires derived_from<T, Scene>
		T* Add_Child();

		template<class T>
			requires derived_from<T, Object>
		T* Add_Child();

		template<class T>
			requires derived_from<T, Conponent>
		T* Add_Child();

	};


};
