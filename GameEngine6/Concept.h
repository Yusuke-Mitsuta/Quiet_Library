#pragma once

#include<concepts>
#include<optional>
#include<tuple>

template <bool t_Fg>
concept Fg = t_Fg;

template <template<class...>class T_Concept>
concept is_Concept = requires
{
	T_Concept<int, int>::Concept;
};

//template<int N>
//struct S_Number
//{
//	static constexpr int Number = N;
//};
//
//template<class T>
//concept is_Exist_Number = requires
//{
//	typename T::Number;
//};
//
////仕様
////[T_Number::Number]の値が[t_Lower_Limit]以上、かつ [t_Upper_Limit]であることを判定する
////
////テンプレート
////T_Number::範囲内かを範囲するクラスでメンバーに[::Number]を持つ事
////t_Lower_Limit::下限値
////t_Upper_Limit::上限値
//template<class T_Number,int t_Lower_Limit,int t_Upper_Limit>
//concept C_Range = (is_Exist_Number<T_Number> && 
//	T_Number::Number >= t_Lower_Limit && T_Number::Number <= t_Upper_Limit);


//仕様
//[T_Tuple]の要素に[t_Number]の要素が存在するか判定する
//
//テンプレート
//T_Tuple::要素を持つクラスで[std::tuple_size_v<T_Tuple>]で呼び出せる事
//t_Number::存在するか判定する要素の番号
template<class T_Size,int t_Number>
concept is_Element = (0<=t_Number && t_Number<std::tuple_size_v<T_Size>);

using std::same_as;

template <class _Ty1>
concept is_nullopt = same_as<_Ty1, std::nullopt_t>;

template <class _Ty1>
concept not_is_nullopt = !is_nullopt<_Ty1>;

template <class _Ty1, class _Ty2>
struct same_as_S
{
	static constexpr bool Concept = same_as<_Ty1, _Ty2>;
};

template<class _Ty1,template<class...>class _Ty2>
struct is_same_as_template_type :
	std::bool_constant<false>{};

template<template<class...>class _Ty1, class ..._Ty1_Types, template<class...>class _Ty2>
struct is_same_as_template_type<_Ty1<_Ty1_Types...>, _Ty2> :
	std::bool_constant< std::same_as< _Ty1<_Ty1_Types...>, _Ty2<_Ty1_Types...>>>{};


template<class _Ty1, template<class...>class _Ty2>
concept same_as_template_type = is_same_as_template_type<_Ty1, _Ty2>::value;

template<class _Ty1, template<auto...>class _Ty2>
struct is_same_as_template_value :
	std::bool_constant<false>{};

template<template<auto...>class _Ty1,auto ..._Ty1_value, template<auto...>class _Ty2>
struct is_same_as_template_value<_Ty1<_Ty1_value...>, _Ty2> :
	std::bool_constant<std::same_as<_Ty1<_Ty1_value...>, _Ty2<_Ty1_value...>>>{};



template<class _Ty1, template<auto...>class _Ty2>
concept same_as_template_value = is_same_as_template_value<_Ty1, _Ty2>::value;


template <class _To,template<class...>class _From_Template>
struct is_copy_template_type :
	std::bool_constant<false> {};

template<class ...T_template_Types, template<class...>class _To_Template, template<class...>class _From_Template>
	requires (std::is_class_v<_From_Template<T_template_Types...>>)
struct is_copy_template_type<_To_Template<T_template_Types...>, _From_Template> :
	std::bool_constant<true> {};


template <class _To, template<auto...>class _From_Template>
struct is_copy_template_value :
	std::bool_constant<false> {};

template<auto ...T_template_Types, template<auto...>class _To_Template, template<auto...>class _From_Template>
	requires (std::is_class_v<_From_Template<T_template_Types...>>)
struct is_copy_template_value<_To_Template<T_template_Types...>, _From_Template> :
	std::bool_constant<true> {};




//
//template <class _Ty1, class _Ty2,class ..._Ty>
//struct same_as_or_S
//{
//	static constexpr bool Judge = same_as<_Ty1, _Ty2>;
//
//	using Swap_1 = same_as_or_S<_Ty1, _Ty...>;
//
//	struct Result
//	{
//		using Type = same_as_or_S;
//	};
//
//	using Swap_2 = Result;
//
//	using Type = U_Swap_t1<Swap_1, Swap_2, Judge>::Type;
//
//	static constexpr bool Concept = Type::Judge;
//
//};
//
//template <class _Ty1, class _Ty2>
//struct same_as_or_S<_Ty1,_Ty2>
//{
//	static constexpr bool Judge = same_as<_Ty1, _Ty2>;
//
//	using Type = same_as_S;
//
//	static constexpr bool Concept = Judge;
//
//};
//
//template <class _Ty1, class _Ty2, class ..._Ty>
//concept same_as_or = same_as_or_S<_Ty1, _Ty2, _Ty...>::Concept;


