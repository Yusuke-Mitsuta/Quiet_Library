### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/関数の引数に互換性を持たせる場合

***
5. `std::tuple`,`std::array`を組み合わせて限界に迫ります。

``` C++
#include<iostream>
#include<array>
#include<tuple>

#include"Function.h"
#include"Tuple.h"
#include"Array.h"

void Output_Int3(int n_1,int n_2,int n_3)
{
    std::cout<<n_1<<" , "<<n_2<<" , "<<n_3<<std::endl;
}
int main()
{
    quiet::Function fn_Output_Int3(&Output_Int3);

    std::array<float, 2> ary_float2{ 1.0f, 2.0f };
    std::array<double, 1> ary_double1{ 1.0 };
    std::tuple<float, double> tuple_2(2.0f, 3.0);

    fn_Output_Int3(ary_double1, ary_float2);
    fn_Output_Int3(ary_double1, ary_double1,ary_double1);
    fn_Output_Int3(ary_double1,3,ary_double1);
    fn_Output_Int3(tuple_2,3);
    fn_Output_Int3(2,tuple_2);

    return 0;
}
``` 
`int`型と互換性のある`float`,`double`なども使用でき、`std::array`,`std::tuple`を混合しても、問題無く動作します。

通常使用しない「要素数1の`std::array`」などでも問題無く使用する事が出来ます。

今回は整数型を例にしましたがユーザー定義等、他の型であっても`std::convertible_to<_Ty1,_Ty2>`が`true`であれば同様に使用できます。

## [Back](merit_0_2.md)　[Home](merit_0_0.md)
