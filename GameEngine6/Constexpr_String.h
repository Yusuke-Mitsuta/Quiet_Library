#pragma once

#include<string>
#include"Concept.h"

namespace N_Constexpr
{
	//仕様
	//静的に文字列を扱う
	//
	//template
	//t_Size::文字列の長さ
	template<size_t t_Size>
	class String
	{
	public:

		char str[t_Size];

		constexpr String(
			const char(&set_Str)[t_Size]) :
			str()
		{
			for (int i = 0; i < t_Size; i++)
			{
				str[i] = set_Str[i];
			}
		}


		template<size_t t_StrSize>
			requires Fg<(t_Size > t_StrSize)>
			constexpr String(const char(&initstr)[t_StrSize]) :
			str()
		{
			for (int i = 0; i < t_StrSize; i++)
			{
				str[i] = initstr[i];
			}
			for (int i = t_StrSize; i < t_Size; i++)
			{
				str[i] = '\0';
			}
		}

		constexpr String() :String("") {}

		template<size_t t_StrSize>
			requires Fg<(t_Size >= t_StrSize)>
		constexpr String(String<t_StrSize> str2)
		{
			for (int i = 0; i < t_StrSize; i++)
			{
				str[i] = str2.str[i];
			}
		}

		template<size_t t_StrSize>
		constexpr bool operator==(String<t_StrSize> str2)
		{
			for (int i = 0; str[i] + str2.str[i]; i++)
			{
				if (str[i] - str2.str[i])
				{
					return false;
				}
			}
			return true;
		}

		template<size_t t_StrSize>
			requires Fg<(t_Size >= t_StrSize)>
		constexpr bool operator==(const char(&initstr)[t_StrSize])
		{
			return this->operator==(String{ initstr });
		}

		template<class T>
		constexpr bool operator==(T t)
		{
			return false;
		}

		template<class T>
		constexpr bool operator!=(T t)
		{
			return !this->operator==(t);
		}


		constexpr std::string Change_stdString()
		{
			std::string r_Str;

			for (int i = 0; str[i] != '\0'; i++)
			{
				r_Str.push_back(str[i]);
			}

			r_Str.push_back('\0');
			return r_Str;
		}
	};



}
