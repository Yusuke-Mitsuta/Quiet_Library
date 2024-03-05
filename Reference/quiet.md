### [README](../README.md)/quiet

# quietライブラリ


|名前|説明|
|:-|:-|
|[Array](Array/Array.md)| 標準ライブラリ`std::array`を元にコンストラクタ、クラステンプレートの推論補助が拡張されたクラス |
|[Vector](Vector.md)|`Vector`は[Array](../Array/Array.md)を元に拡張され、要素数が`2～4`の時にメンバー変数[`x`,`y`,`z`,`w`]が提供される。|
|[Tuple](Tuple/Tuple.md)|標準ライブラリ`std::tuple`を元にコンストラクタが拡張されたクラス|
|[Function](Function/Function.md)|`Function`は標準ライブラリ`std::function`から**複数の関数オブジェクト**、**引数の一部バインド**機能が追加されたクラス|
|[Apply](Tuple/N_Tuple/Apply.md)|`Apply`に渡されたテンプレート、引数によって、要求されている型を認識し、引数を要求されている型にそって変形し、`関数オブジェクトの実行`,`クラスの生成`,`配列への追加`を行う。|

***
## 補助用の名前空間、クラス、関数
|名前|説明|
|:-|:-|
|[N_Array](Array/N_Array/N_Array.md) |Arrayに関わる補助コード|
|[tuple_t](Tuple/tuple_t.md)|　テンプレートの型操作用のリストクラス|
|[tuple_tp](Tuple/tuple_t.md)  |  テンプレートの型操作用クラス|
|[tuple_v](Tuple/tuple_v.md)   |  テンプレートの値操作用のリストクラス |
|[tuple_vp](Tuple/tuple_vp.md) |  テンプレートの値操作用のクラス |
|[N_Tuple](Tuple/N_Tuple/N_Tuple.md)| tupleに纏わる補助クラス が所属する名前空間|
|[invalid](invalid_t.md)|無効値を示す|

