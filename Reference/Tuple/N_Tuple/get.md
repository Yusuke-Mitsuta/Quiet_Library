### [README](../../../README.md)/[quiet](../../quiet.md)/[N_Tuple](N_Tuple.md)/get

# std::get 

```　C++
namespace quiet::N_Tuple
{
    template<size_t I, class T>
    concept is_std_get_chack = requires(T t)
    {
        requires is_invalid_not<typename S_Parameter<T>::tuple>;
        requires !is_Tuple<T>;
        requires S_Parameter<T>::size >= I;
    };
}

template<size_t I, class T>
    requires requires(T&& t)
{
    requires quiet::N_Tuple::is_std_get_chack<I, T>;
    {t.get<I>()};
}
static constexpr auto& get(T&& t);

template<size_t I, class T>
    requires requires(const T& t)
{
    requires quiet::N_Tuple::is_std_get_chack<I,remove_const_t<T>>;
    {const_cast<T&>(t).get<I>()};
}
static constexpr const auto get(const T& t);

template<size_t I, class T>
    requires requires(T t)
{
    requires quiet::N_Tuple::is_std_get_chack<I,T>;
    {t.get<I>()};
}
static constexpr auto& get(T* t);

template<size_t I, class T>
    requires requires(const T* t)
{
    requires quiet::N_Tuple::is_std_get_chack<I,remove_const_t<T>>;
    {const_cast<T*>(t)->get<I>()};
}
static constexpr const auto& get(const T* t);
```
***
## 概要 

<a href=N_Tuple.md#tuple及び互換性について 
style="text-decoration:underline;" 
span title="tuple及び互換性について
    以下のいずれかを満たす事
1.[tuple_t,tuple_tp,tuple_v,tuple_vp]型である&#13;&#10;
2.メンバー型に[tuple]が宣言されている、
    かつその型が条件１を満たす&#13;&#10;
3.[N_Tuple::S_Parameter]にて特殊化されている、
    かつ[N_Tuple::S_Parameter::tuple]が条件１を満たす
">tuple及び、tupleと互換性がある</span></a>、かつメンバー関数に**参照を返す**`get<N>`が実装されている場合、[`std::get`]の呼び出しを可能にする
***
## 制限
#### 以下の全てを満たす事

1. <a href=N_Tuple.md#tuple及び互換性について 
style="text-decoration:underline;" 
span title="tuple及び互換性について
    以下のいずれかを満たす事
1.[tuple_t,tuple_tp,tuple_v,tuple_vp]型である&#13;&#10;
2.メンバー型に[tuple]が宣言されている、
    かつその型が条件１を満たす&#13;&#10;
3.[N_Tuple::S_Parameter]にて特殊化されている、
    かつ[N_Tuple::S_Parameter::tuple]が条件１を満たす
">tuple及び、tupleと互換性がある</span></a>
1. [`1.`]で返す[`tuple_t`]のsizeが、[`I`]より小さい事
***

## 関連  
[std::tuple_element (quiet)](tuple_element.md)  
[N_Tuple::構造化束縛](構造化束縛.md) 