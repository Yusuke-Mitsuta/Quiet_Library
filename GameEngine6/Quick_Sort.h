#pragma once

#include"SwapType.h"
#include"Parameter.h"

//template<template<class, class>class T_Judge, class TP>
//struct IS_Quick_Sort
//{
//
//
//	template<class TP, bool t_Finish_Fg = (TP::Size > 2)>
//		struct S_Quick_Sort_Base
//	{
//
//		struct S_Quick_Sort_Standard
//		{
//			using Element_0 = U_Element_t<0, TP>;
//			using Element_1 = U_Element_t<1, TP>;
//			using Element_2 = U_Element_t<2, TP>;
//
//			static constexpr bool Judge_01 = T_Judge<Element_0, Element_1>::Judge;
//			static constexpr bool Judge_12 = T_Judge<Element_1, Element_2>::Judge;
//			static constexpr bool Judge_20 = T_Judge<Element_2, Element_0>::Judge;
//
//			using Element_02 = U_Swap_t1<Element_0, Element_2, (Judge_12&& Judge_20)>;
//
//			using Type = U_Swap_t1<Element_02, Element_1, (Judge_01 && Judge_12)>;
//
//		};
//
//		template<class TP_Flont, class TP_Back, class T_Standard, int t_Flont, int t_Back, bool t_Flont_Select_Fg, bool t_Finish_Fg = (t_Flont > t_Back)>
//			struct S_Quick_Sort;
//
//		template<class TP_Flont,int t_Flont, class T_Standard>
//		struct S_Quick_Sort_Flont
//		{
//			using Flont= U_Element_t<t_Flont,TP>;
//
//			static constexpr bool Judge_Flnot = T_Judge<Flont, T_Standard>::Judge;
//
//		//	using Type = 
//
//		};
//
//
//		using Type = S_Quick_Sort<S_Parameter<>, S_Parameter<>, S_Quick_Sort_Standard::Type, 0, TP::Size - 1, true>::Type;
//	};
//
//	template<class TP>
//	struct S_Quick_Sort_Base<TP, false>
//	{
//		using Type = TP;
//	};
//
//	using Type = S_Quick_Sort_Base<TP>;
//};
//
