### [README](../../README.md)/[quiet](../quiet.md)/[Array](Array.md)/tuple

# quiet::Array::tuple

``` C++
using tuple = N_Tuple::U_Repeat_Multiple<T, N>;
```
***
## 概要
[`N_Tuple::U_Repeat_Multiple<T, N>`](../Tuple/N_Tuple/I_Repeat_Multiple.md)にて、tuple_t< T... >の中に`T`が`N`個存在する型の定義
***
## 例
```　C++
#include"Array.h"
using namespace quiet;
int main()
{
    std::cout<< typeid(Array<int,3>::tuple).name() <<std::endl;
    return 0;
}
```
***
## 出力
```
struct quiet::tuple_t<int,int,int>
```
***
## 関連
[Array](Array.md)    
[`N_Tuple::U_Repeat_Multiple`](../Tuple/N_Tuple/I_Repeat_Multiple.md)