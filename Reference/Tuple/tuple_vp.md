### [README](../../README.md)/[quiet](../quiet.md)/tuple_vp

# quiet::tuple_vp
``` C++
template<auto ...t_Value>
struct tuple_vp;
```

## 概要
`tuple_vp`は[`tuple_v`](tuple_v.md)の値操作に関するクラスであり、値リストの中から要素を１つ選択し、保持する事が出来る。
***
## 備考
`tuple_vp`は、[`tuple_tp`](tuple_tp.md)と同じ手段で操作を行う
***
## メンバー変数
| 名前      | 説明 |
| --------- |:-- |
|[size](N_Tuple/S_Size/size.md)  |  型の要素数を示す  |
| [head_size](N_Tuple/S_Size/head_size.md)  |  選択している要素より前に存在する要素の数  |
| [tail_size](N_Tuple/S_Size/tail_size.md)| 選択している要素より後ろに存在する要素の数 |
| value    | 先頭の値 |
| next_v   | 選択している型を一つ後ろに進めた際に選択する値 |
| prev_v   | 選択している型を一つ前に進めた際に選択する値|
| front_v  | 先頭の要素の値  |
| back_v | 最後の要素の値|
***
## メンバー型
| 名前     | 説明   |
| -------- |:------- |
| head     | 選択している型より前の型全てを[tuple_t](tuple_t.md)に格納した型   |
| tail     | 選択している型より後ろの型全てを[tuple_t](tuple_t.md)に格納した型 |
| next     | 選択している型を一つ後ろに進める                                  |
| prev     | 選択している型を一つ前に進める                                    |
| front    | 先頭の要素を選択する                                              |
| back     | 最後の要素を選択する                                              |
| remove   | 選択している型を除去する                                          |
| reverse  | 型の並び順を反転させる                                            |
| create_p | [tuple_v](tuple_v.md)専用のメンバー型、使用時は現在と同じ型を返す |
| remove_p | 選択出来る機能を排除した[tuple_v](tuple_v.md)型                   |
***
## 関連
[tuple_tp](tuple_tp.md)    
[tuple_v](tuple_v.md)    
[N_Tuple](N_Tuple/N_Tuple.md)    
[S_Size](N_Tuple/S_Size.md) 
