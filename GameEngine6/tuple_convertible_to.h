#pragma once
#include<tuple>
#include"Concept.h"
#include"Using_Type.h"

//�d�l
//tuple�^�̗v�f�̂��ϊ��\���A�S�́A�O���A����̎O��ނŔ��肷��
//
//template
//T_Flom::���肷��^
//T_To::�x�[�X�̌^
template<class T_Flom, class T_To>
struct IS_tuple_convertible_to
{
private:
	template<size_t t_FlomNumber>
	using flom_tuple_element = std::tuple_element<t_FlomNumber, T_Flom>::type;

	template<size_t t_ToNumber>
	using to_tuple_element = std::tuple_element<t_ToNumber,T_To>::type;
public:

	//�d�l
	//�^�̔���̌���
	template<Size_Type t_TupleFinishNumber, Size_Type t_TupleFlomNumber = 0, Size_Type t_TupleToNumber = 0,
		bool t_LoopFg=(t_TupleFinishNumber>t_TupleToNumber)>
	struct S_tuple_convertible_to
	{
		using Type =std::bool_constant<(t_TupleFinishNumber == t_TupleToNumber)>;
	};
	//�d�l
	//�^��Flom����To�ɕύX�\�����肵�A�\�Ȃ玟�̌^�̔���Ɉڂ�
	template<Size_Type t_TupleFinishNumber, Size_Type t_TupleFlomNumber, Size_Type t_TupleToNumber>
		requires convertible_to<flom_tuple_element<t_TupleFlomNumber>, to_tuple_element<t_TupleToNumber>>
	struct S_tuple_convertible_to<t_TupleFinishNumber,t_TupleFlomNumber,t_TupleToNumber,true>
	{
		using Type = S_tuple_convertible_to<t_TupleFinishNumber,t_TupleFlomNumber+1, t_TupleToNumber+1>::Type;
	};

	//�d�l
	//tuple�^�̗v�f�̕ϊ��\�����肷��
	using All = S_tuple_convertible_to<std::tuple_size<T_To>::value>::Type;

	//�d�l
	//tuple�^�̗v�f�̑O�����ϊ��\�����肷��
	using FlontPart = S_tuple_convertible_to<std::tuple_size<T_Flom>::value>::Type;
	
	//�d�l
	//tuple�^�̗v�f�̌�����ϊ��\�����肷��
	using BackPart = S_tuple_convertible_to<std::tuple_size<T_To>::value, 0, std::tuple_size<T_To>::value - std::tuple_size<T_Flom>::value>::Type;

};


//�d�l
//tuple�^�̗v�f�̕ϊ��\�����肷��
//
//template
//T_Flom::���肷��tuple�^
//T_To::�x�[�X��tuple�^
template<class _Flom, class _To>
concept tuple_convertible_to = std::same_as<std::true_type,typename IS_tuple_convertible_to<_Flom, _To>::All>;

//�d�l
//tuple�^�̗v�f�̑O���������ϊ��\�����肷��
//
//template
//T_Flom::���肷��tuple�^
//T_To::�x�[�X��tuple�^
template<class _Flom, class _To>
concept tuple_flont_part_convertible_to = std::same_as<std::true_type,typename IS_tuple_convertible_to<_Flom, _To>::FlontPart>;

//�d�l
//tuple�^�̗v�f�̌���������ϊ��\�����肷��
//
//template
//T_Flom::���肷��tuple�^
//T_To::�x�[�X��tuple�^
template<class _Flom, class _To>
concept tuple_back_part_convertible_to = std::same_as<std::true_type,typename IS_tuple_convertible_to<_Flom, _To>::BackPart>;
