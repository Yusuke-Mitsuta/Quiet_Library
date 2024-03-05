# quiet

このライブラリは**C++** において**堅牢性**、**柔軟性**、**簡素性**の３つを高水準で実現した[Array][Array]、[Tuple][Tuple]、[Function][Function]を提供し、型が**複数の要素から構成**されてると捉えれる様になります。

[ライブラリ詳細へ][quiet]
***
## quietを利用するメリット
`クラス`、`関数`の引数が、構成される要素と互換性がある値を、受け取れる様になり、オーバーロード、キャストの手間を削減出来ます。

[詳しい解説へ](Reference/Explanation/merit_0_0.md)    

### quietの実用例
<details>
    <summary style="display: flex; align-items: center; cursor: pointer;">
        <span id="triangle-icon" style="margin-right: 10px;"></span>
        <h4>関数の引数に互換性を持たせる場合</h4>
    </summary>

``` C++
#include"Array.h"
#include"Function.h"
using namespace quiet;

void Args_Vector3(Array<int,3> vec3)
{
    std::cout << "x : " << vec3[0] << " ,"
        << "y : " << vec3[1] << " ,"
        << "z : " << vec3[2] << std::endl;
}

int main()
{
    //[int]型の要素を2つ持つ型
    Array vec2(1, 2);

    //引数に[Array<int,3>] ([int]型の要素を3つ持つ型) を取る関数を
    //　[[int]型を合計3つ] 受け取れば関数を実行できる様にラッピングする。
    Function fn_Args_Vector3(&Args_Vector3);

    //[int]型の要素を合計で3つ受け取る
    // 
    //引数 1:[int]型の要素を2つ持つ型
    //引数 2:[int]型
    fn_Args_Vector3(vec2,0);

    //[int]型の要素を合計で3つ受け取る
    // 
    //引数 1:[int]型
    //引数 2:[int]型
    //引数 3:[int]型
    fn_Args_Vector3(4, 5, 6);

    return 0;
}
```
関数をオブジェクトとして、ラッピングする際は[Function][Function]、即時関数を呼び出す場合は[Apply][Apply]を使用すること
***

</details>


<details>
    <summary style="display: flex; align-items: center; cursor: pointer;">
        <span id="triangle-icon" style="margin-right: 10px;"></span>
        <h4>クラスの生成に互換性を持たせる場合</h4>
    </summary>

``` C++
#include"Array.h"
#include"Function.h"
using namespace quiet;

//対象のクラス
struct MyStruct
{
    //このクラスがコンストラクタで受け取る型、及び、
    //　構造化束縛された際に返す型を[tuple]で宣言する。
    using tuple = tuple_t<int,float,double>;

    int i;
    float f;
    double d;

    //[tuple]で宣言した型を受け取るコンストラクタ
    MyStruct(int set_i, float set_f, double set_d) :
    	i(set_i), f(set_f), d(set_d) {}

    //構造化束縛された際に返す関数
    //  メンバー関数に[::get]が定義されていれば、自動で[std::get]がオーバーロードされる
    template<size_t I>
    constexpr std::tuple_element_t<I, MyStruct>& get();
};

template<>
constexpr std::tuple_element_t<0, MyStruct>& MyStruct::get<0>() {return i;}

template<>
constexpr std::tuple_element_t<1, MyStruct>& MyStruct::get<1>() {return f;}

template<>
constexpr std::tuple_element_t<2, MyStruct>& MyStruct::get<2>() {return d;}

int main()
{
    //[int]型の要素を3つ持つ型
    Array ary(1, 2, 3);

    //MyStructに要求する要素[int,float,doudle]がaryの要素[int,int,int]と
    //　互換性がある為呼び出せる
    MyStruct create = N_Tuple::Apply<MyStruct>(ary);
    return 0;
}
```

</details>

***
### 環境
|項目|値|
|:-|:-|
ライブラリ種別|静的ライブラリ
バージョン|C++ 20
コンパイラ|MSVC 2022

&#13;&#10;
&#13;&#10;
ライブラリ、及びリファレンスは著作権法に基づき保護されています。    

(C) 2024 Mitsuta Yusuke

[quiet]:Reference/quiet.md
[Array]:Reference/Array/Array.md
[Tuple]:Reference/Tuple/Tuple.md
[Function]:Reference/Function/Function.md   
[Apply]:Reference/Tuple/N_Tuple/Apply.md

<style>
    details[open] summary #triangle-icon::before {
        content: "▼ ";
    }
    details summary #triangle-icon::before {
        content: "▶ ";
    }
</style>
