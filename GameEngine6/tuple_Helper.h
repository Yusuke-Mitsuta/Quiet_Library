#pragma once
#include<tuple>
#include<optional>
template<int _Index, class _Tuple, bool overflowFg = 
	(_Index >= std::tuple_size_v<_Tuple>) ||(_Index<0)>
struct tuple_element_overflow
{
	using type = std::tuple_element_t<_Index, _Tuple>;
};

template<int _Index, class _Tuple>
struct tuple_element_overflow<_Index, _Tuple, true>
{
	using type = std::nullopt_t;
};
template<int _Index, class _Tuple>
using tuple_element_t_overflow = tuple_element_overflow<_Index, _Tuple>::type;

template<class T_Tuple>
struct S_EnvelopOptional;

//仕様
//tuple内の型[...T_TupleInnerType]を[optional]でラッピングする
//
//template
//[optional]でラッピングするtuple
template<class ...T_TupleInnerType>
struct S_EnvelopOptional<std::tuple<T_TupleInnerType...>>
{
	using Type = std::tuple<std::optional<T_TupleInnerType>...>;
};
