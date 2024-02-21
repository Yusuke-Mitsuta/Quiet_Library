# quiet::Array

``` C++
namespace quiet {
  template <class T, std::size_t N>
  struct Array;
}
```

## 概要
`Array`は標準ライブラリ`std::array`を元に**コンストラクタ**、**クラステンプレートの推論補助**が拡張されたクラスである。


---

## メンバー関数
### 構築/破棄
|                               名前                                |      説明      |
|:-----------------------------------------------------------------:|:--------------:|
| <a href="./constructor.md" target="_self">(constructor)</a> | コンストラクタ |
|   <a href="/@Mitsuta-Hal-Osaka/quiet-Array-operator-assign" target="_self">operator=</a>   |   代入演算子  |


### 要素へのアクセス
|                               名前                                |      説明      |
|:-----------------------------------------------------------------:|:--------------:|
|<a href="/@Mitsuta-Hal-Osaka/quiet-Array-get" target="_self">get</a>     |   静的な要素にアクセスする |


---

## メンバー型
|                               名前                                |      説明      |
|:-----------------------------------------------------------------:|:--------------:|
|<a href="/@Mitsuta-Hal-Osaka/quiet-Array-tuple" target="_self">tuple</a>|`Array`と互換性のある<a href="/@Mitsuta-Hal-Osaka/quiet-tuple_t" target="_self">quiet::tuple_t型</a>を示す　|



---

## 推論補助
|                               名前                                |      説明      |
|:-----------------------------------------------------------------:|:--------------:|
|<a href="/@Mitsuta-Hal-Osaka/quiet-Array-deduction_guide" target="_self">(deduction_guide)</a>|クラステンプレートの推論補助 |