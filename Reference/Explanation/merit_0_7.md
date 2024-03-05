### [README](../../README.md)/quietを利用するメリット

***
## オーバーロードの削減しよう
**quiet**を利用し、オーバーロードを削減します。

使用する型      
[quiet::Function][Function]     
[quiet::Vector3](../Vector/Vector.md#Vector3)   
[quiet::Vector2](../Vector/Vector.md#Vector2)   
***
9. `Output_Vector3`のオーバーロードを全て削除します。
10.  `Output_Vector3`に互換性を持たせる為に[quiet::Function][Function]でラッピングし、`fn_Output_Vector3`を作成します。
11.  `Output_Vector3`で関数を呼び出してた所を、`fn_Output_Vector3`に置き換えます。
``` C++
#include<iostream>

#include"Function.h"
#include"Vector.h"
using namespace quiet;

void Output_Vector3(Vector3 vec3)
{
    std::cout << "x : " << vec3.x << " , y : " << vec3.y << " , z : " << vec3.z << std::endl;
}

//関数の引数に互換性を持たせる為のラッピング
static Function fn_Output_Vector3(&Output_Vector3);

int main()
{

    Vector3 vec3(1.0f, 2.0f, 3.0f);

    Vector2 vec2(1.0f, 2.0f);

    float x = 1.0f;
    float y = 2.0f;
    float z = 3.0f;

    fn_Output_Vector3(x, y, z);
    fn_Output_Vector3(vec3);
    fn_Output_Vector3(vec2, z);

    return 0;
}
```
**quiet**を利用により、非効率な**オーバーロード**が解消されたと思います。

次は、もっと複雑なパターンを見てみましょう

## [Back](merit_0_6.md)　[Home](merit_0_0.md)　[Next](merit_0_8.md)　


[Function]:../Function/Function.md