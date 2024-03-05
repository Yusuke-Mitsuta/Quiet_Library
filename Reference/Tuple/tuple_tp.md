### [README](../../README.md)/[quiet](../quiet.md)/tuple_tp

# quiet::tuple_tp

``` C++
template<N_Tuple::same_as_tuple_t T_Head, class T, N_Tuple::same_as_tuple_t T_Tail>
struct tuple_tp;
```

## 概要
`tuple_tp`は[`tuple_t`](tuple_t.md)の型操作に関するクラスであり、型リストの中から要素を１つ選択し、保持する事が出来る。
***
## メンバー変数


| 名前      |   説明  |
| --------- |:----|
|[size](N_Tuple/S_Size/size.md)  |  型の要素数を示す  |
| [head_size](N_Tuple/S_Size/head_size.md)  |  選択している要素より前に存在する要素の数  |
| [tail_size](N_Tuple/S_Size/tail_size.md)| 選択している要素より後ろに存在する要素の数 |

***
## メンバー型
| 名前     | 説明                                                              |
| -------- |:-- |
| type     | 選択している型                                                    |
| head     | 選択している型より前の型全てを[tuple_t](tuple_t.md)に格納した型   |
| tail     | 選択している型より後ろの型全てを[tuple_t](tuple_t.md)に格納した型 |
| next     | 選択している型を一つ後ろに進める                                  |
| next_t   | 選択している型を一つ後ろに進めた際に選択する型                    |
| prev     | 選択している型を一つ前に進める                                    |
| prev_t   | 選択している型を一つ前に進めた際に選択する型                      |
| front    | 先頭の要素を選択する                                              |
| front_t  | 先頭の要素の型                                                    |
| back     | 最後の要素を選択する                                              |
| back_t   | 最後の要素の型                                                    |
| remove   | 選択している型を除去する                                          |
| reverse  | 型の並び順を反転させる                                            |
| create_p | [tuple_t](tuple_t.md)専用のメンバー型、使用時は現在と同じ型を返す |
| remove_p | 選択出来る機能を排除した[tuple_t](tuple_t.md)型                   |
***
## 関連
[tuple_t](tuple_t.md)    
[N_Tuple](N_Tuple/N_Tuple.md)    
[S_Size](N_Tuple/S_Size.md) 