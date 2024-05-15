#pragma once

#include"String.h"

namespace quiet::N_Tuple
{
	template<size_t t_Size>
	class S_Name :
		public String<t_Size>
	{
	public:


		constexpr S_Name(const char(&set_Str)[t_Size]) :
			String<t_Size>(set_Str) {}

		constexpr S_Name() :
			String<t_Size>("") {}

		template<size_t t_StrSize>
			requires (t_Size >= t_StrSize)
		constexpr S_Name(String<t_StrSize> str2) :
			String<t_Size>(str2) {}

		using String<t_Size>::operator=;
		using String<t_Size>::operator==;
		using String<t_Size>::operator!=;

	};
}
