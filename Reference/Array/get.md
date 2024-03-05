### [README](../../README.md)/[quiet](../quiet.md)/[Array](Array.md)/get

# quiet::Array::get

``` C++
template<size_t I>
constexpr T& get()
{
    return std::array<T, N>::_Elems[I];
}
```
***
## 概要
`Array<T,N>`に対して、`N`番目の要素の参照を取得する。
***
## 例
``` C++
#include"Array.h"
using namespace quiet;
int main()
{
    Array<int,3> ary_int3(1,2,3);
    
    std::cout<< ary_int3.get<0> <<std::endl;
    std::cout<< ary_int3.get<1> <<std::endl;
    std::cout<< ary_int3.get<2> <<std::endl;
    return 0;
}
```
***
## 出力
```
1
2
3
```
***
## 関連
[Array](Array.md)    
[std::get(quiet)](../Tuple/N_Tuple/get.md)    
