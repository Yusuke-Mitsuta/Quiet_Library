### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/クラスの生成に互換性を持たせる

***
6. もう一つ解決方法として、`Vector3`型のコンストラクタを[`Vector2`+`float`]でも受け取れる様に**オーバーロード**します。

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
};

int main()
{
    Vector2 vec2(1.0f,2.0f);

    Vector3 vec3(vec2,3.0f);
    return 0;
}
``` 
`Vector3`のコンストラクタのオーバーロードにより、[`Vector2`+`float`]でも初期化出来る様になりました。

これで手間なく初期化出来る様になりましたね。

では、[`float`+`Vector2`]の場合はどうでしょう。

## [Back](merit_1_3.md)　[Home](merit_0_0.md)　[Next](merit_1_5.md)　
