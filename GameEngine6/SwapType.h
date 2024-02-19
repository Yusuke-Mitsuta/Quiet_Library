#pragma once

#include<optional>
#include"Concept.h"
#include"If_Type.h"

//�d�l
//[T_1],[T_2]��[t_Order]�ɂ���ē���ւ���
//
//template
//T_1::�^�C�v1
//T_2::�^�C�v2
//t_Order::true�Ȃ�[T_1],[T_2]�����ւ���
template<class T_1, class T_2,long long t_Order>
struct I_Swap_Type
{
	template<bool t_Order>
	struct S_SwapType
	{
		using Type = T_1;
	};

	template<>
	struct S_SwapType<true>
	{
		using Type = T_2;
	};

	using Type_1 = S_SwapType<static_cast<bool>(t_Order)>::Type;
	using Type_2 = S_SwapType<!static_cast<bool>(t_Order)>::Type;
};

//�d�l
//[t_Order]��0�Ȃ�[T_1],0�ȊO�Ȃ�[T_2]��Ԃ�
//
//template
//T_1::�^�C�v1
//T_2::�^�C�v2
//t_Order::true�Ȃ�[T_1],[T_2]�����ւ���
template<class T_1, class T_2, long long t_Order>
using U_Swap_t1 = typename I_Swap_Type<T_1, T_2, t_Order>::Type_1;

//�d�l
//[t_Order]��0�Ȃ�[T_2],0�ȊO�Ȃ�[T_1]��Ԃ�
//
//template
//T_1::�^�C�v1
//T_2::�^�C�v2
//t_Order::true�Ȃ�[T_1],[T_2]�����ւ���
template<class T_1, class T_2, long long t_Order>
using U_Swap_t2 = typename I_Swap_Type<T_1, T_2, t_Order>::Type_2;

//�d�l
//[T],[invalid_t]��[I_Swap_Type]���쐬����
//
//template
//T::�^�C�v
//t_Order::true�Ȃ�[Type1 = T],false�Ȃ�[Type1 = invalid_t]
template<class T, long long t_Order>
using U_Judge = I_Swap_Type<invalid_t, T, t_Order>;

//�d�l
//[t_Order]��0�Ȃ�[invalid_t],0�ȊO�Ȃ�[T]��Ԃ�
//
//template
//T::�^�C�v
//t_Order::�t���O
template<class T, long long t_Order>
using U_Judge_t = typename U_Judge<T, t_Order>::Type_1;

//�d�l
//[t_1],[t_2]��[t_Order]�ɂ���ē���ւ���
//
//template
//T_1::�ϐ��P
//T_2::�ϐ��P
//t_Order::true�Ȃ�[T_1],[T_2]�����ւ���
template<auto t_1, auto t_2, int t_Order>
struct IS_Swap_Variable
{
	template<bool t_Order>
	struct S_SwapType
	{
		static constexpr auto Variable = t_1;
	};

	template<>
	struct S_SwapType<true>
	{
		static constexpr auto Variable = t_2;
	};

	static constexpr auto _1 = S_SwapType<static_cast<bool>(t_Order)>::Variable;
	static constexpr auto _2 = S_SwapType<!static_cast<bool>(t_Order)>::Variable;
};

template<auto t_1, auto t_2, int t_Order>
using U_Swap_v= IS_Swap_Variable<t_1, t_2, t_Order>;

template<auto t_1, auto t_2, int t_Order>
static constexpr auto U_Swap_v1 = IS_Swap_Variable<t_1, t_2, t_Order>::_1;

template<auto t_1, auto t_2, int t_Order>
static constexpr auto U_Swap_v2 = IS_Swap_Variable<t_1, t_2, t_Order>::_2;