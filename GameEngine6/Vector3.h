#pragma once

#include"Constexpr_Array.h"

class Vector3:
	public N_Constexpr::Array<float,3>
{

	

public:
	
	using base_array = N_Constexpr::Array<float, 3>;
	float& x = base_array::operator[](0);
	float& y = base_array::operator[](1);
	float& z = base_array::operator[](2);

	

	template<class U, class ...V>
		requires N_Constexpr::N_Array::chack_C<float, 3, U, V...>
	Vector3(U u,V... v) : N_Constexpr::Array<float, 3>(u,v...) {};

};
