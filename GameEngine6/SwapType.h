#pragma once

//�d�l
//[T_1],[T_2]��[t_Order]�ɂ���ē���ւ���
//
//template
//T_1::�^�C�v1
//T_2::�^�C�v2
//t_Order::true�Ȃ�[T_1],[T_2]�����ւ���
template<class T_1, class T_2, bool t_Order>
struct IS_SwapType
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

	using Type_1 = S_SwapType<t_Order>::Type;
	using Type_2 = S_SwapType<!t_Order>::Type;
};

