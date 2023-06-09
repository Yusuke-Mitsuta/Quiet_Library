#pragma once

#include"Constexpr_String.h"

class Core_Name
{
private:

public:

	static constexpr unsigned short className_Size = 64;

	N_Constexpr::String<className_Size> className;

	template<unsigned int t_ClassNameSize>
	constexpr Core_Name(
		const char(&set_ClassName)[t_ClassNameSize]) :
		className()
	{
		for (int i = 0; i < t_ClassNameSize; i++)
		{
			className.str[i] = set_ClassName[i];
		}

		for (int i = 0; i < className_Size- t_ClassNameSize; i++)
		{
			className.str[i+ t_ClassNameSize] = '\0';
		}

	}

};

