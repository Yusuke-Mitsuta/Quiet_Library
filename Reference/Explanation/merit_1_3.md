### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/クラスの生成に互換性を持たせる

***
3. [`std::array`->`quiet::Array`]に変更し、柔軟性の高いコンストラクタを利用します。

``` C++
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
``` 
`quiet::Array`を利用する事により、全て`quiet::Array<int,3>`に推論されます。

次は、**推論補助**の柔軟性の高さです。

## [Back](merit_1_2.md)　[Home](merit_0_0.md)　[Next](merit_1_4.md)　