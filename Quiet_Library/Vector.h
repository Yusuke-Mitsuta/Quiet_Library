/*!
 * Vector.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Array.h"
#include"Vector_Core.h"

namespace quiet
{

	using Vector2 = quiet::N_Vector::S_Core<float, 2>;
	using Vector2Int = quiet::N_Vector::S_Core<int, 2>;
	using Vector2Bool = quiet::N_Vector::S_Core<bool, 2>;
	template<class T>
	using Vector2All = quiet::N_Vector::S_Core<T, 2>;


	using Vector3 = quiet::N_Vector::S_Core<float, 3>;
	using Vector3Int = quiet::N_Vector::S_Core<int, 3>;
	using Vector3Bool = quiet::N_Vector::S_Core<bool, 3>;
	template<class T>
	using Vector3All = quiet::N_Vector::S_Core<T, 3>;

	using Vector4 = quiet::N_Vector::S_Core<float, 4>;
	using Vector4Int = quiet::N_Vector::S_Core<int, 4>;
	using Vector4Bool = quiet::N_Vector::S_Core<bool, 4>;
	template<class T>
	using Vector4All = quiet::N_Vector::S_Core<T, 4>;
}