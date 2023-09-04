#pragma once

#include"SwapType.h"
#include"Parameter.h"
#include"Constexpr_Array.h"

template<template<class, class>class T_Judge, class TP>
struct IS_Quick_Sort
{
	template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max>
	struct IS_Part_Sort
	{
		template<size_t _Index>
		using Element = U_Element_t<U_Element_vp<_Index, TP_Numbers>, TP>;

		template<class TP_Numbers=TP_Numbers, int t_Limit_Min = t_Limit_Min, int t_Limit_Max=t_Limit_Max, int t_Range = (t_Limit_Max - t_Limit_Min)>
		struct S_Part_Sort
		{
			using Type = TP_Numbers;
		};

		template<same_as_template_value<S_Parameter_Value> TP_Numbers, int t_Limit_Min, int t_Limit_Max>
		struct S_Part_Sort<TP_Numbers,t_Limit_Min,t_Limit_Max,1>
		{
			static constexpr bool Judge = T_Judge<Element<t_Limit_Max>, Element<t_Limit_Min>>::Judge;

			using Swap_1 = TP_Numbers;

			using Swap_2 = U_Change_Element_v<t_Limit_Min, t_Limit_Max, TP_Numbers>;

			using Type = S_Part_Sort;
			using Type_7 = U_Swap_t1<Swap_1, Swap_2, Judge>;

		};

		template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max>
		struct S_Part_Sort<TP_Numbers, t_Limit_Min, t_Limit_Max, 2>
		{
			using Part_Sort_Flont =typename S_Part_Sort<TP_Numbers, t_Limit_Min, t_Limit_Min + 1>::Type;

			using Part_Sort_Back = typename S_Part_Sort<Part_Sort_Flont,t_Limit_Max-1, t_Limit_Max>::Type;

			using Type = Part_Sort_Back;
		};

		using Type = S_Part_Sort<>::Type;

		using Type_6 = S_Part_Sort<>;

	};

	template<class TP_Numbers, int t_Limit_Min,int t_Limit_Max>
	struct IS_Quick_Sort_Standard
	{
		static constexpr int Range = t_Limit_Max - t_Limit_Min;
		static constexpr int Range_Half = static_cast<int>(Range * 0.5f);
		static constexpr int Range_Quarter = static_cast<int>(Range_Half * 0.5f);

		//using TP_Standard_Search_Number = S_Parameter_Value<U_Element_vp<t_Limit_Min+Range_Quarter, TP_Numbers>, U_Element_vp<t_Limit_Min+Range_Half, TP_Numbers>, U_Element_vp<t_Limit_Max- Range_Quarter, TP_Numbers>>;

		using TP_Standard_Search_Number = S_Parameter_Value<U_Element_vp<t_Limit_Min, TP_Numbers>, U_Element_vp<t_Limit_Min + 1, TP_Numbers>, U_Element_vp<t_Limit_Max, TP_Numbers>>;

		using Standard_Search = IS_Part_Sort<TP_Standard_Search_Number, 0, 2>::Type;
		using T = Standard_Search;
		using Type = U_Element_t<U_Element_vp<t_Limit_Min+1,Standard_Search>,TP>;

	};

	template<class TP_Numbers, int t_Limit_Min, int t_Center, int t_Limit_Max>
	struct IS_Next_Quick_Sort;

	template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max, int t_Flont = 0, int t_Back = 0,
		class T_Standard = typename IS_Quick_Sort_Standard<TP_Numbers,t_Limit_Min,t_Limit_Max>::Type>
	struct S_Quick_Sort
	{
		template<size_t _Index>
		using Element = U_Element_t<U_Element_vp<_Index, TP_Numbers>, TP>;

		static constexpr int Flont_Number = t_Limit_Min + t_Flont;
		static constexpr int Back_Number = t_Limit_Max - t_Back;

		template<int t_Flont, int t_Back = 0, bool t_Judge_Back = T_Judge<Element<Back_Number - t_Back>, T_Standard>::Judge, bool t_End_Fg = ((Flont_Number + t_Flont) >= Back_Number - t_Back)>
		struct S_Quick_Sort_Back
		{
			using Type = S_Quick_Sort_Back<t_Flont, t_Back + 1>::Type;
		};

