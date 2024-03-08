
### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/関数の引数に互換性を持たせる場合

***
3.  `int`型３つを使用して、`Output_Int3`を出力します。

``` C++
#include<iostream>
#include<array>

void Output_Int3(std::array<int,3> ary_int3)
{
    for (int& n : ary_int3)
    {
        std::cout << n << std::endl;
    }
    std::cout << std::endl;
    return;
}

int main()
{
    //std::array<int, 3> ary_int3{ 1, 2, 3 };
    Output_Int3(1,2,3);
    return 0;
}
``` 
`Output_Int3(int,int,int)`は呼び出し引数が多すぎる為、エラーになると思います。

次は

## [Back](merit_0_2.md)　[Home](merit_0_0.md)　[Next](merit_0_4.md)　
