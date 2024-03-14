#include "Test_Cord.h"

#include<iostream>
#include<array>


void Output_Int3(std::array<int, 3> ary_int3)
{
    std::cout << ary_int3[0] << " , " << ary_int3[1] << " , " << ary_int3[2] << std::endl;
}

void Output_Int3(int n_1, int n_2, int n_3)
{
    Output_Int3(std::array<int, 3>{ n_1, n_2, n_3});
}

void Output_Int3(std::array<int, 2> n_12, int n_3)
{
    Output_Int3(std::array<int,3>{n_12[0], n_12[1], n_3});
}

void Output_Int3(int n_1, std::array<int, 2>  n_23)
{
    Output_Int3(std::array<int, 3>{ n_1, n_23[0], n_23[1]});
}

void Test_Cord::Cord_1()
{

    std::array<int, 3> ary_int3{ 31, 32, 33 };
    std::array<int, 2> ary_int2{ 21, 22 };

    Output_Int3(11, 12, 13);
    Output_Int3(ary_int3);
    Output_Int3(ary_int2, 13);
    Output_Int3(11, ary_int2);

}

