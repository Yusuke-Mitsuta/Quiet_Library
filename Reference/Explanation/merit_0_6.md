### [README](../../README.md)/quietを利用するメリット

***
7. `float`の要素を2つ持つ型`Vector2`を作成します。
8. `Output_Vector3`を**オーバーロード**を行い、`Vector2` + `float` も受け取れる様にします。
``` C++
#include<iostream>
struct Vector3
{
    float x;
    float y;
    float z;
};

struct Vector2
{
    float x;
    float y;
};


void Output_Vector3(Vector3 vec3)
{
    std::cout<<"x : "<<vec3.x<<" , y : "<<vec3.y<<" , z : "<<vec3.z<<std::endl;
}

void Output_Vector3(float x,float y,float z)
{
    Output_Vector3(Vector3(x,y,z));
}

void Output_Vector3(Vector2 vec2,float z)
{
    Output_Vector3(Vector3(vec2.x,vec2.y,z));
}

int main()
{
    Vector3 vec3(1.0f,2.0f,3.0f);

    Vector2 vec2(1.0f,2.0f);

    float x=0.0f;
    float y=1.0f;
    float z=2.0f;

    Output_Vector3(x,y,z);
    Output_Vector3(vec3);
    Output_Vector3(vec2,z);

    return 0;
}
```
これで、`Vector3`型、`float`型3つ、に加え、`Vector2` + `float` でも受け取れる様になりました。

***
ですが、、、
皆さんこう思ったはずです。
型が異なるが、すべて`float`型3つを受け取る関数なのに、
#### **オーバーロード**を行わない行けないのは非効率ではないのか？

## [Back](merit_0_5.md)　[Home](merit_0_0.md)　[Next](merit_0_7.md)　