template <class _Ty1,class _Ty2>
concept not_same_as = !(same_as<_Ty1, _Ty2>);

template <class _Ty1, class _Ty2>
struct not_same_as_S
{
	static constexpr bool Concept = !same_as<_Ty1, _Ty2>;
};

using std::convertible_to;


template <class _To,class _From>
concept convertible_from = convertible_to<_From, _To>;

template <class _To,class _From>
concept not_convertible_from = !convertible_to<_From, _To>;

template <class _From, class _To>
struct convertible_to_S
{
	static constexpr bool Concept = convertible_to<_From, _To>;
};

template <class _From, class T_To>
concept not_convertible_to = !(convertible_to<_From,T_To>);

template <class _From, class _To>
struct not_convertible_to_S
{
	static constexpr bool Concept = !convertible_to<_From, _To>;
};

using std::derived_from;

template <class _Derived, class _Base>
concept not_derived_from = !(derived_from<_Derived, _Base>);

using std::constructible_from;

template <class T>
concept is_pointer = std::is_pointer_v<T>;

template <class T>
concept not_is_pointer = !std::is_pointer_v<T>;

template <class T>
concept is_reference = std::is_reference_v<T>;

template <class T>
concept not_is_reference = !std::is_reference_v<T>;

template <class T>
concept is_member_function_pointer = std::is_member_function_pointer_v<T>;

template <class _Ty1, template<class...>class _Ty2>
struct template_class_concept;

//仕様
//テンプレートを持つクラスのアウタークラスを比較する
template <template<class...>class _Ty1, class ..._Ty1_Inner, template<class...>class _Ty2>
struct template_class_concept<_Ty1<_Ty1_Inner...>,_Ty2>
{
	using T1 = _Ty1<_Ty1_Inner...>;
	using T2 = _Ty2<_Ty1_Inner...>;

	static constexpr bool same_as = same_as <T1, T2>;
	static constexpr bool convertible_to = convertible_to <T1, T2>;
	static constexpr bool convertible_from = convertible_from <T1, T2>;

};

//仕様
//テンプレートを持つクラスのアウタークラスを[same_as]で判定する
template <class _Ty1,template<class...> class _Ty2>
concept same_as_template_class = (template_class_concept<_Ty1, _Ty2>::same_as);

//仕様
//テンプレートを持つクラスのアウタークラスを[convertible_to]で判定する
template <class _Ty1, template<class...> class _Ty2>
concept convertible_to_template_class = (template_class_concept<_Ty1, _Ty2>::convertible_to);

template <class _Ty1, template<class...> class _Ty2>
concept not_convertible_to_template_class = !(template_class_concept<_Ty1, _Ty2>::convertible_to);

template <class _Ty1, template<class...> class _Ty2>
concept convertible_from_template_class = template_class_concept<_Ty1, _Ty2>::convertible_from;

template <class _Ty1, template<class...> class _Ty2>
concept not_convertible_from_template_class = !(template_class_concept<_Ty1, _Ty2>::convertible_from);


template <class _Ty1, template<auto...>class _Ty2>
struct template_value_concept;

//仕様
//非系テンプレートを持つクラスのアウタークラスを比較する
template <template<auto...>class _Ty1, auto ..._ty1_Inner, template<auto...>class _Ty2>
struct template_value_concept<_Ty1<_ty1_Inner...>, _Ty2>
{
	using T1 = _Ty1<_ty1_Inner...>;
	using T2 = _Ty2<_ty1_Inner...>;

	static constexpr bool same_as = std::same_as <T1, T2>;
	static constexpr bool convertible_to = std::convertible_to <T1, T2>;

};

//仕様
//非系テンプレートを持つクラスのアウタークラスを[same_as]で判定する
//template <class _Ty1, template<auto...> class _Ty2>
//concept same_as_template_value = (template_value_concept<_Ty1, _Ty2>::same_as);

//仕様
//非系テンプレートを持つクラスのアウタークラスを[convertible_to]で判定する
template <class _Ty1, template<auto...> class _Ty2>
concept convertible_to_template_value = (template_value_concept<_Ty1, _Ty2>::convertible_to);

template <class _Ty1, template<auto...> class _Ty2>
concept not_convertible_to_template_value = !(template_value_concept<_Ty1, _Ty2>::convertible_to);