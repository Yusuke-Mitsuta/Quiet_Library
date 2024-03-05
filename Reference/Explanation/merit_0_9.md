
## quietを利用するメリット
`クラス`、`関数`の引数が、構成される要素と互換性がある値を、受け取れる様になり、オーバーロード、キャストの手間を削減出来ます。

***

### **quiet**を利用する、複雑なパターンについて

使用する型  
[quiet::Function][Function]     
[quiet::Vector4](../Vector/Vector.md#Vector4)       
[quiet::Vector4All](../Vector/Vector.md#Vector4)   
***

1. `Vector4`を4つ受け取る関数を`Output_Vector4x4`とします。
2. `Output_Vector4x4`に互換性を持たせる為に[quiet::Function][Function]でラッピングし、`fn_Output_Vector4x4`を作成します。

``` C++
#include<iostream>

#include"Function.h"
#include"Vector.h"
using namespace quiet;

void Output_Vector4x4(Vector4 vec4_1,Vector4 vec4_2,Vector4 vec4_3,Vector4 vec4_4)
{
    std::cout << vec4_1.x<<"," << vec4_1.y << "," << vec4_1.z << "," << vec4_1.w << std::endl;
    std::cout << vec4_2.x<<"," << vec4_2.y << "," << vec4_2.z << "," << vec4_2.w << std::endl;
    std::cout << vec4_3.x<<"," << vec4_3.y << "," << vec4_3.z << "," << vec4_3.w << std::endl;
    std::cout << vec4_4.x<<"," << vec4_4.y << "," << vec4_4.z << "," << vec4_4.w << std::endl;
}

//関数の引数に互換性を持たせる為のラッピング
static Function fn_Output_Vector4x4(&Output_Vector4x4);

int main()
{
    fn_Output_Vector4x4(
        1.0f, 2.0f, 3.0f,4.0f,
        5.0f, 6.0f, 7.0f,8.0f,
        9.0f, 10.0f, 11.0f,12.0f,
        13.0f, 14.0f, 15.0f,16.0f);

    Vector4 vec4_1(1.0f, 2.0f, 3.0f,4.0f);
    Vector4 vec4_2(5.0f, 6.0f, 7.0f,8.0f);
    Vector4 vec4_3(9.0f, 10.0f, 11.0f,12.0f);
    Vector4 vec4_4(13.0f, 14.0f, 15.0f,16.0f);

    fn_Output_Vector4x4(vec4_1, vec4_2, vec4_3, vec4_4);

    Vector4All<Vector4> vec4X4(vec4_1, vec4_2, vec4_3, vec4_4);

    fn_Output_Vector4x4(vec4X4);

    Vector3 vec3_1(1.0f, 2.0f, 3.0f);
    Vector3 vec3_2(4.0f,5.0f, 6.0f);
    Vector3 vec3_3(7.0f,8.0f,9.0f);
    Vector3 vec3_4(10.0f, 11.0f,12.0f);
    Vector3 vec3_5(13.0f, 14.0f, 15.0f);

    fn_Output_Vector4x4(vec3_1,vec3_2,vec3_3,vec3_4,vec3_5,16.0f);
    fn_Output_Vector4x4(vec3_1,vec3_2,7.0f,8.0f,9.0f,vec3_4,vec3_5,16.0f);

    return 0;
}
```
`Vector4`を4つ引数に取る場合でも同様の考え方を行い、`float`型を4つ受け取る`Vector4`、を4つ取る為、`float`型の要素16つと考えれます。

よって同じ様に、引数の`float`型の要素が合計16になる**全てのパターン**で関数を呼び出せます。

## [Back](merit_0_8.md)　[Home](merit_0_0.md)


[Function]:../Function/Function.md