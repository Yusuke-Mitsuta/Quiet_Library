
### [README](../../README.md)/quietを利用するメリット

***
4. 次は、`float`型3つで関数を使用します。
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

int main()
{
    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;

    Output_Vector3(x,y,z);
    return 0;
}
```
`Output_Vector3(x,y,z)`の呼び出し引数が多すぎる為、エラーになると思います。

## [Back](merit_0_2.md)　[Home](merit_0_0.md)　[Next](merit_0_4.md)　
