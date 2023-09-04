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

			using Type = U_Swap_t1<Swap_1, Swap_2, Judge>;

		};

		template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max>
		struct S_Part_Sort<TP_Numbers, t_Limit_Min, t_Limit_Max, 2>
		{
			
			template<int Index_1,int Index_2>
			static constexpr bool Judge = T_Judge<Element<t_Limit_Min+Index_1>, Element<t_Limit_Min+Index_2>>::Judge;

			template<int t_Center_Number,
				int t_Side_Number_1,
				int t_Side_Number_2>
			struct S_Judge_Side
			{
				using Side_Number = U_Swap_v<t_Side_Number_1, t_Side_Number_2,
					Judge<t_Side_Number_1, t_Side_Number_2>>;
				using T = S_Judge_Side;
				using T1 = S_Parameter_Value< Side_Number::_1, Side_Number::_2>;
				using Type = S_Parameter_Value<Side_Number::_2, t_Center_Number, Side_Number::_1>;
			};
			//main.cpp : 153 << struct S_Parameter_Value<2,3,1,0>
			template<	
				bool t_Center_0 = !(Judge<0, 1>^ Judge<2, 0>),
				bool t_Center_1 = !(Judge<0, 1> ^ Judge<1, 2>),
				bool t_Center_2 = !(Judge<1, 2> ^ Judge<2, 0>)>
			struct S_Judge_Center
			{
				using Type = S_Parameter_Value<0, 1, 2>;
			};

			template<>
			struct S_Judge_Center<true,false,false>
			{
				using Type = S_Judge_Side<0, 1, 2>::Type;
			};

			template<>
			struct S_Judge_Center< false, true, false>
			{
				using Type = S_Judge_Side<1, 2, 0>::Type;
			};

			template<>
			struct S_Judge_Center<false, false, true>
			{
				using Type = S_Judge_Side<2, 0, 1>::Type;
			};


			using Part_Sort = S_Judge_Center<>::Type;

			using Remove = U_Remove_Element_v<TP_Numbers, t_Limit_Min ,t_Limit_Min + 1, t_Limit_Min + 2>;

			using TPN = TP_Numbers;
			using Insert = U_Insert_Element_v<Remove, t_Limit_Min,
				U_Element_vp<U_Element_vp<0, Part_Sort>+t_Limit_Min, TP_Numbers>,
				U_Element_vp<U_Element_vp<1, Part_Sort>+t_Limit_Min, TP_Numbers>,
				U_Element_vp<U_Element_vp<2, Part_Sort>+t_Limit_Min, TP_Numbers>>;

			using Type = Insert;
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

		using TP_Standard_Search_Number = S_Parameter_Value<U_Element_vp<t_Limit_Min+ Range_Quarter, TP_Numbers>, U_Element_vp<t_Limit_Min + Range_Half, TP_Numbers>, U_Element_vp<t_Limit_Max- Range_Quarter, TP_Numbers>>;

		using Standard_Search = IS_Part_Sort<TP_Standard_Search_Number, 0, 2>::Type;

		using Type = U_Element_t<U_Element_vp<1,Standard_Search>,TP>;

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

		template<int t_Flont, int t_Back = 0, bool t_Judge_Back = T_Judge<Element<Back_Number - t_Back>,T_Standard>::Judge, bool t_End_Fg = ((Flont_Number + t_Flont) >= Back_Number - t_Back)>
		struct S_Quick_Sort_Back
		{
			using Type = S_Quick_Sort_Back<t_Flont, t_Back + 1>::Type;
			static constexpr int N = t_Flont;
			using Type_6 = S_Quick_Sort_Back<t_Flont, t_Back + 1>;
		};

		template<int t_Flont, int t_Back, bool t_End_Fg>
		struct S_Quick_Sort_Back<t_Flont, t_Back, true, t_End_Fg>
		{
			using Change_TP_Number = U_Change_Element_v<Flont_Number + t_Flont, Back_Number - t_Back, TP_Numbers>;
			

			using T= S_Parameter< Element<Flont_Number + t_Flont>, Element<Back_Number - t_Back>>;
			using Type = S_Quick_Sort<Change_TP_Number, t_Limit_Min, t_Limit_Max, t_Flont, t_Back, T_Standard>::Type;
			using Type_7 = S_Quick_Sort<Change_TP_Number, t_Limit_Min, t_Limit_Max, t_Flont, t_Back, T_Standard>;
		};

		template<int t_Flont, int t_Back>
		struct S_Quick_Sort_Back<t_Flont, t_Back, false, true>
		{
			using Type = IS_Next_Quick_Sort<TP_Numbers, t_Limit_Min, Back_Number - t_Back, t_Limit_Max>::Type;
			using Type_8 = IS_Next_Quick_Sort<TP_Numbers, t_Limit_Min, Back_Number - t_Back, t_Limit_Max>;
		};

		template<int t_Flont = 0, bool t_Judge_Flnot = (T_Judge<Element<Flont_Number + t_Flont>, T_Standard>::Judge), bool t_End_Fg = ((Flont_Number + t_Flont) >= Back_Number)>
		struct S_Quick_Sort_Flont
		{
			using Type_3 = S_Quick_Sort_Flont<t_Flont + 1>;
			using T = Element<Flont_Number + t_Flont>;
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

			using T1 = T_Standard;
			using T2 = TP_Numbers;

			using Type = IS_Next_Quick_Sort<TP_Numbers, t_Limit_Min, Flont_Number + t_Flont, t_Limit_Max>::Type;

		};

		using ST = IS_Quick_Sort_Standard<TP_Numbers, t_Limit_Min, t_Limit_Max>::Standard_Search;

		using Type_2 = S_Quick_Sort_Flont<>;

		using Type = S_Quick_Sort_Flont<>::Type;

	};

	template<class TP_Numbers, int t_Limit_Min, int t_Center, int t_Limit_Max>
	struct IS_Next_Quick_Sort
	{
		template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max, bool t_Quick_Sort_Fg = ((t_Limit_Max - t_Limit_Min) > 2)>
		struct S_Next_Sort 
		{
			using Type = S_Quick_Sort<TP_Numbers, t_Limit_Min, t_Limit_Max>::Type;
			using Type_10 = S_Quick_Sort<TP_Numbers, t_Limit_Min, t_Limit_Max>;
		};

		template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max>
		struct S_Next_Sort<TP_Numbers,t_Limit_Min,t_Limit_Max,false>
		{
			using Type = IS_Part_Sort<TP_Numbers, t_Limit_Min, t_Limit_Max>::Type;
			using N = N<t_Limit_Min>;
			using Type_11 = IS_Part_Sort<TP_Numbers, t_Limit_Min, t_Limit_Max>;
		};

		using Flont_Sort = S_Next_Sort<TP_Numbers, t_Limit_Min, t_Center>::Type;
		using Back_Sort = S_Next_Sort<Flont_Sort, t_Center,t_Limit_Max>::Type;
		using ST = TP_Numbers;
		using Type = Back_Sort;
		using Type_9 = //S_Next_Sort<TP_Numbers, t_Limit_Min, t_Center>;
			S_Next_Sort<Flont_Sort, t_Center, t_Limit_Max>;

	};

	template<class TP_Numbers>
	struct S_Data_Sort;

	template<int ...t_Numbers>
	struct S_Data_Sort<S_Parameter_Value<t_Numbers...>>
	{
		using Type = S_Parameter<U_Element_t<t_Numbers, TP>...>;
	};


	using Number_Sort =S_Quick_Sort<typename IS_Index_Sequence<TP::Size>::Type, 0, TP::Size - 1>::Type;

	using Type_1 = S_Quick_Sort<typename IS_Index_Sequence<TP::Size>::Type, 0, TP::Size - 1>;
	using Type = S_Data_Sort<Number_Sort>::Type;

};
