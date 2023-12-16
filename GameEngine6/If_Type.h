#pragma once

#include<optional>
#include"Concept.h"

//�d�l
//[t_Order=true]�Ȃ�[ type_1 = [T_1] ],[t_Order=false]�Ȃ�[ type_1 = [T_2] ]
//
//template
//T_1::�^�C�v1
//T_2::�^�C�v2
//t_Order::[false]�Ȃ�[T_1],[T_2]�����ւ���
template<class T_1, class T_2, long long t_Order>
struct I_if_type
{
	template<bool t_Order>
	struct S_if_type
	{
		using type = T_1;
	};

	template<>
	struct S_if_type<false>
	{
		using type = T_2;
	};

	using type_1 = S_if_type<static_cast<bool>(t_Order)>::type;
	using type_2 = S_if_type<!static_cast<bool>(t_Order)>::type;
};

template<class T_1, class T_2, long long t_Order>
using U_if = I_if_type<T_1, T_2, t_Order>;

template<class T_1, class T_2, long long t_Order>
using U_if_t1 = I_if_type<T_1, T_2, t_Order>::type_1;

template<class T_1, class T_2, long long t_Order>
using U_if_t2 = I_if_type<T_1, T_2, t_Order>::type_2;
