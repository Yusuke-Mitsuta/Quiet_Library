#pragma once

#include"Constexpr_String.h"

template<unsigned short className_Size>
class Core_Name
{
private:

public:

	//static constexpr unsigned short className_Size = 12;

	N_Constexpr::String<className_Size> className;

	//template<unsigned int className_Size>
	constexpr Core_Name(
		const char(&set_ClassName)[className_Size]) :
		className()
	{
		for (int i = 0; i < className_Size; i++)
		{
			className.str[i] = set_ClassName[i];
		}


	}

};

