### [README](../../README.md)/[quiet](../quiet.md)/Function

# quiet::Function
``` C++
namespace quiet {

template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function;
}
```

## 概要
`Function`は標準ライブラリ[`std::function`](https://cpprefjp.github.io/reference/functional/function.html)から**複数の関数オブジェクト**、**引数の一部バインド**機能が追加されたクラス

---

## メンバー関数
### 構築/破棄
|              名前               |              説明              |
|:-------------------------------:|:------------------------------:|
| [(constructor)](constructor.md) |         コンストラクタ         |


### 要素へのアクセス
|     名前      |           説明           |
|:-------------:|:------------------------:|
|  [operator->](operator-p.md)  　|     アロー演算子を定義する     |
|  [operator()](operator-fn.md)   | 関数オブジェクトにアクセスする |



---

## 推論補助
|                   名前                   　|     説明         |
|:-----------------------------------------:|:----------------------------:|
| [deduction_guide](deduction_guide.md) | クラステンプレートの推論補助 |
***

## 関連
[`std::function`](https://cpprefjp.github.io/reference/functional/function.html)    
[N_Tuple::構造化束縛](../Tuple/N_Tuple/構造化束縛.md)