
### [README](../../README.md)/quietを利用するメリット

***
3. `Vector3`型を作成し、制作した関数`Output_Vector3`で出力します。
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
    Vector3 vec3 {1.0f,2.0f,3.0f};
    Output_Vector3(vec3);
    return 0;
}
```
ここまでは、なんの変哲もない通常のコードですね。

次は、`float`型3つで呼び出す事について考えていきます。

## [Back](merit_0_1.md)　[Home](merit_0_0.md)　[Next](merit_0_3.md)　
