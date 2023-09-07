#pragma once


#pragma once
#include"Concept.h"
#include"Parameter_Element.h"

template<class ...T_Parameters>
struct S_Parameter;

//�d�l
//[S_Parameter]�̗v�f�̂��ϊ��\���A�S�́A�O���A����̎O��ނŔ��肷��
//
//template
//T_Flom::���肷��^
//T_To::�x�[�X�̌^
template<class T_Flom, class T_To, int t_Mode = 0>
struct IS_Parameter_convertible_to
{
private:

public:

	//�d�l
	//�^�̔���̌���
	template<int t_FinishNumber, int t_Flom_Number = 0, int t_To_Number = 0,
		bool t_LoopFg = (t_FinishNumber > t_To_Number) && (0 <= t_To_Number)>
	struct S_Parameter_convertible_to
	{
		using Type = std::bool_constant<(t_FinishNumber == t_To_Number)>;
	};

	//�d�l
	//�^��Flom����To�ɕύX�\�����肵�A�\�Ȃ玟�̌^�̔���Ɉڂ�
	template<int t_FinishNumber, int t_Flom_Number, int t_To_Number>
		requires convertible_to<U_Element_t<t_Flom_Number>,U_Element_t<t_To_Number>>
	struct S_Parameter_convertible_to<t_FinishNumber, t_Flom_Number, t_To_Number, true>
	{
		using Type = S_Parameter_convertible_to<t_FinishNumber, t_Flom_Number, t_To_Number>::Type;
	};
	
	//�d�l
	//tuple�^�̗v�f�̕ϊ��\�����肷��
	using All = S_Parameter_convertible_to<std::max(T_Flom::Size, T_To::Size)>::Type;

	//�d�l
	//tuple�^�̗v�f�̑O�����ϊ��\�����肷��
	using FlontPart = S_Parameter_convertible_to<T_Flom::Size>::Type;

	//�d�l
	//tuple�^�̗v�f�̌�����ϊ��\�����肷��
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

//�d�l
//[S_Parameter]�̗v�f�̕ϊ��\�����肷��
//
//template
//T_Flom::���肷��[S_Parameter]
//T_To::�x�[�X��[S_Parameter]
template<class _Flom, class _To>
concept parameter_convertible_to = std::same_as<std::true_type, typename IS_Parameter_convertible_to<_Flom, _To>::All>;

//�d�l
//[S_Parameter]�̗v�f�̑O���������ϊ��\�����肷��
//
//template
//T_Flom::���肷��[S_Parameter]
//T_To::�x�[�X��[S_Parameter]
template<class _Flom, class _To>
concept parameter_flont_part_convertible_to = std::same_as<std::true_type, typename IS_Parameter_convertible_to<_Flom, _To>::FlontPart>;

//�d�l
//[S_Parameter]�̗v�f�̌���������ϊ��\�����肷��
//
//template
//T_Flom::���肷��[S_Parameter]
//T_To::�x�[�X��[S_Parameter]
template<class _Flom, class _To>
concept parameter_back_part_convertible_to = std::same_as<std::true_type, typename IS_Parameter_convertible_to<_Flom, _To>::BackPart>;
