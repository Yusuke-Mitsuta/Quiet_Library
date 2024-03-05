### [README](../../../README.md)/[quiet](../../quiet.md)/[N_Tuple](N_Tuple.md)/Apply

# quiet::N_Tuple::Apply


<details>
    <summary style="display: flex; align-items: center; cursor: pointer;">
        <span id="triangle-icon" style="margin-right: 10px;"></span>
        <h3>関数オブジェクトを実行する</h3>
    </summary>

``` C++
template<class T_Fn, class ...T_Args>
    requires requires
{
    requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>;
    requires N_Apply::Chack<T_Fn, T_Args...>();
}
static constexpr auto Apply(T_Fn&& fn, T_Args&&... args);

template<class T_Fn, class ...T_Args>
    requires requires
{
    requires N_Apply::is_apply_type<T_Fn, N_Apply::E_Type::FN>;
    requires N_Apply::Chack<T_Fn, T_Args...>();
}
static constexpr auto Apply(T_Fn&& fn, auto* p, T_Args&&... args);
```
</details>


<details>
    <summary style="display: flex; align-items: center; cursor: pointer;">
        <span id="triangle-icon" style="margin-right: 10px;"></span>
        <h3>クラスを生成する</h3>
    </summary>

``` C++
template<class T, class ...T_Args>
    requires requires
{
    requires N_Apply::is_apply_type<Ta,N_Apply::E_Type::CLASS>;
    requires N_Apply::Chack<T, T_Args...>();
}
static constexpr auto Apply(T_Args&&... args);

template<class T, class ...T_Args>
    requires requires
{
    requires N_Apply::is_apply_type<T, N_Apply::E_Type::CLASS_NEW>;
    requires N_Apply::Chack<T, T_Args...>();
}
static constexpr auto Apply(T_Args&&... args);
```

</details>

<details>
    <summary style="display: flex; align-items: center; cursor: pointer;">
        <span id="triangle-icon" style="margin-right: 10px;"></span>
        <h3>配列に値を格納する</h3>
    </summary>

``` C++
template<size_t set_Num, class T_Array, class ...T_Args>
    requires requires
{
    requires N_Apply::is_apply_type<T_Array[set_Num], N_Apply::E_Type::ARRAY>;
    requires N_Apply::Chack<T_Array[set_Num], T_Args...>();
}
static constexpr void Apply(T_Array* array_p, T_Args&&... args);
```
***
</details>


## 概要
`Apply`に渡されたテンプレート、引数によって、要求されている型を認識し、引数を要求されている型にそって変形し、`関数オブジェクトの実行`,`クラスの生成`,`配列への追加`を行う。

要求されている型に変形不可の場合は**静的なエラー**となる。
***
## 動作
`Apply`は以下の条件にて動作を行う
1. Apply(`静的関数`,`供給する引数...`)の場合は、静的な関数を実行する。
2. Apply(`クラスのメンバー関数`,`メンバー関数にアクセスするクラスポインター`,`供給する引数...`)の場合は、メンバー関数を実行する。
3. Apply<`T`>(`供給する引数...`)の場合は、`T`を生成する
4. Apply<`T*`>(`供給する引数...`)の場合は、`T`をnewする
5. Apply<`N`>(`配列のポインター`,`供給する引数...`)の場合は、配列のポインターに、`N`個の要素を追加する。
***
## 制限
####`Apply`は以下の条件を全てを満たす事
`供給する引数...`を構成する要素が、[`関数オブジェクトの実行`,`クラスの生成`,`配列への追加`]が要求する引数と、[構成される要素](Apply.md#構成される要素とは)の並びに互換性がある事
***
## 備考
Applyに渡す関数オブジェクトが複数の関数オブジェクトを複合する[Function](../../Function/Function.md)の場合、(`引数...`)で呼び出せる中で、先頭の関数オブジェクトを呼び出す

* #### 「構成される要素」とは
  `std::array<int, 3>`の場合、**要素**としては、[`int`,`int`,`int`] となり**要素**は **int 型が 3つ**から構成されています。
少し複雑な型として`quiet::Array< quiet::Array<int, 3> , 3>`の場合は、**int 型 3つ × 3つ** と考え、**int 型が9つ**から構成されています。

* #### 「型の変換について」
  型の構成される要素に互換性がある型は、全て変換出来る様になります。
`quiet::Array<int, 3>`の場合、**int 型が3つ**から構成されている為、「**int 型**と互換性がある型が**3つ**」で構成される型である。
***
## 関連    
[N_Tuple](N_Tuple.md)    
[tuple_t](../tuple_t.md)    
[Function](../../Function/Function.md)   
[Tuple](../../Tuple/Tuple.md)   
[N_Tuple::構造化束縛](構造化束縛.md)    

<style>
    details[open] summary #triangle-icon::before {
        content: "▼ ";
    }
    details summary #triangle-icon::before {
        content: "▶ ";
    }
</style>
