### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/クラスの生成に互換性を持たせる

***
7. [`float`+`Vector2`]で初期化を行う為、`Vector3`のコンストラクタを更にオーバーロードします。

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

    Vector3(Vector2 set_xy,float set_z):
        x(set_xy.x),y(set_xy.y),z(set_z)
    {}

    Vector3(float set_x,Vector2 set_yz):
        x(set_x),y(set_yz.x),z(set_yz.y)
    {}
};

int main()
{
    Vector2 vec2(2.0f,3.0f);

    Vector3 vec3(1.0f,vec2);
    return 0;
}
``` 
`Vector3`のコンストラクタのオーバーロードにより、[`float`+`Vector2`]でも初期化出来る様になりました。

これで[`float`+`Vector2`]でも、手間なく初期化出来る様になりましたね。

皆さんこう思ったはずです。  
型が異なるが、すべて`float`型3つを受け取るコンストラクタなのに、
#### **オーバーロード**を行わない行けないのは非効率ではないのか？


## [Back](merit_1_4.md)　[Home](merit_0_0.md)　[Next](merit_1_6.md)　
