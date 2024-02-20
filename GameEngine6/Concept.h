#pragma once

#include<concepts>
#include"Invalid.h"
#include<tuple>

#define CONCEPT_1(name,type_1,type_name_1) \
template <type_1 type_name_1> \
concept name = name##_C<type_name_1>::value; \
template <type_1 ...type_name_1> \
concept name##_or = (... || name##_C<type_name_1>::value); \
template <type_1 ...type_name_1> \
concept name##_and = (... && name##_C<type_name_1>::value); \
template <type_1 type_name_1> \
concept name##_not = !name<type_name_1>; \
template <type_1 ...type_name_1> \
concept name##_nor = !name##_or<type_name_1...>;\
template <type_1 ...type_name_1> \
concept name##_nand = !name##_and<type_name_1...>; \

#define CONCEPT_TYPE_1(name,type_name_1) CONCEPT_1(name,class,type_name_1) \

#define CONCEPT_TYPE_1_DEFAULT(name) CONCEPT_TYPE_1(name,_Ty) \


#define CONCEPT_2(name,type_1,type_name_1,type_2,type_name_2) \
template <type_1 type_name_1,type_2 type_name_2> \
concept name = name##_C<type_name_1,type_name_2>::value; \
template <type_1 type_name_1,type_2 ...type_name_2> \
concept name##_or = (... || name##_C<type_name_1,type_name_2>::value); \
template <type_1 type_name_1,type_2 ...type_name_2> \
concept name##_and = (... && name##_C<type_name_1,type_name_2>::value); \
template <type_1 type_name_1,type_2 type_name_2> \
concept name##_not = !name<type_name_1,type_name_2>; \
template <type_1 type_name_1,type_2 ...type_name_2> \
concept name##_nor = !name##_or<type_name_1,type_name_2...>;\
template <type_1 type_name_1,type_2 ...type_name_2> \
concept name##_nand = !name##_and<type_name_1,type_name_2...>;\

#define CONCEPT_TYPE_2(name,type_name_1,type_name_2) CONCEPT_2(name,class,type_name_1,class,type_name_2) \

#define CONCEPT_TYPE_2_DEFAULT(name) CONCEPT_TYPE_2(name,_Ty1,_Ty2) \







template <bool t_Fg>
concept Fg = t_Fg;

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


template <class _Ty1, class _Ty2>
struct same_as_C :
	std::bool_constant<std::same_as<_Ty1,_Ty2>>{};

CONCEPT_TYPE_2_DEFAULT(same_as)

template<class _Ty1>
struct is_invalid_C :
	std::bool_constant<same_as<_Ty1,invalid_t>>{};

template<class _Ty1>
struct is_invalid_C<const _Ty1> :
	is_invalid_C<_Ty1> {};

CONCEPT_TYPE_1_DEFAULT(is_invalid)




template<class _Ty1,template<class...>class _Ty2>
struct same_as_template_type_C :
	std::false_type {};

template<template<class...>class _Ty1, class ..._Ty1_Types, template<class...>class _Ty2>
	requires (std::is_class_v<_Ty1<_Ty1_Types...>>)
struct same_as_template_type_C<_Ty1<_Ty1_Types...>, _Ty2> :
	std::bool_constant<std::same_as< _Ty1<_Ty1_Types...>, _Ty2<_Ty1_Types...>>>{};

CONCEPT_2(same_as_template_type, class, _Ty1, template<class...>class, _Ty2)


template<class _Ty1, template<auto...>class _Ty2>
struct same_as_template_value_C :
	std::bool_constant<false>{};

template<template<auto...>class _Ty1,auto ..._Ty1_value, template<auto...>class _Ty2>
struct same_as_template_value_C<_Ty1<_Ty1_value...>, _Ty2> :
	std::bool_constant<std::same_as<_Ty1<_Ty1_value...>, _Ty2<_Ty1_value...>>>{};

CONCEPT_2(same_as_template_value, class, _Ty1, template<auto...>class, _Ty2)


template <class _From, class _To>
struct convertible_to_C :
std::bool_constant<std::convertible_to<_From,_To>>{};

CONCEPT_TYPE_2(convertible_to, _From, _To)

template <class _Ty1, class _Ty2>
struct convertible_mutual_C :
	std::bool_constant<
	std::convertible_to<_Ty1, _Ty2> &&
	std::convertible_to<_Ty2, _Ty1> > {};

CONCEPT_TYPE_2(convertible_mutual, _Ty1, _Ty2)

template <class _To, class _From>
struct convertible_from_C :
	std::bool_constant<convertible_to<_From, _To>> {};

CONCEPT_TYPE_2(convertible_from,_To,_From)

template <class _Derived, class _Base>
struct derived_from_C :
	std::bool_constant<std::derived_from<_Derived, _Base>> {};

CONCEPT_TYPE_2(derived_from, _Derived, _Base)


using std::constructible_from;

template<class _Ty1>
struct is_pointer_C :
	std::is_pointer<_Ty1>{};

CONCEPT_TYPE_1_DEFAULT(is_pointer)

template<class _Ty1>
struct is_reference_C :
	std::is_reference<_Ty1> {};

CONCEPT_TYPE_1_DEFAULT(is_reference)

template<class _Ty1>
struct is_class_C :
	std::is_class<_Ty1> {};

CONCEPT_TYPE_1_DEFAULT(is_class)

template<class T>
struct is_static_function_pointer_C :
	std::false_type
{};

template<class T>
struct is_static_function_pointer_C<T*> :
	std::is_function<T>
{};

template<class T>
concept is_static_function_pointer = is_static_function_pointer_C<T>::value;

template<class T>
concept is_member_function_pointer = std::is_member_function_pointer_v<T>;

template<class T>
concept is_function_pointer = is_static_function_pointer<T> || is_member_function_pointer<T>;

using std::integral;
