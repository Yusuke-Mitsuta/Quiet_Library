### [README](../../../../README.md)/[quiet](../..//..quiet.md)/[N_Tuple](../N_Tuple.md)/[S_Size](../S_Size.md)/tail_size

# quiet::N_Tuple::S_Size::head_size

```　C++
static constexpr size_t head_size;
```

## 概要
[[`tuple_tp`](../tuple_tp.md),[`tuple_vp`](../tuple_vp.md)]型の、選択している要素より**後ろに存在する**要素の数
***
## 備考
1. [[`tuple_t`](../tuple_tp.md),[`tuple_v`](../tuple_vp.md)]型では、[[S_Size::size](size.md) - 1]の値を返す
2. [[`tuple_t`](../tuple_t.md),[`tuple_tp`](../tuple_tp.md),[`tuple_v`](../tuple_v.md),[`tuple_vp`](../tuple_vp.md)]以外の型では、`0`を返す
***
## 例
```　C++
#include"Tuple.h"
using namespace quiet;
int main()
{
    using tuple_1 = tuple_tp<tuple_t<int>,float,tuple_t<double,double>>;
    std::cout<<N_Tuple::S_Size<tuple_1>::tail_size <<std::endl;

    using tuple_2 = tuple_tp<tuple_t<int>,float,tuple_t<>>;
    std::cout<<N_Tuple::S_Size<tuple_2>::tail_size <<std::endl;

    using tuple_3 = tuple_t<int,int,float,double>;
    std::cout<<N_Tuple::S_Size<tuple_3>::tail_size <<std::endl;
    return 0;
}
```
***
## 出力
```
2
0
0
```
***
## 関連
[S_Size](../S_Size.md)  
[`tuple_t`](../tuple_t.md)  
[`tuple_tp`](../tuple_tp.md)    
[`tuple_v`](../tuple_v.md)  
[`tuple_vp`](../tuple_vp.md)    
[std::tuple_size(quiet)](../tuple_size.md)  