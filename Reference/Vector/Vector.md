### [README](../../README.md)/[quiet](../quiet.md)/Vector

``` C++
using Vector2 = quiet::N_Vector::S_Core<float, 2>;

using Vector3 = quiet::N_Vector::S_Core<float, 3>;

using Vector4 = quiet::N_Vector::S_Core<float, 4>;
```

## 概要
`Vector`は[Array](../Array/Array.md)を元に拡張され、要素数が`2～4`の時にメンバー変数[`x`,`y`,`z`,`w`]が提供される。

---

<details>
    <summary style="display: flex; align-items: center; cursor: pointer;">
        <span id="triangle-icon" style="margin-right: 10px;"></span>
        <h2><u>Vector2</u></h2>
    </summary>

### 構築/破棄
|名前| 説明|
|:-------------------------------:|:--------------:|
| [(constructor)](../Array/constructor.md) |型`float`,要素数`2`の[Array](../Array/Array.md)と同様|

## メンバー変数
| 名前|説明 |
|:-|:-|
|ary|型`float`,要素数`2`の[Array](../Array/Array.md)|
| x| aryの0番目の要素|
| y| aryの1番目の要素|


## 関数
| 名前|説明 |
|:-|:-|
|get|`ary`の`I`番目の要素数を取得する|
|operator[]|`ary`の`I`番目の要素数を取得する|

</details>


<details>
    <summary style="display: flex; align-items: center; cursor: pointer;">
        <span id="triangle-icon" style="margin-right: 10px;"></span>
        <h2><u>Vector3</u></h2>
    </summary>

### 構築/破棄
|名前| 説明|
|:-------------------------------:|:--------------:|
| [(constructor)](../Array/constructor.md) |型`float`,要素数`3`の[Array](../Array/Array.md)と同様|

## メンバー変数
| 名前|説明 |
|:-|:-|
|ary|型`float`,要素数`3`の[Array](../Array/Array.md)|
| x| aryの0番目の要素|
| y| aryの1番目の要素|
| z| aryの2番目の要素|

## 関数
| 名前|説明 |
|:-|:-|
|get|`ary`の`I`番目の要素数を取得する|
|operator[]|`ary`の`I`番目の要素数を取得する|

</details>

<details>
    <summary style="display: flex; align-items: center; cursor: pointer;">
        <span id="triangle-icon" style="margin-right: 10px;"></span>
        <h2><u>Vector4</u></h2>
    </summary>

### 構築/破棄
|名前| 説明|
|:-------------------------------:|:--------------:|
| [(constructor)](../Array/constructor.md) |型`float`,要素数`4`の[Array](../Array/Array.md)と同様|

## メンバー変数
| 名前|説明 |
|:-|:-|
|ary|型`float`,要素数`4`の[Array](../Array/Array.md)|
| x| aryの0番目の要素|
| y| aryの1番目の要素|
| z| aryの2番目の要素|
| w| aryの3番目の要素|

## 関数
| 名前|説明 |
|:-|:-|
|get|`ary`の`I`番目の要素数を取得する|
|operator[]|`ary`の`I`番目の要素数を取得する|
</details>

## 備考
`int`を管理する
`Vector2Int`,`Vector3Int`,`Vector4Int`

`bool`を管理する
`Vector2Bool`,`Vector3Bool`,`Vector4Bool`

任意の型を管理する
`Vector2All<T>`,`Vector3All<T>`,`Vector4All<T>`


[std::tuple]:https://cpprefjp.github.io/reference/tuple/tuple.html

## 関連
[Array](../Array/Array.md)   
[Array::constructor](../Array/constructor.md)   
