### [README](../../../README.md)/[quiet](../../quiet.md)/N_Tuple

# quiet::N_Tuple

## 概要
`N_Tuple`は[`tuple_t`](../tuple_tp.md),[`tuple_tp`](../tuple_tp.md)に関連するクラス、関数が収められている名前空間である。
***
## 関数

| 名前              | 説明 |
|:----------------- |:---- |
| [Apply](Apply.md) | 変数を指定された型に適切に変形し、クラスの生成,関数の実行,配列の初期化を実施する。  |
***
## クラス
| 名前 | 説明 |
|:- |:-|
|[I_Element](I_Element.md)|[<u>tuple及び、tupleと互換性がある型</u>][1]から、`I`番目の要素を取得する|
|[S_Size](S_Size.md)|[[`tuple_t`](../tuple_t.md),[`tuple_tp`](../tuple_tp.md),[`tuple_v`](../tuple_v.md),[`tuple_vp`](../tuple_vp.md)]型の、要素数を取得する|
|[I_Repeat_Multiple](I_Repeat_Multiple.md)|`T`が`N`個存在する[`tuple_t`](../tuple_t.md)型を生成する|

***

## tuple及び互換性について
#### 以下のいずれかを満たす事
1. [[`tuple_t`](../tuple_t.md),[`tuple_tp`](../tuple_tp.md),[`tuple_v`](../tuple_v.md),[`tuple_vp`](../tuple_vp.md)]型である

1. メンバー型に`tuple`が宣言されている、
　　かつその型が条件１を満たす
1. [`N_Tuple::S_Parameter`](Parameter.md)にて特殊化されている、
　　かつ[`N_Tuple::S_Parameter::tuple`](Parameter.md#メンバー型)が条件１を満たす
***
## 関連
[tuple_t](../tuple_t.md)    
[tuple_tp](../tuple_tp.md)    

[1]:#tuple及び互換性について "tuple及び互換性について&#13;&#10;　　以下のいずれかを満たす事&#13;&#10;1.[tuple_t,tuple_tp,tuple_v,tuple_vp]型である&#13;&#10;&#13;&#10;2.メンバー型に[tuple]が宣言されている、&#13;&#10;    かつその型が条件１を満たす&#13;&#10;&#13;&#10;3.[N_Tuple::S_Parameter]にて特殊化されている、&#13;&#10;    かつ[N_Tuple::S_Parameter::tuple]が条件１を満たす"