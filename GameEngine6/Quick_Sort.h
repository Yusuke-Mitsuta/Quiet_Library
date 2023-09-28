#pragma once

#include"SwapType.h"
#include"Parameter.h"

#include"Tuple.h"

//仕様
//[S_Parameter]内の型を、[T_Judge< class,class >::Judge]によって並び替える
//
//テンプレート
//[T_Judge]::比較条件
//[TP]::[S_Parameter]型の型リスト
//[t_Reverse_Fg]::trueだと並び順を反転させる
// 
//補足
//[T_Judge]はテンプレートを二つ取り、静的なメンバー変数として[static constexpr bool Judge]が存在する事
template<template<class, class>class T_Judge, class TP, bool t_Reverse_Fg = false>
struct IS_Quick_Sort
{
private:

	template<class T_1,class T_2>
	static constexpr bool t_Judge = t_Reverse_Fg ^ T_Judge<T_1, T_2>::Judge;

	//仕様
	//[TP_Numbers]内の番号の、[t_Limit_Min]番目から[int t_Limit_Max]番目までの範囲で並び替える補助クラス
	//
	//テンプレート
	//TP_Numbers::[TP]を参照する番号リスト
	//t_Limit_Min::[TP_Numbers]の参照する起点の要素番号
	//t_Limit_Max::[TP_Numbers]の参照する終点の要素番号
	// 
	//補足
	//並び替え出来る要素は3個まで、
	//それ以上は並び替えされずに出力される
	template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max>
	struct IS_Part_Sort
	{
		template<size_t _Index>
		using Element = N_Tuple::U_Element_t<N_Tuple::U_Element_v<_Index, TP_Numbers>,TP>;

		template<class TP_Numbers=TP_Numbers, int t_Limit_Min = t_Limit_Min, int t_Limit_Max=t_Limit_Max, int t_Range = (t_Limit_Max - t_Limit_Min)>
		struct S_Part_Sort
		{
			using Type = TP_Numbers;
		};

		//仕様
		//並び替える要素が2つの時
		template<same_as_template_value<S_Parameter_Value> TP_Numbers, int t_Limit_Min, int t_Limit_Max>
		struct S_Part_Sort<TP_Numbers,t_Limit_Min,t_Limit_Max,1>
		{
			static constexpr bool Judge = t_Judge<Element<t_Limit_Max>, Element<t_Limit_Min>>;

			using Swap_1 = TP_Numbers;

			using Swap_2 = N_Tuple::U_Swap<TP_Numbers, t_Limit_Min, t_Limit_Max>;
				//U_Change_Element_v<t_Limit_Min, t_Limit_Max, TP_Numbers>;

			using Type = U_Swap_t1<Swap_1, Swap_2, Judge>;

		};
		//仕様
		//並び替える要素が3つの時
		template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max>
		struct S_Part_Sort<TP_Numbers, t_Limit_Min, t_Limit_Max, 2>
		{
			template<int Index_1,int Index_2>
			static constexpr bool Judge = t_Judge<Element<t_Limit_Min + Index_1>, Element<t_Limit_Min + Index_2>>;

			template<int t_Center_Number,
				int t_Side_Number_1,
				int t_Side_Number_2>
			struct S_Judge_Side
			{
				using Side_Number = U_Swap_v<t_Side_Number_1, t_Side_Number_2,
					Judge<t_Side_Number_1, t_Side_Number_2>>;
				using Type = N_Tuple::Tuple_v<Side_Number::_2, t_Center_Number, Side_Number::_1>;
			};

			template<	
				bool t_Center_0 = !(Judge<0, 1>^ Judge<2, 0>),
				bool t_Center_1 = !(Judge<0, 1> ^ Judge<1, 2>),
				bool t_Center_2 = !(Judge<1, 2> ^ Judge<2, 0>)>
			struct S_Judge_Center
			{
				using Type = N_Tuple::Tuple_v<0, 1, 2>;
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
			using Remove_Tuple = typename N_Tuple::U_Select<t_Limit_Min, TP_Numbers>::Remove::Remove::Romove;
				//U_Remove_Element_v<TP_Numbers, t_Limit_Min ,t_Limit_Min + 1, t_Limit_Min + 2>;

			using Insert = N_Tuple::U_Insert<Remove_Tuple, N_Tuple::U_Calculate_plus<Part_Sort, t_Limit_Min>>;


				//U_Insert_Element_P_v<Remove_Tuple,t_Limit_Min,
				//U_Get_Element_v<TP_Numbers, U_Element_vp<0, Part_Sort>+t_Limit_Min, U_Element_vp<1, Part_Sort>+t_Limit_Min, U_Element_vp<2, Part_Sort>+t_Limit_Min>>;

			using Type = Insert;
		};

		using Type = S_Part_Sort<>::Type;

	};

	//仕様
	//Quick_Sortの基準になる値を範囲から選定する
	//
	//テンプレート
	//TP_Numbers::[TP]を参照する番号リスト
	//t_Limit_Min::[TP_Numbers]の参照する起点の要素番号
	//t_Limit_Max::[TP_Numbers]の参照する終点の要素番号
	template<class TP_Numbers, int t_Limit_Min,int t_Limit_Max>
	struct IS_Quick_Sort_Standard
	{
		static constexpr int Range = t_Limit_Max - t_Limit_Min;
		static constexpr int Range_Half = static_cast<int>(Range * 0.5f);
		static constexpr int Range_Quarter = static_cast<int>(Range_Half * 0.5f);

