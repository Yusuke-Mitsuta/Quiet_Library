#include "Test_Code.h"

void Test_Code::Array_Test()
{
	//Time_Test::Action();

	//Array ary_int_3(1, 3, 5);

	//Array ary_float_5(1.0f, 3, 5,7,9);

	//ary_float_5 *= 10;//全ての要素に単体での計算を実施する

	//Array ary_int_9(0, ary_int_3, ary_float_5);// [ary_int_3 ]はint 3つ分に分解, [ary_float_5]float 5つ分に分解しArrayを構築する

	//ary_float_5 += ary_int_3;//[ary_float_5]の要素の内、[ary_int_3]のサイズである、[0,1,2]の要素のみ計算する

}

void Int_3(const int& n1, int n2, int n3)
{
	C_OUT(n1, n2, n3);
}

void Ary_Int_3(Array<int,3> ary_int_3)
{
	
}


void Test_Code::Function_Test()
{
	constexpr std::array<int, 3> a{ 2,4,5 };
	//constexpr Array b(222, 5, 7);
	//auto ab= std::get<0>(a);

	//constexpr auto aba = std::get<0>(b);

	//static_cast<int[3]>(a);
	

	constexpr Array ary_int_3(10, 20, 30);




	C_OUT(ary_int_3[0]);
	//Function Int_3_fn(&Int_3);
//
	//Function Ary_Int_3_fn(&Ary_Int_3);


	//Int_3_fn(1, 2, 3);

	//Int_3_fn(ary_int_3);

	//N_Tuple::Apply<Array<int, 3>>(1, 3, 5);


	//Ary_Int_3_fn(2, 4, 6);

	//Ary_Int_3_fn(ary_int_3);

}
