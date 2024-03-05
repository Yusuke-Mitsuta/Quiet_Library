### [README](../../README.md)/[quiet](../quiet.md)/tuple_t

###### 継承[`std::tuple`](https://cpprefjp.github.io/reference/tuple/tuple.html)
# quiet::tuple_t
``` C++
template<class ...T_Types>
struct tuple_t;
```

## 概要
`tuple_t`は標準ライブラリ[`std::tuple`](https://cpprefjp.github.io/reference/tuple/tuple.html)を元に、型操作関連が拡張されたクラスである。
***
## メンバー変数
| 名前      | 説明 |
| --------- |:---- |
| [size](N_Tuple/S_Size/size.md)| 型の要素数を示す|
| [head_size](N_Tuple/S_Size/head_size.md) | [tuple_tp](tuple_tp.md)と統一運用する為、常に`0`が返る      |
| [tail_size](N_Tuple/S_Size/tail_size.md) | [tuple_tp](tuple_tp.md)と統一運用する為、常に[[size](N_Tuple/S_Size/size.md) - 1 ]が返る |
***
## メンバー型
| 名前     | 説明           |
| -------- |:-----------------|
| type     | 先頭の型  |
| head     | [tuple_tp](tuple_tp.md)と統一運用する為、常に`tuple_t<>`が返る            |
| tail     | [tuple_tp](tuple_tp.md)と統一運用する為、常に先頭の要素を除去した型が返る |
| next     | 先頭の次の要素を選択した[tuple_tp](tuple_tp.md)が返る                 |
| next_t   | 先頭の次の要素の型    |
| prev     | 前の要素が選択出来ない為、無効な型として[invalid_t](../invalid.md)を生成、選択した[tuple_tp](tuple_tp.md)が返る |
| prev_t   |   無効な型として[invalid_t](../invalid_t.md)が返る                          |
| front    | 先頭の要素を選択する                                                      |
| front_t  | 先頭の要素の型                                                            |
| back     | 最後の要素を選択する                                                      |
| back_t   | 最後の要素の型                                                            |
| remove   | 選択している型を除去する                                                  |
| reverse  | 型の並び順を反転させる                                                    |
| create_p | 先頭の要素を選択した[tuple_tp](tuple_tp.md)型                           |
| remove_p | [tuple_tp](tuple_tp.md)専用のメンバー型、使用時は現在と同じ型を返す|
***
## 関連
[tuple_tp](tuple_tp.md)    
[N_Tuple](N_Tuple/N_Tuple.md)    
[S_Size](N_Tuple/S_Size.md) 


