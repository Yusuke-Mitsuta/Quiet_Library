#pragma once
#include<tuple>
#include"Concept.h"

template<class _Flom, class _To>
struct S_tuple_convertible_to
{
	using Type = S_tuple_convertible_to;
	using All = std::false_type;
	using FlontPart = std::false_type;
};

template<class C_Flom_Flont, class ...C_Flom, class C_To_Flont, class ...C_To>
	requires (sizeof...(C_Flom) != 0) && (sizeof...(C_To) != 0) && convertible_to<C_Flom_Flont, C_To_Flont>
struct S_tuple_convertible_to<std::tuple<C_Flom_Flont, C_Flom...>, std::tuple<C_To_Flont, C_To...>>
{
	using Type = S_tuple_convertible_to<std::tuple<C_Flom...>, std::tuple<C_To...>>::Type;	
	using Type1 = S_tuple_convertible_to<std::tuple<C_Flom...>, std::tuple<C_To...>>;	
};

template<class C_Flom_Flont, class C_To_Flont>
	requires convertible_to<C_Flom_Flont, C_To_Flont>
struct S_tuple_convertible_to<std::tuple<C_Flom_Flont>, std::tuple<C_To_Flont>>
{
	using Type = S_tuple_convertible_to;
	using All = std::true_type;
	using FlontPart = std::true_type;
};

template<class C_Flom_Flont, class ...C_Flom, class C_To_Flont, class ...C_To>
	requires (sizeof...(C_Flom) == 0) && (sizeof...(C_To) != 0) && convertible_to<C_Flom_Flont, C_To_Flont>
struct S_tuple_convertible_to<std::tuple<C_Flom_Flont, C_Flom...>, std::tuple<C_To_Flont, C_To...>>
{
	using Type = S_tuple_convertible_to;
	using FlontPart = std::true_type;
};


template<class C_Flom_Flont, class C_To_Flont>
struct S_tuple_convertible_to_Access{};

template<class ...C_Flom, class ...C_To>
	requires (sizeof...(C_Flom) >= sizeof...(C_To))
struct S_tuple_convertible_to_Access<std::tuple<C_Flom...>, std::tuple<C_To...>>
{
	using Type = S_tuple_convertible_to<std::tuple<C_Flom...>, std::tuple< C_To...>>::Type;

	using All = Type::All;

	using FlontPart = Type::FlontPart;

	using BackPart = All;
};

template<class ...C_Flom, class C_To_Flont, class ...C_To>
	requires (sizeof...(C_Flom) < (sizeof...(C_To)+1))
struct S_tuple_convertible_to_Access<std::tuple<C_Flom...>, std::tuple<C_To_Flont, C_To...>>
{
	using Type = S_tuple_convertible_to_Access<std::tuple<C_Flom...>, std::tuple<C_To...>>::Type;

	using BackPart = Type::All;
};

template<class _Flom, class _To>
concept tuple_convertible_to = std::same_as<std::true_type,typename S_tuple_convertible_to_Access<_Flom, _To>::All>;

template<class _Flom, class _To>
concept tuple_flont_part_convertible_to = std::same_as<std::true_type,typename S_tuple_convertible_to_Access<_Flom, _To>::FlontPart>;

template<class _Flom, class _To>
concept tuple_back_part_convertible_to = std::same_as<std::true_type,typename S_tuple_convertible_to_Access<_Flom, _To>::BackPart>;
