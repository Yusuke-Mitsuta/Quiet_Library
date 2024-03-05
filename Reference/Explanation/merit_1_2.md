### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/クラスの生成に互換性を持たせる

***
3. `float`の要素を2つ持つ型、`Vector2`を作成します。
4. `Vector3`型を`Vector2`型と`float`型で宣言します

``` C++
#include<iostream>

struct Vector2
{
    float x;
    float y;

    Vector2(float set_x,float set_y):
        x(set_x),y(set_y)
    {}
};

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
    Vector2 vec2(1.0f,2.0f);

    Vector3 vec3(vec2,3.0f);
    return 0;
}
``` 
`Vector3`は`float`型３つで初期化を行う為、[`Vector2`+`float`]では初期出来ずエラーになります。

次は[`Vector2`+`float`]で`Vector3`を初期化する方法について

## [Back](merit_1_1.md)　[Home](merit_0_0.md)　[Next](merit_1_3.md)　
