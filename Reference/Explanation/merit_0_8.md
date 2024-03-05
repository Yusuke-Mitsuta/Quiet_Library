
## quietを利用するメリット
`クラス`、`関数`の引数が、構成される要素と互換性がある値を、受け取れる様になり、オーバーロード、キャストの手間を削減出来ます。

***

### **quiet**を利用する、複雑なパターンについて

使用する型  
[quiet::Function][Function]     
[quiet::Vector4](../Vector/Vector.md#Vector4)   
[quiet::Vector4All](../Vector/Vector.md#Vector4) 
***

1. `4行4列`の行列を受け取る型`Vector4All<Vector4>`とします。
2. `4行4列`を受け取る関数を`Output_Vector4x4`とします。
3. `Output_Vector4x4`に互換性を持たせる為に[quiet::Function][Function]でラッピングし、`fn_Output_Vector4x4`を作成します。

``` C++
#include<iostream>

#include"Function.h"
#include"Vector.h"
using namespace quiet;

void Output_Vector4x4(Vector4All<Vector4> vec4x4)
{
    std::cout << vec4x4.x.x<<"," << vec4x4.x.y << "," << vec4x4.x.z << "," << vec4x4.x.w << std::endl;
    std::cout << vec4x4.y.x<<"," << vec4x4.y.y << "," << vec4x4.y.z << "," << vec4x4.y.w << std::endl;
    std::cout << vec4x4.z.x<<"," << vec4x4.z.y << "," << vec4x4.z.z << "," << vec4x4.z.w << std::endl;
    std::cout << vec4x4.w.x<<"," << vec4x4.w.y << "," << vec4x4.w.z << "," << vec4x4.w.w << std::endl;
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
`4行4列`を表す`Vector4All<Vector4>`は、`float`型の要素を4つ`Vector4`、を4つ持つ型であり、`Vector4All<Vector4>`は、`float`型の要素16つ持つと考えれます。

よって、引数の`float`型の要素が合計16になる**全てのパターン**で関数を呼び出せます。
***
次は、関数が複数の引数を取る場合について

## [Back](merit_0_7.md)　[Home](merit_0_0.md)　[Next](merit_0_9.md)　


[Function]:../Function/Function.md