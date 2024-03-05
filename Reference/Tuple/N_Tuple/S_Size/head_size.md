### [README](../../../../README.md)/[quiet](../..//..quiet.md)/[N_Tuple](../N_Tuple.md)/[S_Size](../S_Size.md)/head_size

# quiet::N_Tuple::S_Size::head_size

```　C++
static constexpr size_t head_size;
```

## 概要
[[`tuple_tp`](../tuple_tp.md),[`tuple_vp`](../tuple_vp.md)]型の、選択している要素より**前に存在する**要素の数
***
## 備考
[[`tuple_tp`](../tuple_tp.md),[`tuple_vp`](../tuple_vp.md)]**以外**の型では、`0`を返す
***
## 例
```　C++
#include"Tuple.h"
using namespace quiet;
int main()
{
    using tuple_1 = tuple_tp<tuple_t<int,int>,float,tuple_t<double>>;
    std::cout<<N_Tuple::S_Size<tuple_1>::head_size <<std::endl;

    using tuple_2 = tuple_tp<tuple_t<>,float,tuple_t<double>>;
    std::cout<<N_Tuple::S_Size<tuple_2>::head_size <<std::endl;

    using tuple_3 = tuple_t<int,int,float,double>;
    std::cout<<N_Tuple::S_Size<tuple_3>::head_size <<std::endl;
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