		template<int t_Flont, int t_Back, bool t_End_Fg>
		struct S_Quick_Sort_Back<t_Flont, t_Back, true, t_End_Fg>
		{
			using Change_TP_Number = U_Change_Element_v<Flont_Number + t_Flont, Back_Number - t_Back, TP_Numbers>;

			using Type = S_Quick_Sort<Change_TP_Number, t_Limit_Min, t_Limit_Max, t_Flont, t_Back, T_Standard>::Type;
		};

		template<int t_Flont, int t_Back>
		struct S_Quick_Sort_Back<t_Flont, t_Back, false, true>
		{
			using Type = IS_Next_Quick_Sort<TP_Numbers, t_Limit_Min, Back_Number - t_Back, t_Limit_Max>::Type;
		};

		template<int t_Flont = 0, bool t_Judge_Flnot = (T_Judge<Element<Flont_Number + t_Flont>, T_Standard>::Judge), bool t_End_Fg = ((Flont_Number + t_Flont) >= Back_Number)>
		struct S_Quick_Sort_Flont
		{
			using Type_3 = S_Quick_Sort_Flont<t_Flont + 1>;
			static constexpr int n = Flont_Number + t_Flont;
			static constexpr int b = Back_Number;
			static constexpr bool End_Fg = ((Flont_Number + t_Flont) >= Back_Number);
			using Type = S_Quick_Sort_Flont<t_Flont + 1>::Type;
		};

		template<int t_Flont>
		struct S_Quick_Sort_Flont<t_Flont, false, false>
		{
			using Type_4 = S_Quick_Sort_Back<t_Flont>;
			using Type = S_Quick_Sort_Back<t_Flont>::Type;
		};

		template<int t_Flont, bool t_Judge_Flnot>
		struct S_Quick_Sort_Flont<t_Flont, t_Judge_Flnot, true>
		{
			using Type_5 = IS_Next_Quick_Sort<TP_Numbers, t_Limit_Min, Flont_Number + t_Flont, t_Limit_Max>;
			using Type = IS_Next_Quick_Sort<TP_Numbers, t_Limit_Min, Flont_Number + t_Flont, t_Limit_Max>::Type;

		};

		using ST = T_Standard;

		using Type_2 = S_Quick_Sort_Flont<>;
		using Type_21 = TP_Numbers;
		using Type = S_Quick_Sort_Flont<>::Type;

	};

	template<class TP_Numbers, int t_Limit_Min, int t_Center, int t_Limit_Max>
	struct IS_Next_Quick_Sort
	{
		static constexpr int t_Flont_Sort_Select = ((t_Center - t_Limit_Min) <= 2);

		static constexpr int t_Back_Sort_Select = ((t_Limit_Max - t_Center) <= 2);

		template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max, bool t_Quick_Sort_Fg = ((t_Limit_Max - t_Limit_Min) > 2)>
		struct S_Next_Sort 
		{
			using Type = S_Quick_Sort<TP_Numbers, t_Limit_Min, t_Limit_Max>::Type;
		};

		template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max>
		struct S_Next_Sort<TP_Numbers,t_Limit_Min,t_Limit_Max,false>
		{
			using Type = IS_Part_Sort<TP_Numbers, t_Limit_Min, t_Limit_Max>::Type;
		};

		using Flont_Sort = S_Next_Sort<TP_Numbers, t_Limit_Min, t_Center>::Type;
		using Back_Sort = S_Next_Sort<Flont_Sort, t_Limit_Min, t_Center>::Type;

		using Type = Back_Sort;

	};

	using Type_1 = S_Quick_Sort<typename IS_Index_Sequence<TP::Size>::Type, 0, TP::Size - 1>;
	using Type = S_Quick_Sort<typename IS_Index_Sequence<TP::Size>::Type, 0, TP::Size - 1>::Type;

};

