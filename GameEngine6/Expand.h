#pragma once

#include<optional>

template<class ...T_Parameters>
struct S_Parameter;

template<class T_Zip>
struct S_Expand
{
	using Not = std::nullopt_t;
};

template<class T_Zi_p>
struct S_Zip
{
	using T= std::is_constructible<S_Expand<int>,int>;
	using Not = std::nullopt_t;
};