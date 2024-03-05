### [README](../../../../README.md)/[quiet](../..//..quiet.md)/[N_Tuple](../N_Tuple.md)/[S_Size](../S_Size.md)/size

# quiet::N_Tuple::S_Size::size

```　C++
static constexpr size_t size;
```

## 概要
[[`tuple_t`](../tuple_t.md),[`tuple_tp`](../tuple_tp.md),[`tuple_v`](../tuple_v.md),[`tuple_vp`](../tuple_vp.md)]型の要素数を取得する
***
## 備考
 [[`tuple_t`](../tuple_t.md),[`tuple_tp`](../tuple_tp.md),[`tuple_v`](../tuple_v.md),[`tuple_vp`](../tuple_vp.md)]型ない場合は`0`を返す
***
## 例
```　C++
#include"Tuple.h"
using namespace quiet;
int main()
{
    using tuple_1 = tuple_tp<tuple_t<int,int>,float,tuple_t<double>>;
    std::cout<<N_Tuple::S_Size<tuple_1>::size <<std::endl;

    using tuple_2 = tuple_tp<tuple_t<>,invalid_t,tuple_t<float,double>>;
    std::cout<<N_Tuple::S_Size<tuple_2>::size <<std::endl;

    using tuple_3 = tuple_t<int,int,float,double>;
    std::cout<<N_Tuple::S_Size<tuple_3>::size <<std::endl;

    using tuple_4 = tuple_t<>;
    std::cout<<N_Tuple::S_Size<tuple_4>::size <<std::endl;
    return 0;
}
```
***
## 出力
```
4
2
4
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
