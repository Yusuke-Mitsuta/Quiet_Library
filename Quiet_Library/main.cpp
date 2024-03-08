#include<compare>

#include"Array.h"
//#include"Float3.h"
#include"Tuple.h"
//#include"Vector.h"
#include"Function.h"

#include<iostream>
#include<array>



void Output_Int3(int n_1, int n_2, int n_3)
{
    std::cout << n_1 << " , " << n_2 << " , " << n_3 << std::endl;
}

using namespace quiet;

int main()
{
    quiet::Function fn(&Output_Int3);

    std::array<int, 3> ary_int3{ 1, 2, 3 };


    fn(ary_int3);


    return 0;
}