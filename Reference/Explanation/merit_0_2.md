### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/関数の引数に互換性を持たせる場合

***
3. 互換性を持たせる為に作成したオーバーロードをすべて削除します。

``` C++
#include<iostream>
#include<array>

void Output_Int3(int n_1,int n_2,int n_3)
{
    std::cout<<n_1<<" , "<<n_2<<" , "<<n_3<<std::endl;
}

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
    std::array<int, 3> ary_int3{ 1, 2, 3 };
    Output_Int3(ary_int3);
    return 0;
}
``` 
ここまでは、なんの変哲もない通常のコードですね。

次は、`int`型3つで呼び出す事について考えていきます。

## [Back](merit_0_1.md)　[Home](merit_0_0.md)　[Next](merit_0_3.md)　
