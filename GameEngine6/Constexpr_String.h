#pragma once

#include"Constexpr_Array.h"
#include<string>
#include"Concept.h"

namespace N_Constexpr
{
	//d—l
	//Ã“I‚É•¶š—ñ‚ğˆµ‚¤
	//
	//template
	//t_Size::•¶š—ñ‚Ì’·‚³
	template<size_t t_Size>
	class String
	{
	public:

		Array<char, t_Size> str;

		constexpr String(const char(&initstr)[t_Size]) :
			str()
		{
			
			for (int i = 0; i < t_Size; i++)
			{
				str[i] = initstr[i];
			}
		}

		template<int t_StrSize>
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

		template<int t_StrSize>
			requires Fg<(t_Size >= t_StrSize)>
		constexpr String(String<t_StrSize> str2)
		{
			for (int i = 0; i < t_StrSize; i++)
			{
				str[i] = str2.str[i];
			}
		}

		//template<int t_StrSize>
		//	requires Fg<(t_Size >= t_StrSize)>
		//void operator=(String<t_StrSize> str2)
		//{
		//	for (int i = 0; i < t_StrSize; i++)
		//	{
		//		str[i] = str2.str[i];
		//	}
		//}

		template<class T>
		constexpr bool operator==(T t)
		{
			return (str == t.str);
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
