#include "Compare_Code_Original.h"

#include<string>

using namespace quiet;

void Compare_Code::Original_Array()
{
	Array ary_int3_1(1, 2, 3);

	Array ary_int3_2(4,5,6);

	auto plus_int= ary_int3_1 + 10;

	type_id(plus_int);
	OUTPUT_MESSAGE::C_Out_For(plus_int);

	auto plus_ary_int3 = ary_int3_1 + ary_int3_2;

	Array<int, 6> ary_int_6(ary_int3_1, ary_int3_2);

	type_id(ary_int_6);
	OUTPUT_MESSAGE::C_Out_For(ary_int_6);




}
