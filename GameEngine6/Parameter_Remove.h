#pragma once

#include"Concept.h"
#include"Parameter_Element.h"

//�d�l
//[S_Parameter]����[t_Remove_Indexs...]�Ԗڂ̗v�f����菜��
template<same_as_template_class<S_Parameter> T_Parameter, int ...t_Remove_Indexs>
struct IS_Remove_Parameters
{
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

	using Type = S_Remove_Parameters<>::Type;
};

template<same_as_template_class<S_Parameter> T_Parameter, int ...t_Remove_Indexs>
using U_Remove_Element = IS_Remove_Parameters<T_Parameter, t_Remove_Indexs...>;

template<same_as_template_class<S_Parameter> T_Parameter, int ...t_Remove_Indexs>
using U_Remove_Element_t = typename IS_Remove_Parameters<T_Parameter, t_Remove_Indexs...>::Type;