#pragma once
#include<tuple>
#include"Concept.h"
#include"Using_Type.h"

//仕様
//tuple型の要素のが変換可能か、全体、前方、後方の三種類で判定する
//
//template
//T_Flom::判定する型
//T_To::ベースの型
template<class T_Flom, class T_To>
struct IS_tuple_convertible_to
{
private:
	template<size_t t_FlomNumber>
	using flom_tuple_element = std::tuple_element<t_FlomNumber% std::tuple_size<T_Flom>::value, T_Flom>::type;

	template<size_t t_ToNumber>
	using to_tuple_element = std::tuple_element<t_ToNumber%std::tuple_size<T_To>::value, T_To>::type;
public:

	//仕様
	//型の判定の結果
	template<int t_TupleFinishNumber, int t_TupleFlomNumber = 0, int t_TupleToNumber = 0,
		bool t_LoopFg = (t_TupleFinishNumber > t_TupleToNumber) && (0 <= t_TupleToNumber)>
	struct S_tuple_convertible_to
	{
		static constexpr int flom = t_TupleFlomNumber;
		static constexpr int to = t_TupleToNumber;
		using Type =std::bool_constant<(t_TupleFinishNumber == t_TupleToNumber)>;
	};
	//仕様
	//型がFlomからToに変更可能か判定し、可能なら次の型の判定に移る
	template<int t_TupleFinishNumber, int t_TupleFlomNumber, int t_TupleToNumber>
		requires convertible_to<flom_tuple_element<t_TupleFlomNumber>, to_tuple_element<t_TupleToNumber>>
	struct S_tuple_convertible_to<t_TupleFinishNumber,t_TupleFlomNumber,t_TupleToNumber,true>
	{
		static constexpr int flom = t_TupleFlomNumber;
		static constexpr int to = t_TupleToNumber;
		using Type = S_tuple_convertible_to<t_TupleFinishNumber,t_TupleFlomNumber+1, t_TupleToNumber+1>::Type;
	};

	//仕様
	//tuple型の要素の変換可能か判定する
	using All = S_tuple_convertible_to<std::tuple_size<T_To>::value>::Type;

	//仕様
	//tuple型の要素の前方が変換可能か判定する
	using FlontPart = S_tuple_convertible_to<std::tuple_size<T_Flom>::value>::Type;
	
	//仕様
	//tuple型の要素の後方が変換可能か判定する
	using BackPart = S_tuple_convertible_to<std::tuple_size<T_To>::value, 0,std::tuple_size<T_To>::value - std::tuple_size<T_Flom>::value>::Type;

};

//仕様
//tuple型の要素の変換可能か判定する
//
//template
//T_Flom::判定するtuple型
//T_To::ベースのtuple型
template<class _Flom, class _To>
concept tuple_convertible_to = std::same_as<std::true_type,typename IS_tuple_convertible_to<_Flom, _To>::All>;

//仕様
//tuple型の要素の前方部分が変換可能か判定する
//
//template
//T_Flom::判定するtuple型
//T_To::ベースのtuple型
template<class _Flom, class _To>
concept tuple_flont_part_convertible_to = std::same_as<std::true_type,typename IS_tuple_convertible_to<_Flom, _To>::FlontPart>;

//仕様
//tuple型の要素の後方部分が変換可能か判定する
//
//template
//T_Flom::判定するtuple型
//T_To::ベースのtuple型
template<class _Flom, class _To>
concept tuple_back_part_convertible_to = std::same_as<std::true_type,typename IS_tuple_convertible_to<_Flom, _To>::BackPart>;
