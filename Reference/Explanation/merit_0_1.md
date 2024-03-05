### [README](../../README.md)/quietを利用するメリット

***
1. `float`の要素を3つ持つ型`Vector3`を作成するとします。
2. 引数に`Vector3`型を一つ受け取り、値を出力する関数として`Output_Vector3`を作成します。
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
    return 0;
}
``` 
## [Back](merit_0_0.md)　[Home](merit_0_0.md)　[Next](merit_0_2.md)　
