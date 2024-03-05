### [<i class="fa fa-fw fa-home"></i>](../../../README.md)/[quiet](../../quiet.md)/[N_Array](N_Array.md)/args_size

# quiet::N_Array::args_size

``` C++
template<class T_Base_Type, class ...T_Args>
static constexpr int args_size =
    N_Tuple::N_Apply::I_Type_Chack<
	tuple_t<N_Tuple::N_Apply::S_Infinite_Args<T_Base_Type>>,
	tuple_t<T_Args...>>::value;
```
***
## 仕様
`T_Args...` から`T_Base_Type`が作れる数を返す。
不適切な型の場合は`-1`を返す
***
## 備考
なお、判定は[構造化束縛](https://cpprefjp.github.io/lang/cpp17/structured_bindings.html)が可能な型は、分解後の型に置き換え、又はその逆の動作を用いて行う
***
## 例
``` C++
#include"Array.h"
using quiet::N_Array::args_size;
int main()
{
    std::cout<< args_size<int,Array<int,3>> <<std::endl;

    std::cout<< args_size<Array<float,3>,Array<int,3>> <<std::endl;
    
    std::cout<< args_size<Array<int,3>,int,int,int> <<std::endl;
    
    std::cout<< args_size<Array<float,9>,Array<Array<int,3>,3>> <<std::endl;
    
    std::cout<< args_size<Array<int,std::string> <<std::endl;

    return 0;
}
```
***
## 出力
```
3
1
1
1
-1
```
***
## 関連
[Array](../Array.md)    
[N_Array](N_Array.md)    
[Array::constructor](../constructor.md)    
[N_Tuple::構造化束縛](../Tuple/N_Tuple/構造化束縛.md)   
