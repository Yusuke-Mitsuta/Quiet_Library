#include "Test_Code.h"

void Test_Code::Array_Test()
{

	Array ary_int_3(1, 3, 5);

	Array ary_float_5(1.0f, 3, 5,7,9);

	ary_float_5 *= 10;//�S�Ă̗v�f�ɒP�̂ł̌v�Z�����{����

	Array ary_int_9(0, ary_int_3, ary_float_5);// [ary_int_3 ]��int 3���ɕ���, [ary_float_5]float 5���ɕ�����Array���\�z����

	ary_float_5 += ary_int_3;//[ary_float_5]�̗v�f�̓��A[ary_int_3]�̃T�C�Y�ł���A[0,1,2]�̗v�f�̂݌v�Z����

}

void Int_3(int n1, int n2, int n3)
{
	C_OUT(n1, n2, n3);
}

void Ary_Int_3(Array<int,3> ary_int_3)
{
	
}

void Test_Code::Function_Test()
{

	//Array ary_int_3(10, 20, 30);

	//Function Int_3_fn(&Int_3);

	Function Ary_Int_3_fn(&Ary_Int_3);


	//Int_3_fn(1, 2, 3);

	//Int_3_fn(ary_int_3);

	//N_Tuple::Apply<Array<int, 3>>(1, 3, 5);

	TYPE_ID(3,
		N_Function::I_Function_Operator_Search<decltype(Ary_Int_3_fn), tuple_t<int, int, int>>::type1::merge_pointer);

	//Ary_Int_3_fn(2, 4, 6);

	//Array<int, 3> ary_2(1, 2, 3);


}
