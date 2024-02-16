#include"main.h"
#include<compare>
#include<initializer_list>
#include<iostream>

#include"Constexpr_Array.h"
#include"Function.h"
#include"Tuple.h"

#include "Output_Message.h"


int main()
{
	Array ary_0(1, 2, 3);
	using t = decltype(ary_0);
	std::tuple_size_v<t>;

	std::tuple_element_t<0, t>;

	std::array ary_1{ 3, 4,5 };
	auto [x, y, z] = ary_0;

	_CrtDumpMemoryLeaks();
	return 0;
}