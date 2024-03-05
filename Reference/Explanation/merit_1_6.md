### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/クラスの生成に互換性を持たせる

***
8. `Vecto2`,`Vector3`のコンストラクタを全て削除します。
9.  `Vector2`,`Vector3`型に、コンストラクタの受け取る要素をそれぞれ[using tuple = quiet::tuple_t< ... >]で定義します。
10. それぞれ`template`で可変長引数が宣言された、コンストラクタを定義します。
11. それぞれ、宣言されたコンストラクタを**requires節**にて制限します。
12.  [9.]で宣言した順序に応じて変数を返す関数[`get<I>`]を定義します。

``` C++
#include<iostream>

struct Vector2
{
    float x;
    float y;

    template<class ...T>
    Vector2(T... t)
    {}
};

struct Vector3
{
    float x;
    float y;
    float z;


};

int main()
{
    Vector2 vec2(2.0f,3.0f);

    Vector3 vec3(1.0f,vec2);
    return 0;
}
``` 
`Vector3`のコンストラクタのオーバーロードにより、[`float`+`Vector2`]でも初期化出来る様になりました。

これで[`float`+`Vector2`]でも、手間なく初期化出来る様になりましたね。

皆さんこう思ったはずです。  
型が異なるが、すべて`float`型3つを受け取るコンストラクタなのに、
#### **オーバーロード**を行わない行けないのは非効率ではないのか？


## [Back](merit_1_4.md)　[Home](merit_0_0.md)　[Next](merit_1_6.md)　
