### [README](../../README.md)/[quiet](../quiet.md)/[Array](Array.md)/operator=

# quiet::Array::operator=

``` C++
constexpr void operator=(const std::convertible_to<T> auto& copy)
{
    std::array<T, N>::fill(static_cast<T>(copy));
}
```
***
## 概要
`Array<T,N>`に対して、[`std::convertible_to<T>`](https://cpprefjp.github.io/reference/concepts/convertible_to.html)が`true`となるとき、全ての値を指定されたに変更する
***
## 例
```　C++
#include"Array.h"
using namespace quiet;
int main()
{
    Array<float,3> ary_float3(1.0f,2.0f,3.0f);
    
    ary_float_3 = 5;
    
    std::cout<< ary_float_3[0] <<std::endl;
    std::cout<< ary_float_3[1] <<std::endl;
    std::cout<< ary_float_3[2] <<std::endl;
    return 0;
}
```
***
## 出力
```
5
5
5
```

***
## 関連
[Array](Array.md)    
[std::array::fill](https://cpprefjp.github.io/reference/array/array/fill.html)    
