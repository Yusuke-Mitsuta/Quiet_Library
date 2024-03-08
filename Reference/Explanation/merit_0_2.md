### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/関数の引数に互換性を持たせる場合

***
3. 互換性を持たせる為に作成したオーバーロードをすべて削除します。
4. 関数`Output_Int3`を`quiet::Function`でラッピングし、`fn_Output_Int3`を作成します。

``` C++
#include<iostream>
#include<array>

#include"Function.h"
#include"Array.h"

void Output_Int3(int n_1,int n_2,int n_3)
{
    std::cout<<n_1<<" , "<<n_2<<" , "<<n_3<<std::endl;
}
int main()
{
    quiet::Function fn_Output_Int3(&Output_Int3);

    std::array<int, 3> ary_int3{ 1, 2, 3 };
    std::array<int, 2> ary_int2{ 1, 2};

    fn_Output_Int3(1,2,3);
    fn_Output_Int3(ary_int3);
    fn_Output_Int3(ary_int2,3);
    fn_Output_Int3(3,ary_int2);

    return 0;
}
``` 
quietライブラリを利用すると、オーバーロードを全て削減されました。

次は作成した関数オブジェクト`fn_Output_Int3`の柔軟性の高さについてです。

## [Back](merit_0_1.md)　[Home](merit_0_0.md)　[Next](merit_0_3.md)　
