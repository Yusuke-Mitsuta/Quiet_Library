#pragma once

#include<concepts>
#include"Invalid.h"
#include<tuple>

template <bool t_Fg>
concept Fg = t_Fg;

template <template<class...>class T_Concept>
concept is_Concept = requires
{
	T_Concept<int, int>::Concept;
};

template<template<class, class>class is_concept, class _Ty1,class ..._Ty>
struct is_or :
	std::false_type {};

template<template<class,class>class is_concept,class _Ty1, class _Ty2,class ..._Ty>
	requires (is_concept<_Ty1,_Ty2>::value)
struct is_or<is_concept,_Ty1,_Ty2,_Ty...>:
	std::true_type {};

template<template<class, class>class is_concept, class _Ty1, class _Ty2, class ..._Ty>
struct is_or<is_concept, _Ty1, _Ty2, _Ty...> :
	is_or<is_concept, _Ty1, _Ty...> {};


template<template<class, class>class is_concept, class _Ty1,class ..._Ty>
struct is_and :
	std::true_type {};

template<template<class, class>class is_concept, class _Ty1, class _Ty2, class ..._Ty>
	requires(!is_concept<_Ty1, _Ty2>::value)
struct is_and<is_concept, _Ty1, _Ty2, _Ty...> :
	std::false_type {};

template<template<class, class>class is_concept, class _Ty1, class _Ty2, class ..._Ty>
struct is_and<is_concept, _Ty1, _Ty2, _Ty...> :
	is_or<is_concept, _Ty1, _Ty...> {};

//仕様
//[T_Tuple]の要素に[t_Number]の要素が存在するか判定する
//
//テンプレート
//T_Tuple::要素を持つクラスで[std::tuple_size_v<T_Tuple>]で呼び出せる事
//t_Number::存在するか判定する要素の番号
template<class T_Size,int t_Number>
concept is_Element = (0<=t_Number && t_Number<std::tuple_size_v<T_Size>);

using std::same_as;

template <class _Ty1, class _Ty2>
struct not_is_same :
	std::bool_constant<!same_as<_Ty1, _Ty2>> {};


template <class _Ty1,class ..._Ty>
concept same_as_or = is_or<std::is_same, _Ty1, _Ty...>::value;

template <class _Ty1, class ..._Ty>
concept same_as_and = is_and<std::is_same, _Ty1, _Ty...>::value;

template <class _Ty1, class _Ty2>
concept not_same_as = not_is_same<_Ty1, _Ty2>::value;

template <class _Ty1, class ..._Ty>
concept not_same_as_or = is_or<not_is_same, _Ty1, _Ty...>::value;

template <class _Ty1, class ..._Ty>
concept not_same_as_and = is_and<not_is_same, _Ty1, _Ty...>::value;


template <class _Ty1, class _Ty2>
struct not_same_as_S
{
	static constexpr bool Concept = !same_as<_Ty1, _Ty2>;
};


template <class _Ty1>
concept is_invalid = same_as<_Ty1, invalid_t>;

template <class _Ty1>
concept not_is_invalid = !is_invalid<_Ty1>;

template<class T,bool t_Fg=1>
struct is_tuple_size_S :
	std::false_type {};

template<class T>
struct is_tuple_size_S<T,1> :
	std::true_type {};

template<class T>
concept is_tuple_size = is_tuple_size_S<T>::value;


template <class _Ty1, class _Ty2>
struct same_as_S
{
	static constexpr bool Concept = same_as<_Ty1, _Ty2>;
};

template<class _Ty1,template<class...>class _Ty2>
struct is_same_as_template_type :
	std::false_type {};

template<template<class...>class _Ty1, class ..._Ty1_Types, template<class...>class _Ty2>
	requires (std::is_class_v<_Ty1<_Ty1_Types...>>)
struct is_same_as_template_type<_Ty1<_Ty1_Types...>, _Ty2> :
	std::bool_constant<std::same_as< _Ty1<_Ty1_Types...>, _Ty2<_Ty1_Types...>>>{};


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





using std::convertible_to;

template <class _From, class _To>
struct not_is_convertible :
	std::bool_constant<!convertible_to<_From, _To>> {};

template <class _From, class ..._To>
concept convertible_to_or = is_or<std::is_convertible,_From, _To...>::value;

template <class _From, class ..._To>
concept convertible_to_and = is_and<std::is_convertible, _From, _To...>::value;

template <class _From, class _To>
concept not_convertible_to = not_is_convertible<_From, _To>::value;

template <class _From, class ..._To>
concept not_convertible_to_or = is_or<not_is_convertible, _From, _To...>::value;

template <class _From, class ..._To>
concept not_convertible_to_and = is_and<not_is_convertible, _From, _To...>::value;



template <class _To, class _From>
struct is_convertible_from :
	std::bool_constant<convertible_to<_From, _To>> {};

template <class _To, class _From>
struct not_is_convertible_from :
	std::bool_constant<!convertible_to<_From, _To>> {};

template <class _To,class _From>
concept convertible_from = is_convertible_from<_To, _From>::value;

template <class _To, class ..._From>
concept convertible_from_or = is_or<is_convertible_from, _To, _From...>::value;

template <class _To, class ..._From>
concept convertible_from_and = is_and<is_convertible_from, _To, _From...>::value;

template <class _To, class _From>
concept not_convertible_from = not_is_convertible_from<_To, _From>::value;

template <class _To, class ..._From>
concept not_convertible_from_or = is_or<not_is_convertible_from, _To, _From...>::value;

template <class _To, class ..._From>
concept not_convertible_from_and = is_and<not_is_convertible_from, _To, _From...>::value;






template <class _From, class _To>
struct convertible_to_S
{
	static constexpr bool Concept = convertible_to<_From, _To>;
};


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

