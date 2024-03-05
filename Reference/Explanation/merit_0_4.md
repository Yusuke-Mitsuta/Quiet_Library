
### [README](../../README.md)/quietを利用するメリット

***
5. 呼び出し引数が多すぎるエラーを解消する為、`float`型3つを、`Vector3`に変換して関数を使用します。
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

    Output_Vector3(Vector3(x,y,z));

    return 0;
}
```
`Vector3(x,y,z)`に変換すると呼び出せますが、毎回変換を書くのは面倒ですよね。

出来れば、`Output_Vector3(x,y,z)`と呼び出したいですね。

## [Back](merit_0_3.md)　[Home](merit_0_0.md)　[Next](merit_0_5.md)　
