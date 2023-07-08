#pragma once
#include<tuple>
#include"Concept.h"


template<class C_Flom, class C_To>
struct IS_tuple_convertible_to
{
private:
	template<size_t t_FlomNumber>
	using flom_tuple_element = std::tuple_element<t_FlomNumber, C_Flom>::type;

	template<size_t t_ToNumber>
	using to_tuple_element = std::tuple_element<t_ToNumber,C_To>::type;
public:

	template<Size_Type t_TupleFinishNumber, Size_Type t_TupleFlomNumber = 0, Size_Type t_TupleToNumber = 0,
		bool t_LoopFg=(t_TupleFinishNumber>t_TupleToNumber)>
	struct S_tuple_convertible_to
	{
		using Type =std::bool_constant<(t_TupleFinishNumber == t_TupleToNumber)>;
	};

	template<Size_Type t_TupleFinishNumber, Size_Type t_TupleFlomNumber, Size_Type t_TupleToNumber>
		requires convertible_to<flom_tuple_element<t_TupleFlomNumber>, to_tuple_element<t_TupleToNumber>>
	struct S_tuple_convertible_to<t_TupleFinishNumber,t_TupleFlomNumber,t_TupleToNumber,true>
	{
		using Type = S_tuple_convertible_to<t_TupleFinishNumber,t_TupleFlomNumber+1, t_TupleToNumber+1>::Type;
	};

	using All = S_tuple_convertible_to<std::tuple_size<C_To>::value>::Type;

	using FlontPart = S_tuple_convertible_to<std::tuple_size<C_Flom>::value>::Type;
	
	using BackPart = S_tuple_convertible_to<std::tuple_size<C_To>::value, 0, std::tuple_size<C_To>::value - std::tuple_size<C_Flom>::value>::Type;

};


template<class _Flom, class _To>
concept tuple_convertible_to = std::same_as<std::true_type,typename IS_tuple_convertible_to<_Flom, _To>::All>;

template<class _Flom, class _To>
concept tuple_flont_part_convertible_to = std::same_as<std::true_type,typename IS_tuple_convertible_to<_Flom, _To>::FlontPart>;

template<class _Flom, class _To>
concept tuple_back_part_convertible_to = std::same_as<std::true_type,typename IS_tuple_convertible_to<_Flom, _To>::BackPart>;
