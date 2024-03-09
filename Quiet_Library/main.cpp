#include<iostream>

#include"Quiet_Library.h"

void Output_Int3(int n_1, int n_2, int n_3)
{
    std::cout << n_1 << " , " << n_2 << " , " << n_3 << std::endl;
}
int main()
{
    quiet::Function fn_Output_Int3(&Output_Int3);
    
    std::array<float, 2> ary_float2{ 1.0f, 2.0f };
    std::array<double, 1> ary_double1{ 1.0 };
    std::tuple<float, double> tuple_2(2.0f, 3.0);
    
    fn_Output_Int3(ary_double1, ary_float2);
    fn_Output_Int3(ary_double1, ary_double1, ary_double1);
    fn_Output_Int3(ary_double1, 3, ary_double1);
    fn_Output_Int3(tuple_2, 3);
    fn_Output_Int3(2, tuple_2);
    
    std::array<int, 2> ary_2{ 1, 2 };
    
    quiet::Array ary_3_0(1, 2, 3);
    quiet::Array ary_3_1(ary_2, 3);
    quiet::Array ary_3_2(3, ary_2);
    quiet::Array ary_3_3(ary_3_0);

    fn_Output_Int3(ary_3_0);
    fn_Output_Int3(ary_3_1);
    fn_Output_Int3(ary_3_2);
    fn_Output_Int3(ary_3_3);

    return 0;
}