### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/関数の引数に互換性を持たせる場合



***
## 標準ライブラリのみ使用の場合

1. 例として`int`型の要素を合計3つ受け取り出力する関数`Output_Int3`を作成します。

1. 次に、`Output_Int3`が`std::array<int,N>`と`int`の組み合わせでも受け取れる様に`Output_Int3`オーバーロードします。

``` C++
#include<iostream>
#include<array>

void Output_Int3(int n_1,int n_2,int n_3)
{
    std::cout<<n_1<<" , "<<n_2<<" , "<<n_3<<std::endl;
}

void Output_Int3(std::array<int,3> n_123)
{
    Output_Int3(n_123[0], n_123[1],n_123[2]);
}

void Output_Int3(std::array<int,2> n_12, int n_3)
{
    Output_Int3(n_12[0], n_12[1], n_3);
}

void Output_Int3(int n_1, std::array<int, 2>  n_23)
{
    Output_Int3(n_1, n_23[0], n_23[1]);
}

int main()
{
    std::array<int, 3> ary_int3{ 1, 2, 3 };
    std::array<int, 2> ary_int2{ 1, 2};

    Output_Int3(1,2,3);
    Output_Int3(ary_int3);
    Output_Int3(ary_int2,3);
    Output_Int3(3,ary_int2);

    return 0;
}
```
`std::array<int,N>`と`int`型を混合し、**3つの要素**を受け取るだけでも、**+3のオーバーロード**になってしまいます。

次は、quietライブラリを利用すると、どうなるか見ていきましょう。

## [Back](merit_0_0.md)　[Home](merit_0_0.md)　[Next](merit_0_2.md)　
