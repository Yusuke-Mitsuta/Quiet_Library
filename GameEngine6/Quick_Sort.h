#pragma once

#include"SwapType.h"
#include"Parameter.h"
#include"Constexpr_Array.h"

template<template<class, class>class T_Judge, class TP>
struct IS_Quick_Sort
{



	struct S_Quick_Sort_Standard
	{
		using Element_0 = U_Element_t<0, TP>;
		using Element_1 = U_Element_t<1, TP>;
		using Element_2 = U_Element_t<2, TP>;

		static constexpr bool Judge_01 = T_Judge<Element_0, Element_1>::Judge;
		static constexpr bool Judge_12 = T_Judge<Element_1, Element_2>::Judge;
		static constexpr bool Judge_20 = T_Judge<Element_2, Element_0>::Judge;

		using Element_02 = U_Swap_t1<Element_0, Element_2, (Judge_12&& Judge_20)>;

		using Type = U_Swap_t1<Element_02, Element_1, (Judge_01&& Judge_12)>;

	};

	template<class TP_Numbers, int t_Limit_Min, int t_Center, int t_Limit_Max>
	struct IS_Next_Quick_Sort;

	template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max, int t_Flont=0, int t_Back=0, class T_Standard = int>
	struct S_Quick_Sort
	{
		template<size_t _Index>
		using Element = U_Element_t<U_Element_v<_Index, TP_Numbers>, TP>;

		static constexpr int Flont_Number = t_Limit_Min + t_Flont;
		static constexpr int Back_Number = t_Limit_Max - t_Back;



		template<int t_Flont, int t_Back = 0, bool t_Judge_Back = T_Judge<Element<Back_Number - t_Back>,T_Standard>::Judge, bool t_End_Fg = ((Flont_Number + t_Flont) >= Back_Number - t_Back)>
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
			using Type = S_Next_Quick_Sort<TP_Numbers, t_Limit_Min, Back_Number - t_Back, t_Limit_Max>::Type;
		};


		template<int t_Flont = 0, bool t_Judge_Flnot = (!T_Judge<Element<Flont_Number + t_Flont>, T_Standard>::Judge), bool t_End_Fg = ((Flont_Number + t_Flont) >= Back_Number)>
		struct S_Quick_Sort_Flont
		{
			using Type = S_Quick_Sort_Flont<t_Flont + 1>::Type;
		};

		template<int t_Flont>
		struct S_Quick_Sort_Flont<t_Flont, false, false>
		{
			using Type = S_Quick_Sort_Back<t_Flont>::Type;
		};

		template<int t_Flont, bool t_Judge_Flnot>
		struct S_Quick_Sort_Flont<t_Flont, t_Judge_Flnot, true>
		{
			using Type = S_Next_Quick_Sort<TP_Numbers, t_Limit_Min, Flont_Number + t_Flont, t_Limit_Max>::Type;

		};


		using Type = S_Quick_Sort_Flont<>::Type;

	};

	template<class TP_Numbers, int t_Limit_Min, int t_Center, int t_Limit_Max>
	struct IS_Next_Quick_Sort
	{

		template<size_t _Index>
		using Element = U_Element_t<U_Element_vp<_Index, TP_Numbers>, TP>;

		template<class TP_Numbers, int t_Range_Min, int t_Range_Max, int t_Range = t_Range_Max - t_Range_Min>
		struct S_Next_Quick_Sort
		{
			using Type= S_Quick_Sort<TP_Numbers, t_Range_Min, t_Range_Max>::Type;
		};

		template<class TP_Numbers, int t_Range_Min, int t_Range_Max>
		struct S_Next_Quick_Sort<TP_Numbers, t_Range_Min,t_Range_Max,3>
		{

		};

		template<class TP_Numbers, int t_Range_Min, int t_Range_Max>
		struct S_Next_Quick_Sort<TP_Numbers, t_Range_Min, t_Range_Max, 2>
		{

		};

		template<class TP_Numbers, int t_Range_Min, int t_Range_Max>
		struct S_Next_Quick_Sort<TP_Numbers, t_Range_Min, t_Range_Max, 1>
		{
			static constexpr bool Judge = T_Judge<Element<t_Range_Max>, Element<t_Range_Min>>::Judge;

			using Swap_1 = TP_Numbers;

			using Swap_2 = U_Change_Element_v<t_Range_Min, t_Range_Max, TP_Numbers>;

			using Type = U_Swap_t1<Swap_1, Swap_2, Judge>;

		};

		template<class TP_Numbers, int t_Range_Min, int t_Range_Max>
		struct S_Next_Quick_Sort<TP_Numbers, t_Range_Min, t_Range_Max, 0>
		{
			using Type = TP_Numbers;
		};

		template<bool t_Flont_End_Fg = ((t_Center - t_Limit_Min) <= 2),
			bool t_Back_End_Fg = ((t_Limit_Max - t_Center) <= 2)>
		struct S_Next_Quick_Sort
		{
			using FLont_Sort = S_Quick_Sort<TP_Numbers, t_Limit_Min, t_Center>::Type;
			using Back_Sort = S_Quick_Sort<FLont_Sort, t_Center, t_Limit_Max>::Type;
			using Type = Back_Sort;
		};

		template<>
		struct S_Next_Quick_Sort<false, true>
		{
			using FLont_Sort = S_Quick_Sort<TP_Numbers, t_Limit_Min, t_Center>::Type;

			using Type = FLont_Sort;
		};

		template<>
		struct S_Next_Quick_Sort<true, false>
		{
			using Back_Sort = S_Quick_Sort<TP_Numbers, t_Center, t_Limit_Max>::Type;

			using Type = Back_Sort;
		};

		template<>
		struct S_Next_Quick_Sort<true, true>
		{
			using Type = TP_Numbers;
		};

		using Type = S_Next_Quick_Sort<>::Type;

	};
	using Type = S_Quick_Sort<typename IS_Index_Sequence<TP::Size>::Type,0,TP::Size-1>::Type;

};

