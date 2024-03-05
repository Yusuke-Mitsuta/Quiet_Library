### [README](../../../README.md)/[quiet](../../quiet.md)/[N_Tuple](N_Tuple.md)/I_Element

# quiet::N_Tuple::I_Element

```　C++
template<size_t _Index, class T_Tuple>
struct I_Element;
```

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
">tuple及び、tupleと互換性がある型</span></a>から`_Index`番目の要素を取得する。
***
## メンバー変数
|名前|説明|
|:-|:-|
|value | [`tuple_v`](../tuple_v.md),[`tuple_vp`](../tuple_vp.md)の場合、`_Index`番目の値を取得する|
***
## メンバー型
|名前|説明|
|:-|:-|
|type| [`tuple_t`](../tuple_t.md),[`tuple_tp`](../tuple_tp.md)の場合、`_Index`番目の型を取得する|
***
## 関連
[std::tuple_element (quiet)](tuple_element.md) 