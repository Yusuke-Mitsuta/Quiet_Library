### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/クラスの生成に互換性を持たせる

***
3. `quiet::Array`の推論補助の限界についてです。

``` C++
#include"Array.h"
#include<array>

int main()
{
    std::array<int, 2> ary_2( 1,2 );

    quiet::Array ary_4_0(ary_2,3,4);
    quiet::Array ary_4_1(1,ary_2,4);
    quiet::Array ary_4_2(1,2,ary_2);
    
    return 0;
}
``` 
[`ary_4_0`=`quiet::Array<quiet::Array<int,2>,2>`]
[`ary_4_1`,`ary_4_2`=`quiet::Array<int,4>`]

尚、型の互換性については 「[関数の引数に互換性を持たせる場合](merit_0_3.md)」と同様になります。

## [Back](merit_1_3.md)　[Home](merit_0_0.md)