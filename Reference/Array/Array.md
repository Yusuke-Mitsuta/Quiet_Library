### [README](../../README.md)/[quiet](../quiet.md)/Array

###### 継承[`std::array`](https://cpprefjp.github.io/reference/array/array.html)
# quiet::Array 
``` C++
namespace quiet {
  template <class T, std::size_t N>
  struct Array;
}
```

## 概要
`Array`は標準ライブラリ[`std::array`](https://cpprefjp.github.io/reference/array/array.html)を元に**コンストラクタ**、**クラステンプレートの推論補助**が拡張されたクラスである。


---

## メンバー関数
### 構築/破棄
|              名前               |      説明      |
|:-------------------------------:|:--------------:|
| [(constructor)](constructor.md) | コンストラクタ |
|  [operator=](erator-assign.md)  |   代入演算子   |


### 要素へのアクセス
|     名前      |           説明           |
|:-------------:|:------------------------:|
| [get](get.md) | 静的な要素にアクセスする |


***

## メンバー型
|       名前        |                                説明                                |
|:-----------------:|:------------------------------------------------------------------:|
| [tuple](tuple.md) | `Array`と互換性のある[quiet::tuple_t](../Tuple/tuple_t.md)型を示す |

---

## 推論補助
|                   名前                   　|             説明             |
|:-----------------------------------------:|:----------------------------:|
| [deduction_guide](deduction_guide.md) | クラステンプレートの推論補助 |

***
## 関連　
[Vector](../Vector/Vector.md)   
[std::array](https://cpprefjp.github.io/reference/array/array.html)   
[std::get(quiet)](../Tuple/N_Tuple/get.md)  