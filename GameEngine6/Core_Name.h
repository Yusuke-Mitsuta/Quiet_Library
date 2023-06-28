#pragma once

#include"Constexpr_String.h"


template<Size_Type className_Size>
class Core_Name
{
private:

public:

	char className[className_Size];

	constexpr Core_Name(
		const char(&set_ClassName)[className_Size]) :
		className()
	{
		for (int i = 0; i < className_Size; i++)
		{
			className[i] = set_ClassName[i];
		}
	}

};