### [README](../README.md)/[quiet](quiet.md)/operator 

``` C++
template<class T_Left, class T_Right>
	requires requires(const T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Sum(&l, &r)};
}
static constexpr auto operator+(const T_Left& l, const T_Right& r);

template<class T_Left, class T_Right>
	requires requires(const T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Difference(&l, &r)};
}
static constexpr auto operator-(const T_Left& l, const T_Right& r);

template<class T_Left, class T_Right>
	requires requires(const T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Product(&l, &r)};
}
static constexpr auto operator*(const T_Left& l, const T_Right& r);

template<class T_Left, class T_Right>
	requires requires(const T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Quotient(&l, &r)};
}
static constexpr auto operator/(const T_Left& l, const T_Right& r);



template<class T_Left, class T_Right>
	requires requires(T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Sum(&l, &r)};
}
static constexpr void operator+=(T_Left& l, const T_Right& r);

template<class T_Left, class T_Right>
	requires requires(T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Difference(&l, &r)};
}
static constexpr void operator-=(T_Left& l, const T_Right& r);

template<class T_Left, class T_Right>
	requires requires(T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Product(&l, &r)};
}
static constexpr void operator*=(T_Left& l, const T_Right& r);

template<class T_Left, class T_Right>
	requires requires(T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Quotient(&l, &r)};
}
static constexpr void operator/=(T_Left& l, const T_Right& r);
```

## 概要
[構造化束縛][構造化束縛]に対応している型に対して、要素同士の**operator**を提供する
***

## 仕様
1. 左辺値、右辺値のどちらもが、[構造化束縛][構造化束縛]に対応している場合、それぞれの要素に対して計算を行う。

1. 左辺値又は、右辺値のどちらかが、[構造化束縛][構造化束縛]に対応していない場合、その値と、もう一方の[構造化束縛][構造化束縛]に対応している値の要素全てと計算を行う。

## 制限
1. 左辺値又は、右辺値のどちらかが[構造化束縛][構造化束縛]に対応している。
2. 計算が行える事

## 備考
1. [構造化束縛][構造化束縛]に対応している値での計算時、どちらかの要素数が少ない場合、少ない要素数に合わせ、残りは代入される。

## 関連
[構造化束縛 (quiet)](Tuple/N_Tuple/構造化束縛.md)      
[構造化束縛][構造化束縛]       


[構造化束縛]:https://cpprefjp.github.io/lang/cpp17/structured_bindings.html