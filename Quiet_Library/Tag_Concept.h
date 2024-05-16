#pragma once

#include"String.h"

namespace quiet
{
	template<class T, String t_tag = "", String... t_tags>
	struct Tag;
}

namespace quiet::N_Tag
{
	template<class T, String t_search_Tag>
	struct is_C
	{

	};
}