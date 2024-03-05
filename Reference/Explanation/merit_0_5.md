
### [README](../../README.md)/quietを利用するメリット

***
6. `Output_Vector3`を**オーバーロード**を行い、float型3つも受け取れる様にします。
``` C++
#include<iostream>
struct Vector3
{
    float x;
    float y;
    float z;
};

void Output_Vector3(Vector3 vec3)
{
    std::cout<<"x : "<<vec3.x<<" , y : "<<vec3.y<<" , z : "<<vec3.z<<std::endl;
}

void Output_Vector3(float x,float y,float z)
{
    Output_Vector3(Vector3(x,y,z));
}

int main()
{
    Vector3 vec3(1.0f,2.0f,3.0f);

    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;

    Output_Vector3(x,y,z);
    Output_Vector3(vec3);

    return 0;
}
```
これで、`Vector3`型、`float`型3つ、のどちらでも受け取れる様になりました。

次は、`float`の要素を2つ持つ型`Vector2`を作成するとします。

## [Back](merit_0_4.md)　[Home](merit_0_0.md)　[Next](merit_0_6.md)　
