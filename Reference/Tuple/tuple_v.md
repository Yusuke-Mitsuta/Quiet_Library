### [README](../../README.md)/[quiet](../quiet.md)/tuple_v

# quiet::tuple_v
``` C++
template<auto ...t_Value>
struct tuple_v;
```

## 概要
`tuple_v`は、テンプレートの値を操作する型である
***
## 備考
`tuple_v`は、[`tuple_t`](tuple_t.md)と同じ手段で操作を行う
***
## メンバー変数
| 名前      | 説明                                                        |
| --------- |:----------------------------------------------------------- |
| [size](N_Tuple/S_Size/size.md)| 型の要素数を示す|
| [head_size](N_Tuple/S_Size/head_size.md) | [tuple_vp](tuple_vp.md)と統一運用する為、常に`0`が返る      |
| [tail_size](N_Tuple/S_Size/tail_size.md) | [tuple_vp](tuple_vp.md)と統一運用する為、常に[[size](N_Tuple/S_Size/size.md) - 1 ]が返る |
| value    | 先頭の値 |
| next_v   | 先頭の次の要素の値 |
| prev_v   | 無効な値として[invalid](../invalid_t.md)が返|
| front_v  | 先頭の要素の値  |
| back_v | 最後の要素の値|
***
## メンバー型
| 名前     | 説明   |
| -------- |:------- |
| head     | [tuple_tp](tuple_tp.md)と統一運用する為、常に`tuple_t<>`が返る            |
| tail     | [tuple_tp](tuple_tp.md)と統一運用する為、常に先頭の要素を除去した型が返る |
| next     | 先頭の次の要素を選択した[tuple_tp](tuple_tp.md)が返る                 |
| prev     | 前の要素が選択出来ない為、無効な型として[invalid_t](../invalid.md)を生成、選択した[tuple_tp](tuple_tp.md)が返る |
| front    | 先頭の要素を選択する|
| back     | 最後の要素を選択する|
| remove   | 選択している型を除去する|
| reverse  | 型の並び順を反転させる|
| create_p | 先頭の要素を選択した[tuple_vp](tuple_vp.md)型|
| remove_p | [tuple_vp](tuple_vp.md)専用のメンバー型、使用時は現在と同じ型を返す|
***
## 関連
[tuple_t](tuple_t.md)    
[tuple_vp](tuple_vp.md)    
[N_Tuple](N_Tuple/N_Tuple.md)    
[S_Size](N_Tuple/S_Size.md) 
