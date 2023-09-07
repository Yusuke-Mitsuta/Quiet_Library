#pragma once

#include"Concept.h"
#include"Parameter_Element.h"

//仕様
//[S_Parameter]の[t_Insert_Index_Point]番目から、[TP_Insert...]を挿入する
template<same_as_template_class<S_Parameter> T_Parameter, int t_Insert_Index_Point, class ...TP_Insert>
struct IS_Insert_Parameters
{
private:

	template<
		class T_Rest_Parameter = T_Parameter,
		class T_Result_Parameter = S_Parameter<>,
		int t_Parameter_Number = 0,
		bool t_Insert_Fg = (t_Parameter_Number == t_Insert_Index_Point)>
	struct S_Insert_Parameters;

	template<class TP_Rest_Flnot_Parameter, class ...TP_Rest_Parameter, class ...TP_Migrated_Parameter, int t_Parameter_Number>
	struct S_Insert_Parameters<
		S_Parameter<TP_Rest_Flnot_Parameter, TP_Rest_Parameter...>,
		S_Parameter<TP_Migrated_Parameter...>,
		t_Parameter_Number, false>
	{

		using Type = S_Insert_Parameters<
			S_Parameter<TP_Rest_Parameter...>,
			S_Parameter<TP_Migrated_Parameter..., TP_Rest_Flnot_Parameter>,
			t_Parameter_Number + 1>::Type;

	};

	template<class ...TP_Rest_Parameter, class ...TP_Migrated_Parameter, int t_Parameter_Number>
	struct S_Insert_Parameters<
		S_Parameter<TP_Rest_Parameter...>,
		S_Parameter<TP_Migrated_Parameter...>,
		t_Parameter_Number, true>
	{
		using Type = S_Parameter<TP_Migrated_Parameter..., TP_Insert..., TP_Rest_Parameter...>;
	};

	template<class ...TP_Insert>
	struct S_Chak_Parameter
	{
		using Type = S_Insert_Parameters<>::Type;
	};

	template<class ...TP_Insert>
	struct S_Chak_Parameter<S_Parameter<TP_Insert...>>
	{
		using Type = IS_Insert_Parameters<T_Parameter, t_Insert_Index_Point, TP_Insert...>::Type;
	};

public:

	using Type = S_Chak_Parameter<TP_Insert...>::Type;

};

template<same_as_template_class<S_Parameter> T_Parameter, int t_Insert_Index_Point, class ...TP_Insert>
using U_Insert_Element = IS_Insert_Parameters<T_Parameter, t_Insert_Index_Point, TP_Insert...>;

//仕様
//[T_Parameter]の[t_Insert_Index_Point]番目から、[TP_Insert...]を挿入する
//
//補足
//[TP_Insert...]を[S_Parameter]で受け取る場合は[U_Insert_Element_P_t]を利用する事
template<same_as_template_class<S_Parameter> T_Parameter, int t_Insert_Index_Point, class ...TP_Insert>
using U_Insert_Element_t = typename IS_Insert_Parameters<T_Parameter, t_Insert_Index_Point, TP_Insert...>::Type;

//仕様
//[T_Parameter]の[t_Insert_Index_Point]番目から、[T_Parameter<TP_Insert...>]の中身を挿入する
//
//補足
//[TP_Insert...]を可変長引数で受け取る場合は[U_Insert_Element_t]を利用する事
template<same_as_template_class<S_Parameter> T_Parameter, int t_Insert_Index_Point, class ...TP_Insert>
using U_Insert_Element_P_t = U_Insert_Element_t<T_Parameter, t_Insert_Index_Point, TP_Insert...>;

//仕様
//[T_Parameter_Value]の[t_Insert_Index_Point]番目から、[tP_Insert...]を挿入する
//
//補足
//[tP_Insert...]を[S_Parameter_Value]で受け取る場合は[U_Insert_Element_P_v]を利用する事
template<same_as_template_value<S_Parameter_Value> T_Parameter_Value, int t_Insert_Index_Point, auto ...tP_Insert>
using U_Insert_Element_v = typename IS_Parameter_Class_Change_Value<typename IS_Insert_Parameters<typename T_Parameter_Value::Parameter_Type, t_Insert_Index_Point, integral_constant<tP_Insert>...>::Type>::Type;

//仕様
//[T_Parameter_Value]の[t_Insert_Index_Point]番目から、[T_Parameter_Value<tP_Insert...>]を挿入する
//
//補足
//[tP_Insert...]を可変長引数で受け取る場合は[U_Insert_Element_v]を利用する事
template<same_as_template_value<S_Parameter_Value> T_Parameter_Value, int t_Insert_Index_Point, same_as_template_value<S_Parameter_Value> TP_Insert>
using U_Insert_Element_P_v = typename IS_Parameter_Class_Change_Value<typename IS_Insert_Parameters<typename T_Parameter_Value::Parameter_Type, t_Insert_Index_Point, typename  TP_Insert::Parameter_Type>::Type>::Type;
