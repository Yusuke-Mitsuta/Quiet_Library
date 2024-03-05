### [README](../../README.md)/[quiet](../quiet.md)/[Array](Array.md)/推論補助

# quiet::Array::推論補助
``` C++
template<class _Ty2, class ..._Ty3>
    requires (N_Array::args_size<_Ty2, _Ty3...> >= 0)
Array(_Ty2 t, _Ty3 ...ts)->
    Array<_Ty2, N_Array::args_size<_Ty2, _Ty2, _Ty3...>>;
```
***
## 概要
`_Ty2`型の要素を[`N_Array::args_size<_Ty２, _Ty3...>`](N_Array/args_size.md)個だけ、受け取れる型[`Array`](Array.md)を推論する
***
## 例
``` C++
#include"Array.h"
using namespace quiet;
int main()
{
    //Array<int,3>
    Array ary_int3(1, 2, 3);
    
    //Array<float,3>
    Array ary_float3(1.0f, 2, 3);
    
    //Array<Array<int,3>,3>
    Array ary_int3_3(ary_int3, ary_float3, 7, 8.0f, 9.0);
    
    //[int]->[Array<int,3>]への暗黙的な型変換は禁止
    //Array ary_int3_2(ary_int3, 0);
}
```
***
## 関連
[Array](Array.md)    
[Array::constructor](constructor.md)    
[N_Array::args_size](N_Array/args_size.md)    
[N_Tuple::構造化束縛](../Tuple/N_Tuple/構造化束縛.md)
