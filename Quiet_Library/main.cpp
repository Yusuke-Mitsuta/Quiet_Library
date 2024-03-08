#include<compare>

#include"Array.h"

#include<array>

int main()
{
    std::array<int, 2> ary_2( 1,2 );

    quiet::Array ary_3_0(1, 2, 3);
    quiet::Array ary_3_1(ary_2, 3);
    quiet::Array ary_3_2(3, ary_2);
    quiet::Array ary_3_3(ary_3_0);

    return 0;
}