
#include<compare>

#include"Array.h"
#include"Function.h"
#include"Tuple.h"
#include"Vector.h"
#include<array>

#include <concepts>
#include <type_traits>


int main()
{



    std::array<int, 2> ary_2{ 1,2 };



    quiet::Array<int, 3> ary_3_0{ 1, 2, 3 };


    quiet::Array ary_3_1{ ary_2, 3 };
    
    quiet::Array ary_3_2(3, ary_2);
    quiet::Array ary_3_3(ary_3_0);

    std::cout<<ary_3_2[0]<< ary_3_2[1]<< ary_3_2[2];
    
    return 0;
}