#include "Compare_Code_Existing.h"

#include<string>
#include<array>

void Compare_Code::Existing_Array()
{
	std::array ary_int3_1{ 1,2,3 };

	std::array ary_int3_2{ 4,5,6 };

	
	std::array plus_int = {
		ary_int3_1[0] + 10,
		ary_int3_1[1] + 10, 
		ary_int3_1[2] + 10 };

	std::array plus_ary_int3 = {
		ary_int3_1[0] + ary_int3_2[0],
		ary_int3_1[1] + ary_int3_2[1],
		ary_int3_1[2] + ary_int3_2[2] };

	

}
