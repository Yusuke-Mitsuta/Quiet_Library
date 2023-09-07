#pragma once

#include"Concept.h"
#include"Parameter_Element.h"

//�d�l
//[S_Parameter]����[t_Remove_Indexs...]�Ԗڂ̗v�f����菜��
// 
//�e���v���[�g
//T_Parameter::�v�f����菜���p�����[�^
//t_Remove_Indexs...::��菜���v�f�̔ԍ�
template<same_as_template_class<S_Parameter> T_Parameter, int ...t_Remove_Indexs>
struct IS_Remove_Parameters
{
private:
	enum class E_State
	{
		Not_Remove,
		Remove,
		End
	};

	//�d�l
	//[S_Remove_Parameters]�̃X�e�[�g�Ǘ����s��
	//
	//Remove::[t_Remove_Indexs...]�̔ԍ��ɓ��Ă͂܂�����
	//Not_Remove::[t_Remove_Indexs...]�̔ԍ��ɓ��Ă͂܂�Ȃ���
	//End::�S�Ă̏������I��������
	template<int t_Parameter_Number, int t_Remove_Indexs_Number,
		bool t_Remove_End_Fg = (sizeof...(t_Remove_Indexs) == t_Remove_Indexs_Number),
		bool t_End_Fg = (T_Parameter::Size == t_Parameter_Number)>
	struct S_Select_State
	{
		static constexpr E_State State = U_Swap_v1< E_State::Not_Remove, E_State::Remove, (t_Parameter_Number == U_Element_v<t_Remove_Indexs_Number, t_Remove_Indexs...>)>;
	};

	template<int t_Parameter_Number, int t_Remove_Indexs_Number, bool t_End_Fg>
	struct S_Select_State<t_Parameter_Number, t_Remove_Indexs_Number, true, t_End_Fg>
	{
		static constexpr E_State State = E_State::Not_Remove;
	};

	template<int t_Parameter_Number, int t_Remove_Indexs_Number>
	struct S_Select_State<t_Parameter_Number, t_Remove_Indexs_Number, true, true>
	{
		static constexpr E_State State = E_State::End;
	};


	template<class T_Result_Parameter = S_Parameter<>, int t_Parameter_Number = 0, int t_Remove_Indexs_Number = 0,
		E_State t_State = S_Select_State<t_Parameter_Number, t_Remove_Indexs_Number>::State>
	struct S_Remove_Parameters
	{
		using Type = T_Result_Parameter;
	};

	template<class T_Result_Parameter, int t_Parameter_Number, int t_Remove_Indexs_Number>
	struct S_Remove_Parameters<T_Result_Parameter, t_Parameter_Number, t_Remove_Indexs_Number, E_State::Remove>
	{
		using Type = S_Remove_Parameters<T_Result_Parameter, t_Parameter_Number + 1, t_Remove_Indexs_Number + 1>::Type;
	};

	template<class ...TP_Result_Parameter, int t_Parameter_Number, int t_Remove_Indexs_Number>
	struct S_Remove_Parameters<S_Parameter<TP_Result_Parameter...>, t_Parameter_Number, t_Remove_Indexs_Number, E_State::Not_Remove>
	{
		using Type = S_Remove_Parameters<S_Parameter<TP_Result_Parameter..., U_Element_t<t_Parameter_Number, T_Parameter>>, t_Parameter_Number + 1, t_Remove_Indexs_Number>::Type;
	};
public:
	using Type = S_Remove_Parameters<>::Type;
};

template<same_as_template_class<S_Parameter> T_Parameter, same_as_template_value<S_Parameter_Value> T_Remove_Index>
struct S_Remove_Parameters_Helper;

//�d�l
//[S_Parameter_Value]����[t_Remove_Indexs...]�����o���A[IS_Remove_Parameters]�ɑ���
template<same_as_template_class<S_Parameter> T_Parameter, int ...t_Remove_Indexs>
struct S_Remove_Parameters_Helper<T_Parameter,S_Parameter_Value<t_Remove_Indexs...>>
{
	using Type= typename IS_Remove_Parameters<T_Parameter, t_Remove_Indexs...>::Type;
};

template<same_as_template_class<S_Parameter> T_Parameter, int ...t_Remove_Indexs>
using U_Remove_Element = IS_Remove_Parameters<T_Parameter, t_Remove_Indexs...>;

//�d�l
//[S_Parameter]����[t_Remove_Indexs...]�Ԗڂ̗v�f����菜��
// 
//�e���v���[�g
//T_Parameter::�v�f����菜���p�����[�^
//t_Remove_Indexs...::��菜���v�f�̔ԍ�
//
//�⑫
//[t_Remove_Indexs...]��[S_Parameter_Value]�Ŏ󂯎��ꍇ��[U_Remove_Element_P_t]�𗘗p���鎖
template<same_as_template_class<S_Parameter> T_Parameter, int ...t_Remove_Indexs>
using U_Remove_Element_t = typename IS_Remove_Parameters<T_Parameter, t_Remove_Indexs...>::Type;

//�d�l
//[S_Parameter]����[S_Parameter_Value< t_Remove_Indexs... >]�Ԗڂ̗v�f����菜��
//
//�e���v���[�g
//T_Parameter::�v�f����菜���p�����[�^
//T_Remove_Index::[S_Parameter_Value]�Ƀ��b�s���O���ꂽ��菜���v�f�̔ԍ�
// 
//�⑫
//[t_Remove_Indexs...]���ϒ������Ŏ󂯎��ꍇ��[U_Remove_Element_t]�𗘗p���鎖
template<same_as_template_class<S_Parameter> T_Parameter, same_as_template_value<S_Parameter_Value> T_Remove_Index>
using U_Remove_Element_P_t = typename S_Remove_Parameters_Helper<T_Parameter, T_Remove_Index>::Type;

//�d�l
//[S_Parameter_Value]����[t_Remove_Indexs...]�Ԗڂ̗v�f����菜��
// 
//�e���v���[�g
//T_Parameter_Value::�v�f����菜���p�����[�^
//t_Remove_Indexs...::��菜���v�f�̔ԍ�
// 
//�⑫
//[t_Remove_Indexs...]��[S_Parameter_Value]�Ŏ󂯎��ꍇ��[U_Remove_Element_P_v]�𗘗p���鎖
template<same_as_template_value<S_Parameter_Value> T_Parameter_Value, int ...t_Remove_Indexs>
using U_Remove_Element_v = typename IS_Parameter_Class_Change_Value<typename IS_Remove_Parameters<typename T_Parameter_Value::Parameter_Type, t_Remove_Indexs...>::Type>::Type;

//�d�l
//[S_Parameter_Value]����[S_Parameter_Value< t_Remove_Indexs... >]�Ԗڂ̗v�f����菜��
//
//�e���v���[�g
//T_Parameter_Value::�v�f����菜���p�����[�^
//T_Remove_Index::[S_Parameter_Value]�Ƀ��b�s���O���ꂽ��菜���v�f�̔ԍ�
// 
//�⑫
//[t_Remove_Indexs...]���ϒ������Ŏ󂯎��ꍇ��[U_Remove_Element_P_v]�𗘗p���鎖
template<same_as_template_value<S_Parameter_Value> T_Parameter_Value, same_as_template_value<S_Parameter_Value> T_Remove_Index>
using U_Remove_Element_P_v = typename IS_Parameter_Class_Change_Value<typename S_Remove_Parameters_Helper<typename T_Parameter_Value::Parameter_Type, T_Remove_Index>::Type>::Type;
