### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/クラスの生成に互換性を持たせる

***
1. `std::array<int,3> `を`std::array<int,2>`と`int`を組み合わせて初期化します。

``` C++
#include<array>

int main()
{
    std::array<int, 2> ary_2{ 1,2 };

    std::array<int, 3> ary_3_0{ 1,2,3 };
    std::array<int, 3> ary_3_1{ ary_2[0],ary_2[1],3};
    std::array<int, 3> ary_3_2{ 3,ary_2[0],ary_2[1]};

    return 0;
}
``` 
`std::array<int,2>`を分解する必要があり**面倒**ですよね。

次は、quietライブラリを利用すると、どうなるか見ていきましょう。

[Home](merit_0_0.md)　[Next](merit_1_2.md)　
