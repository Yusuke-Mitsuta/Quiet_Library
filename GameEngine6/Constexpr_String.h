#pragma once

#include"Constexpr_Array.h"

namespace N_Constexpr
{

	//�d�l
	//�ÓI�ɕ����������
	//
	//template
	//t_Size::������̒���
	template<size_t t_Size>
	class String
	{
	public:

		Array<char, size> str;

		constexpr String(const char(&initstr)[t_Size]) :
			str()
		{
			for (int i = 0; i < t_Size; i++)
			{
				str[i] = initstr[i];
			}

		}
	};


}