		using TP_Standard_Search_Number = N_Tuple::U_Extract<TP_Numbers, N_Tuple::Tuple_v< t_Limit_Min + Range_Quarter, t_Limit_Min + Range_Half, t_Limit_Max - Range_Quarter>>;
			
			
			//S_Parameter_Value<U_Element_vp<t_Limit_Min+ Range_Quarter, TP_Numbers>, U_Element_vp<t_Limit_Min + Range_Half, TP_Numbers>, U_Element_vp<t_Limit_Max- Range_Quarter, TP_Numbers>>;

		using Standard_Search = IS_Part_Sort<TP_Standard_Search_Number, 0, 2>::Type;

		using Type = N_Tuple::U_Element_t<N_Tuple::U_Element_v<1, Standard_Search>,TP>;

	};

	template<class TP_Numbers, int t_Limit_Min, int t_Center, int t_Limit_Max>
	struct IS_Next_Quick_Sort;

	//仕様
	//範囲内のクイックソートを行う
	//
	//テンプレート
	//TP_Numbers::[TP]を参照する番号リスト
	//t_Limit_Min::[TP_Numbers]の参照する起点の要素番号
	//t_Limit_Max::[TP_Numbers]の参照する終点の要素番号
	//t_Flont::一度値を交換した後、続きから探索する為の補助番号
	//t_Back::一度値を交換した後、続きから探索する為の補助番号
	//T_Standard::交換の基準とする値
	template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max, int t_Flont = 0, int t_Back = 0,
		class T_Standard = typename IS_Quick_Sort_Standard<TP_Numbers,t_Limit_Min,t_Limit_Max>::Type>
	struct S_Quick_Sort
	{
		template<size_t _Index>
		using Element = N_Tuple::U_Element_t<N_Tuple::U_Element_v<_Index, TP_Numbers>, TP>;

		static constexpr int Flont_Number = t_Limit_Min + t_Flont;
		static constexpr int Back_Number = t_Limit_Max - t_Back;

		//仕様
		//範囲内の後方から探索する
		//交換する候補の発見時は、発見済みの前方の値と入れ替えを実施し、再度前方から値を探索する
		//未発見時は次の探索に移行する
		template<int t_Flont, int t_Back = 0, bool t_Judge_Back = t_Judge<Element<Back_Number - t_Back>,T_Standard>, bool t_End_Fg = ((Flont_Number + t_Flont)>= Back_Number - t_Back)>
		struct S_Quick_Sort_Back
		{
			using Type = S_Quick_Sort_Back<t_Flont, t_Back + 1>::Type;
		};

		template<int t_Flont, int t_Back, bool t_End_Fg>
		struct S_Quick_Sort_Back<t_Flont, t_Back, true, t_End_Fg>
		{
			using Change_TP_Number = N_Tuple::U_Swap<TP_Numbers, Flont_Number + t_Flont, Back_Number - t_Back>;

			using Type = S_Quick_Sort<Change_TP_Number, t_Limit_Min, t_Limit_Max, t_Flont, t_Back, T_Standard>::Type;
		};

		template<int t_Flont, int t_Back>
		struct S_Quick_Sort_Back<t_Flont, t_Back, false, true>
		{
			using Type = IS_Next_Quick_Sort<TP_Numbers, t_Limit_Min, Back_Number - t_Back, t_Limit_Max>::Type;
		};

		//仕様
		//範囲内の前方から探索する
		//交換する候補の発見時は、後方からの探索を実施する
		//未発見時は次の探索に移行する
		template<int t_Flont = 0, bool t_Judge_Flnot = t_Judge<Element<Flont_Number + t_Flont>, T_Standard>, bool t_End_Fg = ((Flont_Number + t_Flont) >= Back_Number)>
		struct S_Quick_Sort_Flont
		{
			using Type = //TP_Numbers;
				S_Quick_Sort_Flont<t_Flont + 1>::Type;
		};

		template<int t_Flont>
		struct S_Quick_Sort_Flont<t_Flont, false, false>
		{
			using Type = TP_Numbers;
				//S_Quick_Sort_Back<t_Flont>::Type;
		};

		template<int t_Flont, bool t_Judge_Flnot>
		struct S_Quick_Sort_Flont<t_Flont, t_Judge_Flnot, true>
		{
			using Type = TP_Numbers;
				//IS_Next_Quick_Sort<TP_Numbers, t_Limit_Min, Flont_Number + t_Flont, t_Limit_Max>::Type;
		};

		using Type=S_Quick_Sort_Flont<>::Type;

	};


	//仕様
	//基準を中心に分けられたデータを、更に探索にかける
	//分けられた要素が3つ以下なら選択ソート、それ以外はクイックソートを実施する
	template<class TP_Numbers, int t_Limit_Min, int t_Center, int t_Limit_Max>
	struct IS_Next_Quick_Sort
	{
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
		using Back_Sort = S_Next_Sort<Flont_Sort, t_Center,t_Limit_Max>::Type;

		using Type = Back_Sort;

	};

	template<class TP_Numbers>
	struct S_Data_Sort;
	
	//仕様
	//参照に使用していた、番号のリスト順にデータを入れ替える
	template<int ...t_Numbers>
	struct S_Data_Sort<N_Tuple::Tuple_v<t_Numbers...>>
	{
		using Type = N_Tuple::Tuple_t<N_Tuple::U_Element_t<t_Numbers, TP>...>;
	};

	using Number_Sort = S_Quick_Sort<
		//typename IS_Index_Sequence<TP::Size>::Type, 0, 
		N_Tuple::Tuple_v<0,1>,
		0,
		TP::Size - 1>::Type;


public:

	using Type = Number_Sort;
		//S_Data_Sort<Number_Sort>::Type;

};
