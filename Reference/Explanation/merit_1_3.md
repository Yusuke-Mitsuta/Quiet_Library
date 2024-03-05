### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/クラスの生成に互換性を持たせる

***
5. [`Vector2`+`float`]で`Vector3`型の初期化する方法として、`Vector2`型を`float`型２つに直して宣言します。

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

    //Vector3 vec3(vec2,3.0f);
    Vector3 vec3(vec2.x,vec2.y,3.0f);
    return 0;
}
``` 
`Vector3`は`float`型3つを取る様になる為、宣言が出来ます。

ですが、毎回分解するのは、**面倒**ですよね。

## [Back](merit_1_2.md)　[Home](merit_0_0.md)　[Next](merit_1_4.md)　
