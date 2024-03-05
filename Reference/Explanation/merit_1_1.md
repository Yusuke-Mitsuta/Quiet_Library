### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/クラスの生成に互換性を持たせる

***
1. `float`の要素を3つ持つ型、`Vector3`を作成します。
2. `Vector3`を`float`の要素3つで、宣言します。

``` C++
#include<iostream>
struct Vector3
{
    float x;
    float y;
    float z;

    Vector3(float set_x,float set_y,float set_z):
    x(set_x),y(set_y),z(set_z)
    {}
};

int main()
{
    Vector3 vec3(1.0f,2.0f,3.0f);
    return 0;
}
``` 
`Vector3`のコンストラクタは、`float`型3つを取る為、`float`型3つで宣言が出来ます。   

次は少し複雑な初期化です。

[Home](merit_0_0.md)　[Next](merit_1_2.md)　
