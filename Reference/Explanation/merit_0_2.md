### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/関数の引数に互換性を持たせる場合

***
## quietライブラリを追加で使用する場合

3. 互換性を持たせる為に作成したオーバーロードをすべて削除します。
4. 関数`Output_Int3`を[quiet::Function](../Function/Function.md)でラッピングし、`fn_Output_Int3`を作成します。

``` C++
#include<iostream>
#include<array>

#include"Quiet_Library.h"

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
`Output_Int3`は[quiet::Function]()にてラッピングされた事により、`int`型と互換性のある型が、合計で3つ以下であれば**全てに対応出来る**ようになりました。

次は作成した関数オブジェクト`fn_Output_Int3`の柔軟性の高さについてです。

## [Back](merit_0_1.md)　[Home](merit_0_0.md)　[Next](merit_0_3.md)　
