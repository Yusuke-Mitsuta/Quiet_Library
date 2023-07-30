#pragma once

#include"SwapType.h"

//�d�l
//�p�����[�^�p�b�N[T_Parameters...]����[_Index]�Ԗڂ̌^�����o��
//
//template
//_Index::�p�����[�^�p�b�N������o���^�̔ԍ�
//T_Parameters...::�^�̃p�����[�^�p�b�N
template<size_t _Index, class T_FlontParameter, class ...T_Parameters>
	requires (_Index <= sizeof...(T_Parameters))
struct S_Parameter_Element_Type
{
	using Type = S_Parameter_Element_Type<_Index - 1, T_Parameters...>::Type;
};

template<class T_FlontParameter, class ...T_Parameters>
struct S_Parameter_Element_Type<0,T_FlontParameter,T_Parameters...>
{
	using Type = T_FlontParameter;
};

template<size_t _Index, class ...T_Parameters>
	requires (_Index <= sizeof...(T_Parameters))
using S_Parameter_Element_t = S_Parameter_Element_Type<_Index, T_Parameters...>::Type;

template<auto t_Variable>
struct S_Variablea
{
	static constexpr auto Variable = t_Variable;
};

//�d�l
//�p�����[�^�p�b�N[t_Parameters...]����[_Index]�Ԗڂ̕ϐ������o��
//
//template
//_Index::�p�����[�^�p�b�N������o���^�̔ԍ�
//t_Parameters...::�ϐ��̃p�����[�^�p�b�N
template<size_t _Index, auto t_FlontParameter, auto ...t_Parameters>
	requires (_Index <= sizeof...(t_Parameters))
struct S_Parameter_Element_Variable
{
	using Type = S_Parameter_Element_Variable<_Index - 1, t_Parameters...>;

	static constexpr auto Variable = Type::Variable;
};

template<auto t_FlontParameter, auto ...t_Parameters>
struct S_Parameter_Element_Variable<0,t_FlontParameter,t_Parameters...>
{
	static constexpr auto Variable = t_FlontParameter;
};
template<size_t _Index, auto ...t_Parameters>
	requires (_Index <= sizeof...(t_Parameters))
static constexpr auto S_Parameter_Element_v = S_Parameter_Element_Variable<_Index, t_Parameters...>::Variable;


