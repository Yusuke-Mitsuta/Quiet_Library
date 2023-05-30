#pragma once

#include"Constexpr_Array.h"

namespace N_Constexpr
{

	//仕様
	//静的に文字列を扱う
	//
	//template
	//t_Size::文字列の長さ
	template<size_t t_Size,char ...t_Str>
	class String
	{
	public:

		Array<char, t_Size> str;

		//constexpr String(const char(&initstr)[t_Size]) :str(initstr) {}
		constexpr String(const char(&initstr)[t_Size]):
			str()
		{
			for (int i = 0; i < t_Size; i++)
			{
				str[i] = initstr[i];
			}

		}
	};

}
