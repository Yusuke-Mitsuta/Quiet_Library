#pragma once

#include<iostream>

#include"Tuple_Declare.h"
#include"Tuple_Get.h"
#include"SwapType.h"


#define TUPLE_CALCULATION(name,oper)\
template<class T_Left, class T_Right>\
	requires requires(const T_Left* l,const T_Right* r)\
{\
	requires N_Apply::I_Type_Chack<tuple_t<T_Left>,tuple_t<decltype(std::get<t_Calculation_Element_Number>(*l) oper std::get<t_Calculation_Element_Number>(*r))...>>::value==0;\
	requires std::tuple_size_v<T_Left> >= std::tuple_size_v<T_Right>;\
	requires sizeof...(t_Calculation_Element_Number)!=0;\
}\
static constexpr auto name(const T_Left* l,const T_Right* r)\
{\
	return T_Left{ (std::get<t_Calculation_Element_Number>(*l)) oper (std::get<t_Calculation_Element_Number>(*r))...,std::get<t_Copy_Element_Number>(*l)... };\
}\
\
template<class T_Left, class T_Right>\
	requires requires(const T_Left* l,const  T_Right* r)\
{\
	requires N_Apply::I_Type_Chack<tuple_t<T_Left>,tuple_t<decltype(std::get<t_Calculation_Element_Number>(*l) oper std::get<t_Calculation_Element_Number>(*r))...>>::value==0;\
	requires std::tuple_size_v<T_Left> < std::tuple_size_v<T_Right>;\
	requires sizeof...(t_Calculation_Element_Number)!=0;\
}\
static constexpr auto name(const T_Left* l,const T_Right* r)\
{\
	return T_Left{(std::get<t_Calculation_Element_Number>(*l)) oper( std::get<t_Calculation_Element_Number>(*r))...};\
}\
\
template<class T_Left, class T_Right>\
	requires requires(const T_Left* l, const T_Right* r)\
{\
	requires N_Apply::I_Type_Chack<tuple_t<T_Left>, tuple_t<decltype(std::get<t_Copy_Element_Number>(*l) oper *r)...>>::value == 0; \
	requires sizeof...(t_Calculation_Element_Number)==0;\
}\
static constexpr auto name(const T_Left* l,const T_Right* r)\
{\
	return T_Left{std::get<t_Copy_Element_Number>(*l) oper *r ...};\
}\
\
template<class T_Left, class T_Right>\
	requires requires(const T_Left* l,const T_Right* r)\
{\
	requires N_Apply::I_Type_Chack<tuple_t<T_Right>, tuple_t<decltype(*l oper std::get<t_Copy_Element_Number>(*r))...>>::value == 0; \
	requires sizeof...(t_Calculation_Element_Number)==0;\
}\
static constexpr auto name(const T_Left* l,const T_Right* r)\
{\
	return T_Right{( *l oper std::get<t_Copy_Element_Number>(*r))...};\
}\

#define TUPLE_CALCULATION_ASSIGNMENT(name,oper)\
template<class T_Left, class T_Right, size_t N = 0>\
	requires requires(T_Left* l,const T_Right* r)\
{\
	{std::get<N>(*l) oper std::get<N>(*r)};\
	requires sizeof...(t_Calculation_Element_Number) > N;\
}\
static constexpr void name(T_Left* l,const T_Right* r)\
{\
	std::get<N>(*l) oper std::get<N>(*r);\
	name< T_Left, T_Right, N + 1>(l, r);\
}\
\
template<class T_Left, class T_Right, size_t N = 0>\
	requires requires \
{\
	requires sizeof...(t_Copy_Element_Number) == N; \
	requires sizeof...(t_Calculation_Element_Number) == 0;\
} ||\
requires\
{\
	requires sizeof...(t_Calculation_Element_Number) == N;\
	requires sizeof...(t_Calculation_Element_Number) != 0; \
}\
static constexpr void name(T_Left* l,const T_Right* r)\
{}\
\
template<class T_Left, class T_Right, size_t N = 0>\
	requires requires(T_Left* l,const T_Right* r)\
{\
	{std::get<N>(l) oper *r};\
	requires sizeof...(t_Copy_Element_Number) > N;\
	requires sizeof...(t_Calculation_Element_Number) == 0; \
}\
static constexpr void name(T_Left* l,const T_Right* r)\
{\
	std::get<N>(*l) oper *r;\
	name< T_Left, T_Right, N + 1>(l, r);\
}\


