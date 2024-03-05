### [README](../../../README.md)/[quiet](../../quiet.md)/[N_Tuple](N_Tuple.md)/tuple_element

# std::tuple_element

```　C++
template <size_t I, class T>
    requires requires
{
    requires quiet::is_invalid_not<typename quiet::N_Tuple::S_Parameter<T>::tuple>;
}
struct tuple_element<I, T> 
```
***
## 概要
<a href=N_Tuple.md#tuple及び互換性について 
style="text-decoration:underline;" 
span title="tuple及び互換性について
    以下のいずれかを満たす事
1.[tuple_t,tuple_tp,tuple_v,tuple_vp]型である&#13;&#10;
2.メンバー型に[tuple]が宣言されている、
    かつその型が条件１を満たす&#13;&#10;
3.[N_Tuple::S_Parameter]にて特殊化されている、
    かつ[N_Tuple::S_Parameter::tuple]が条件１を満たす
">tuple及び、tupleと互換性がある</span></a>型</span></a>から`_Index`番目の要素を取得する。

