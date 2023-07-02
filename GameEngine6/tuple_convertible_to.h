#pragma once
#include<tuple>
#include"Concept.h"

template<class _Flom, class _To>
struct S_tuple_convertible_to
{
	using Type = std::false_type;
	using Type6 = std::false_type;
};

template<class C_Flom_Flont, class ...C_Flom, class C_To_Flont, class ...C_To>
	requires (sizeof...(C_Flom) != 0) && (sizeof...(C_To) != 0) && convertible_to<C_Flom_Flont, C_To_Flont>
struct S_tuple_convertible_to<std::tuple<C_Flom_Flont, C_Flom...>, std::tuple<C_To_Flont, C_To...>>
{
	using Type = S_tuple_convertible_to<std::tuple<C_Flom...>, std::tuple<C_To...>>::Type;	
	using Type1 = S_tuple_convertible_to<std::tuple<C_Flom...>, std::tuple<C_To...>>;	
};

template<class ...C_Flom_Flont_Tuple, class ...C_Flom, class ...C_To>
struct S_tuple_convertible_to<
	std::tuple<std::tuple<C_Flom_Flont_Tuple...>,C_Flom...>, 
	std::tuple< C_To...>>
{
	using Type = S_tuple_convertible_to<std::tuple<C_Flom_Flont_Tuple...,C_Flom...>, std::tuple<C_To...>>::Type;
	using Type2 = S_tuple_convertible_to<std::tuple<C_Flom_Flont_Tuple...,C_Flom...>, std::tuple<C_To...>>;
	
};

template<class ...C_Flom, class ...C_To_Flont_Tuple, class ...C_To>
struct S_tuple_convertible_to<
	std::tuple< C_Flom...>, 
	std::tuple<std::tuple<C_To_Flont_Tuple...>, C_To...>>
{
	using Type = S_tuple_convertible_to<std::tuple<C_Flom...>, std::tuple<C_To_Flont_Tuple...,C_To...>>::Type;
	using Type3 = S_tuple_convertible_to<std::tuple<C_Flom...>, std::tuple<C_To_Flont_Tuple...,C_To...>>;
};

template<class ...C_Flom_Flont_Tuple, class ...C_Flom, class ...C_To_Flont_Tuple, class ...C_To>
struct S_tuple_convertible_to<
	std::tuple<std::tuple<C_Flom_Flont_Tuple...>, C_Flom...>,
	std::tuple<std::tuple<C_To_Flont_Tuple...>, C_To...>>
{
	using Type = S_tuple_convertible_to<std::tuple<C_Flom_Flont_Tuple...,C_Flom...>, std::tuple<C_To_Flont_Tuple..., C_To...>>::Type;
	using Type4 = S_tuple_convertible_to<std::tuple<C_Flom_Flont_Tuple...,C_Flom...>, std::tuple<C_To_Flont_Tuple..., C_To...>>;
};


template<class C_Flom_Flont, class C_To_Flont>
	requires convertible_to<C_Flom_Flont, C_To_Flont>
struct S_tuple_convertible_to<std::tuple<C_Flom_Flont>, std::tuple<C_To_Flont>>
{
	using Type = std::true_type;
	using Type5 = std::true_type;
};

template<class C_Flom_Flont, class C_To_Flont>
struct S_tuple_convertible_to_Access{};

template<class ...C_Flom, class ...C_To>
struct S_tuple_convertible_to_Access<std::tuple<C_Flom...>, std::tuple<C_To...>>
{
	using Type = S_tuple_convertible_to<std::tuple<C_Flom..., void>, std::tuple< C_To..., void>>::Type;
	using Type0 = S_tuple_convertible_to<std::tuple<C_Flom..., void>, std::tuple< C_To..., void>>;
};

template<class _Flom, class _To>
concept tuple_convertible_to = std::same_as<std::true_type,typename S_tuple_convertible_to_Access<_Flom, _To>::Type>;
