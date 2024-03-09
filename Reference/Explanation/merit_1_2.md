### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/クラスの生成に互換性を持たせる

***

## quietライブラリを追加で使用する場合 ( 1 / 2 )

1. `std::array`のコンストラクタは追加定義する事が出来ない為、関数`quiet::Apply<T>`を用いて生成する事により、引数に柔軟性を持たせます。

``` C++
#include"Quiet_Library.h"
#include<array>

int main()
{
    std::array<int, 2> ary_2{ 1,2 };

    std::array<int, 3> ary_3_0 = quiet::Apply<std::array<int, 3>>(1, 2, 3);
    std::array<int, 3> ary_3_1 = quiet::Apply<std::array<int, 3>>(ary_2, 3);
    std::array<int, 3> ary_3_2 = quiet::Apply<std::array<int, 3>>(3, ary_2);
    std::array<int, 3> ary_3_3 = quiet::Apply<std::array<int, 3>>(ary_3_0);

    return 0;
}
``` 
`quiet::Apply<T>`を利用する事により、`ary_2`を明示的に分解せずとも、`std::array<int,3>`を作成する事が出来ました。

ただ、初期化用に毎回、関数を呼び出していると、**推論補助**が使えずは不便ですよね。

次は、`std::array`を元に拡張されたクラス`quiet::Array`を利用します。

## [Back](merit_1_1.md)　[Home](merit_0_0.md)　[Next](merit_1_3.md)　
