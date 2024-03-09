### [README](../../README.md)/[quiet](../quiet.md)/[Array](Array.md)/constructor

# quiet::Array::constructor

``` C++
template< class ..._Ty2>
    requires ( convertible_from_and<_Ty1, _Ty2...> &&
        (sizeof...(_Ty2) == static_cast<int>(N) ))
constexpr Array(_Ty2... t);

template< class ..._Ty2>
    requires (convertible_from_nand<_Ty1, _Ty2...> &&
	(N_Array::args_size<_Ty1, _Ty2...> == static_cast<int>(N)) )
constexpr Array(_Ty2... t);


template<class ..._Ty2>
    requires ( (N_Array::args_size<_Ty1, _Ty2...> > 0) &&
        (N_Array::args_size<_Ty1, _Ty2...> < static_cast<int>(N))) &&
    requires
    {
        _Ty1{};
    }
explicit constexpr Array(_Ty2 ...t);
    
```
***
## 制限
#### 以下のいずれかを満たす事
1. `T`と互換性がある型を`N`個の場合
1. [`N_Array::args_size<_Ty1, _Ty2...>`](N_Array/args_size.md)が`N`と一致する場合
1. [`N_Array::args_size<_Ty1, _Ty2...>`](N_Array/args_size.md)が`N`より小さい、かつ`T`がデフォルト構築可能な場合
1. `T`がデフォルト構築可能な場合
***
## 備考
* `条件2`,`条件3`は[`N_Tuple::I_Apply_Action`](../Tuple/N_Tuple/Apply.md)にて`_Ty2...`を適切に変換し、`std::array`を構築する
***
## 例
``` C++
#include"Array.h"
using namespace quiet;

int main()
{
    Array<int, 3> ary_int3_1(1, 2.0f, 3.0);//[1, 2.0f, 3.0]->[1,2,3]
    Array<int, 3> ary_int3_2(1);//[1]->[1,int{},int{}]->[1,0,0]
    //Array<int, 3> ary_int3_3(1, 2.0f, 3.0,4);//引数が多い為、エラー

    Array<float,3> ary_float3_1(ary_int3_1);//[1,2,3]->[1.0f,2.0f,3.0f]

    Array<double, 9> ary_double9_1(ary_int3_1, ary_float3_1, 7, 8.0f, 9.0);//[1,2,3,1.0f,2.0f,3.0f,7,8.0f,9.0]->[1.0,2.0,3.0,1.0,2.0,3.0,7.0,8.0,9.0]

    Array<Array<int,3>, 3> ary_int33_1(ary_int3_1, ary_float3_1, 7, 8.0f, 9.0); //[1, 2, 3, 1.0f, 2.0f, 3.0f, 7, 8.0f, 9.0] ->[[1, 2, 3],[1, 2, 3],[7, 8, 9]]
    Array<Array<int,3>, 2> ary_int32_1(ary_int3_1);//[1, 2, 3] ->[[1, 2, 3],[int{},int{},int{}]]->[[1, 2, 3],[0,0,0]]

    //Array<Array<int,3>, 2> ary_int32_2(ary_int3_1,0);//[int]から Array<int,3>へ変換しようとするが、デフォルト構築を伴う暗黙的な型変換は、禁止されている為エラーとなる
    Array<int,6> ary_int6_1(ary_int3_1,0);//似たような場合だが、上記と異なり[int]から Array<int,3>へ変換が行われない為、可となる

    return 0;
}
```
***
## 関連
[Array](Array.md)    
[N_Array::args_size](N_Array/args_size.md)    
