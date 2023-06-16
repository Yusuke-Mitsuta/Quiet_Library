#pragma once

#include"Core_Storge.h"

namespace N_Core_Control
{

	//template<class T,bool t_Core>
	//class Manager;

	template<class C_T>
	class Tower
	{
	public:

		Storge storge;

		template<class T>
			requires convertible_to<T, C_T>&&
		not_same_as<C_T, Base>
			T* Select_Manager() {}

		template<class T>
			requires convertible_to<T, Scene>
		T* Select_Manager() {}

		template<class T>
			requires convertible_to<T, Object>
		T* Select_Manager(){}

		template<class T>
			requires convertible_to<T, Conponent>
		T* Select_Manager(){}


	};




}