namespace quiet::N_Tuple
{
	//仕様
	//構造化束縛に対応してる型同士の計算、
	//構造化束縛に対応してる型の要素全てと、単一の要素の計算
	// の為の補助クラス
	// 
	//戻り値
	// 左辺値の型で返される
	// ※左辺値が構造化束縛に対応していない場合は、右辺値の型で返される
	// 
	//補足
	// 左辺値のサイズの方が大きい場合、右辺値と計算されない値はそのままとなる
	// 右辺値のサイズの方が大きい場合は無視される
	template<class T_Left, class T_Right>
	struct I_Calculation
	{
	private:
		template<class T>
		struct S_Size_Chack
		{
			static constexpr size_t value = 0;
		};

		template<class T>
			requires requires
		{
			std::tuple_size<T>::value;
		}
		struct S_Size_Chack<T>
		{
			static constexpr size_t value = std::tuple_size<T>::value;
		};

		static constexpr size_t l_size = S_Size_Chack<T_Left>::value;

		static constexpr size_t r_size = S_Size_Chack<T_Right>::value;

		using return_type = U_if_t1<T_Left, T_Right, l_size>;

		static constexpr size_t min = std::min(l_size, r_size);
		static constexpr size_t max = std::max(l_size, r_size);

		template<class T_Calculation_Element_Number = U_index_sequence<min>,
			class T_Copy_Element_Number = U_Template_Calculate_plus<U_index_sequence<max - min>, min>>
			struct S_Calculation {};

		template<size_t... t_Calculation_Element_Number, size_t... t_Copy_Element_Number>
		struct S_Calculation<tuple_v<t_Calculation_Element_Number...>, tuple_v<t_Copy_Element_Number...>>
		{

			TUPLE_CALCULATION(Sum, +)
			TUPLE_CALCULATION(Difference, -)
			TUPLE_CALCULATION(Product, *)
			TUPLE_CALCULATION(Quotient, / )

			TUPLE_CALCULATION_ASSIGNMENT(Assignment_Sum, +=)
			TUPLE_CALCULATION_ASSIGNMENT(Assignment_Difference, -=)
			TUPLE_CALCULATION_ASSIGNMENT(Assignment_Product, *=)
			TUPLE_CALCULATION_ASSIGNMENT(Assignment_Quotient, /=)

		};
	public:
		using type = S_Calculation<>;

	};


}

template<class T_Left, class T_Right>
	requires requires(const T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Sum(&l, &r)};
}
static constexpr auto operator+(const T_Left& l, const T_Right& r)
{
	return quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Sum(&l, &r);
};

template<class T_Left, class T_Right>
	requires requires(const T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Difference(&l, &r)};
}
static constexpr auto operator-(const T_Left& l, const T_Right& r) {
	return quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Difference(&l, &r);
};

template<class T_Left, class T_Right>
	requires requires(const T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Product(&l, &r)};
}
static constexpr auto operator*(const T_Left& l, const T_Right& r)
{
	return quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Product(&l, &r);
}

template<class T_Left, class T_Right>
	requires requires(const T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Quotient(&l, &r)};
}
static constexpr auto operator/(const T_Left& l, const T_Right& r)
{
	return quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Quotient(&l, &r);
};



template<class T_Left, class T_Right>
	requires requires(T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Sum(&l, &r)};
}
static constexpr void operator+=(T_Left& l, const T_Right& r)
{
	quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Sum(&l, &r);
};

template<class T_Left, class T_Right>
	requires requires(T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Difference(&l, &r)};
}
static constexpr void operator-=(T_Left& l, const T_Right& r)
{
	quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Difference(&l, &r);
};

template<class T_Left, class T_Right>
	requires requires(T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Product(&l, &r)};
}
static constexpr void operator*=(T_Left& l, const T_Right& r)
{
	quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Product(&l, &r);
};

template<class T_Left, class T_Right>
	requires requires(T_Left& l, const T_Right& r)
{
	{quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Quotient(&l, &r)};
}
static constexpr void operator/=(T_Left& l, const T_Right& r)
{
	quiet::N_Tuple::I_Calculation<T_Left, T_Right>::type::Assignment_Quotient(&l, &r);
};
