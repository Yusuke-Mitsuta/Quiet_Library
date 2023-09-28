#pragma once

#include"SwapType.h"
#include"Parameter.h"

#include"Tuple.h"

//�d�l
//[S_Parameter]���̌^���A[T_Judge< class,class >::Judge]�ɂ���ĕ��ёւ���
//
//�e���v���[�g
//[T_Judge]::��r����
//[TP]::[S_Parameter]�^�̌^���X�g
//[t_Reverse_Fg]::true���ƕ��я��𔽓]������
// 
//�⑫
//[T_Judge]�̓e���v���[�g�����A�ÓI�ȃ����o�[�ϐ��Ƃ���[static constexpr bool Judge]�����݂��鎖
template<template<class, class>class T_Judge, class TP, bool t_Reverse_Fg = false>
struct IS_Quick_Sort
{
private:

	template<class T_1,class T_2>
	static constexpr bool t_Judge = t_Reverse_Fg ^ T_Judge<T_1, T_2>::Judge;

	//�d�l
	//[TP_Numbers]���̔ԍ��́A[t_Limit_Min]�Ԗڂ���[int t_Limit_Max]�Ԗڂ܂ł͈̔͂ŕ��ёւ���⏕�N���X
	//
	//�e���v���[�g
	//TP_Numbers::[TP]���Q�Ƃ���ԍ����X�g
	//t_Limit_Min::[TP_Numbers]�̎Q�Ƃ���N�_�̗v�f�ԍ�
	//t_Limit_Max::[TP_Numbers]�̎Q�Ƃ���I�_�̗v�f�ԍ�
	// 
	//�⑫
	//���ёւ��o����v�f��3�܂ŁA
	//����ȏ�͕��ёւ����ꂸ�ɏo�͂����
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

		//�d�l
		//���ёւ���v�f��2�̎�
		template<same_as_template_value<S_Parameter_Value> TP_Numbers, int t_Limit_Min, int t_Limit_Max>
		struct S_Part_Sort<TP_Numbers,t_Limit_Min,t_Limit_Max,1>
		{
			static constexpr bool Judge = t_Judge<Element<t_Limit_Max>, Element<t_Limit_Min>>;

			using Swap_1 = TP_Numbers;

			using Swap_2 = N_Tuple::U_Swap<TP_Numbers, t_Limit_Min, t_Limit_Max>;
				//U_Change_Element_v<t_Limit_Min, t_Limit_Max, TP_Numbers>;

			using Type = U_Swap_t1<Swap_1, Swap_2, Judge>;

		};
		//�d�l
		//���ёւ���v�f��3�̎�
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

	//�d�l
	//Quick_Sort�̊�ɂȂ�l��͈͂���I�肷��
	//
	//�e���v���[�g
	//TP_Numbers::[TP]���Q�Ƃ���ԍ����X�g
	//t_Limit_Min::[TP_Numbers]�̎Q�Ƃ���N�_�̗v�f�ԍ�
	//t_Limit_Max::[TP_Numbers]�̎Q�Ƃ���I�_�̗v�f�ԍ�
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

	//�d�l
	//�͈͓��̃N�C�b�N�\�[�g���s��
	//
	//�e���v���[�g
	//TP_Numbers::[TP]���Q�Ƃ���ԍ����X�g
	//t_Limit_Min::[TP_Numbers]�̎Q�Ƃ���N�_�̗v�f�ԍ�
	//t_Limit_Max::[TP_Numbers]�̎Q�Ƃ���I�_�̗v�f�ԍ�
	//t_Flont::��x�l������������A��������T������ׂ̕⏕�ԍ�
	//t_Back::��x�l������������A��������T������ׂ̕⏕�ԍ�
	//T_Standard::�����̊�Ƃ���l
	template<class TP_Numbers, int t_Limit_Min, int t_Limit_Max, int t_Flont = 0, int t_Back = 0,
		class T_Standard = typename IS_Quick_Sort_Standard<TP_Numbers,t_Limit_Min,t_Limit_Max>::Type>
	struct S_Quick_Sort
	{
		template<size_t _Index>
		using Element = N_Tuple::U_Element_t<N_Tuple::U_Element_v<_Index, TP_Numbers>, TP>;

		static constexpr int Flont_Number = t_Limit_Min + t_Flont;
		static constexpr int Back_Number = t_Limit_Max - t_Back;

		//�d�l
		//�͈͓��̌������T������
		//����������̔������́A�����ς݂̑O���̒l�Ɠ���ւ������{���A�ēx�O������l��T������
		//���������͎��̒T���Ɉڍs����
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

		//�d�l
		//�͈͓��̑O������T������
		//����������̔������́A�������̒T�������{����
		//���������͎��̒T���Ɉڍs����
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


	//�d�l
	//��𒆐S�ɕ�����ꂽ�f�[�^���A�X�ɒT���ɂ�����
	//������ꂽ�v�f��3�ȉ��Ȃ�I���\�[�g�A����ȊO�̓N�C�b�N�\�[�g�����{����
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
	
	//�d�l
	//�Q�ƂɎg�p���Ă����A�ԍ��̃��X�g���Ƀf�[�^�����ւ���
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
