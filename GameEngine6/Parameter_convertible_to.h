#pragma once


#pragma once
#include"Concept.h"
#include"Parameter_Element.h"

template<class ...T_Parameters>
struct S_Parameter;

//仕様
//[S_Parameter]の要素のが変換可能か、全体、前方、後方の三種類で判定する
//
//template
//T_Flom::判定する型
//T_To::ベースの型
template<class T_Flom, class T_To, int t_Mode = 0>
struct IS_Parameter_convertible_to
{
private:

public:

	//仕様
	//型の判定の結果
	template<int t_FinishNumber, int t_Flom_Number = 0, int t_To_Number = 0,
		bool t_LoopFg = (t_FinishNumber > t_To_Number) && (0 <= t_To_Number)>
	struct S_Parameter_convertible_to
	{
		using Type = std::bool_constant<(t_FinishNumber == t_To_Number)>;
	};

	//仕様
	//型がFlomからToに変更可能か判定し、可能なら次の型の判定に移る
	template<int t_FinishNumber, int t_Flom_Number, int t_To_Number>
		requires convertible_to<U_Element_t<t_Flom_Number>,U_Element_t<t_To_Number>>
	struct S_Parameter_convertible_to<t_FinishNumber, t_Flom_Number, t_To_Number, true>
	{
		using Type = S_Parameter_convertible_to<t_FinishNumber, t_Flom_Number, t_To_Number>::Type;
	};
	
	//仕様
	//tuple型の要素の変換可能か判定する
	using All = S_Parameter_convertible_to<std::max(T_Flom::Size, T_To::Size)>::Type;

	//仕様
	//tuple型の要素の前方が変換可能か判定する
	using FlontPart = S_Parameter_convertible_to<T_Flom::Size>::Type;

	//仕様
	//tuple型の要素の後方が変換可能か判定する
	using BackPart = S_Parameter_convertible_to<T_To::Size, 0, static_cast<int>(T_To::Size - T_Flom::Size)>::Type;



	template<int t_Mode>
	struct S_Type
	{
		using Type = All;
	};

	template<>
	struct S_Type<1>
	{
		using Type = FlontPart;
	};
	template<>
	struct S_Type<2>
	{
		using Type = BackPart;
	};

	using Select = S_Type<t_Mode>::Type;
};

//仕様
//[S_Parameter]の要素の変換可能か判定する
//
//template
//T_Flom::判定する[S_Parameter]
//T_To::ベースの[S_Parameter]
template<class _Flom, class _To>
concept parameter_convertible_to = std::same_as<std::true_type, typename IS_Parameter_convertible_to<_Flom, _To>::All>;

//仕様
//[S_Parameter]の要素の前方部分が変換可能か判定する
//
//template
//T_Flom::判定する[S_Parameter]
//T_To::ベースの[S_Parameter]
template<class _Flom, class _To>
concept parameter_flont_part_convertible_to = std::same_as<std::true_type, typename IS_Parameter_convertible_to<_Flom, _To>::FlontPart>;

//仕様
//[S_Parameter]の要素の後方部分が変換可能か判定する
//
//template
//T_Flom::判定する[S_Parameter]
//T_To::ベースの[S_Parameter]
template<class _Flom, class _To>
concept parameter_back_part_convertible_to = std::same_as<std::true_type, typename IS_Parameter_convertible_to<_Flom, _To>::BackPart>;
