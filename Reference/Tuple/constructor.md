### [README](../../README.md)/[quiet](../quiet.md)/[Tuple](Tuple.md)/constructor

# quiet::Tuple::constructor

``` C++
template<class T_Tuple = tuple, class ...T_Args>
    requires requires
{
    requires same_as<T_Tuple, tuple_t<T_Args...>>;
}
constexpr Tuple(T_Args... args):
    std::tuple<T_Args...>(args...)
{}

template<class T_Tuple =tuple, class ...T_Args>
    requires requires
{
    requires N_Tuple::N_Apply::Chack<tuple, T_Args...>();
    requires same_as_not<T_Tuple, tuple_t<T_Args...>>;
}
constexpr Tuple(T_Args... args) :
    std::tuple<_Types...>({Apply<std::tuple<_Types...>>(args...)})
    {}
    
```
***
## 概要
**要求する型**と**供給する型**の[構成する型の要素](N_Tuple/Apply.md#構成される要素とは)に互換性があること
***
## 制限
#### 以下のいずれかを満たす事
1. `_Types...`と`T_Args...`の型が一致する事
1. [Apply](N_Tuple/Apply.md)にて構築可能なこと
***
## 例
``` C++
#include"Array.h"
#include"Tuple.h"
using namespace quiet;

int main()
{
    Tuple tuple_int_3(1, 3, 5);
    Array ary_float_3(2.0f, 4.0f, 6.0f);

    std::string str = { "str" };

    //要求する型:[ int,int,int ,[ int , int , int]]
    //供給する型:[[int,int,int],[float,float,float]]
    Tuple<int, int, int, Array<int, 3>> r_tuple_1(tuple_int_3, ary_float_3);

    //要求する型:[[int,int],int , int  ,[int , int]]
    //供給する型:[[int,int ,int],[float,float,float]]
    Tuple<Array<float, 2>,int, int, Array<int,2>> r_tuple_2(tuple_int_3, ary_float_3);

    //要求する型:[int,std::string,int]
    //供給する型:[int,std::string,int]
    Tuple<int,std::string, int> r_tuple_3(0,str, 1);

    //要求する型:[[int,int],std::string,int]
    //供給する型:[ int,[int,std::string,int]]
    Tuple<Array<int,2>,std::string,int> r_tuple_4(0,r_tuple_3);
    return 0;
}
```
***
## 関連
[Tuple](Tuple.md)   
[Array](../Array/Array.md)    
[Apply](N_Tuple/Apply.md)  