
#include "Test_Cord.h"

#include<iostream>
#include<array>

struct Int3
{
    std::array<int, 3> data;

    void Output_Int3();

    Int3(int n_1, int n_2, int n_3) :
        data({ n_1,n_2,n_3 })
    { Output_Int3(); }

    Int3(std::array<int, 3> ary_int3) :
        data(ary_int3) 
    { Output_Int3(); }

    Int3(std::array<int, 2> n_12, int n_3) :
        data({n_12[0], n_12[1], n_3})
    { Output_Int3(); }

    Int3(int n_1, std::array<int, 2>  n_23) :
        data({ n_1, n_23[0], n_23[1]})
    { Output_Int3(); }
    
};

void Int3::Output_Int3()
{
    std::cout << data[0] << " , " << data[1] << " , " << data[2] << std::endl;
}

void Test_Cord::Cord_2()
{

    std::array<int, 3> ary_int3{ 31, 32, 33 };
    std::array<int, 2> ary_int2{ 21, 22 };

    Int3 int3_0(11, 12, 13);
    Int3 int3_1(ary_int3);
    Int3 int3_2(ary_int2, 13);
    Int3 int3_3(11, ary_int2);

}


