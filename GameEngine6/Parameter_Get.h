#pragma once

#include"Parameter_Element.h"

//�d�l
//�p�����[�^�p�b�N[T_Parameters...]����[_Index]�Ԗڂ̌^�����o��
//
//template
//_Index::�p�����[�^�p�b�N������o���^�̔ԍ�
//T_Parameters...::�^�̃p�����[�^�p�b�N
//
//�⑫
//�͈͊O�̏ꍇ[std::nullopt_t]���Ԃ�
template<class T_Parameters, class TP_Index>
struct IS_Get_Parameters
{
	template<class T_Parameters,class TP_Index>
	struct S_Get_Parameters;

	template<same_as_template_class<S_Parameter> T_Parameters, size_t... tP_Index>
	struct S_Get_Parameters<T_Parameters,S_Parameter_Value<tP_Index...>>
	{
		using Type = S_Parameter<U_Element_t<tP_Index, T_Parameters>...>;
	};

	template<same_as_template_value<S_Parameter_Value> T_Parameters_Value,size_t... tP_Index>
	struct S_Get_Parameters<T_Parameters_Value, S_Parameter_Value< tP_Index...>>
	{
		using Type = S_Parameter_Value<U_Element_vp<tP_Index, T_Parameters_Value>...>;
	};

	using Type = typename S_Get_Parameters<T_Parameters,TP_Index>::Type;
};

template<same_as_template_class<S_Parameter>T_Parameter, size_t... _Indexs>
using U_Get_Element_t = typename IS_Get_Parameters< T_Parameter, S_Parameter_Value< _Indexs...>>::Type;

template<same_as_template_class<S_Parameter>T_Parameter,same_as_template_value<S_Parameter_Value> TP_Indexs>
using U_Get_Element_P_t = typename IS_Get_Parameters<T_Parameter,TP_Indexs>::Type;


template<same_as_template_value<S_Parameter_Value>T_Parameter_Value, size_t... _Indexs>
using U_Get_Element_v = typename IS_Get_Parameters<T_Parameter_Value, S_Parameter_Value< _Indexs...>>::Type;

template<same_as_template_value<S_Parameter_Value>T_Parameter_Value, same_as_template_value<S_Parameter_Value> TP_Indexs>
using U_Get_Element_P_v = typename IS_Get_Parameters<T_Parameter_Value, TP_Indexs>::Type;