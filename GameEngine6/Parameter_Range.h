#pragma once

#include"Parameter_Get.h"

template<size_t _Index, int t_Start_Number>
struct IS_Index_Sequence;

//仕様
//[T_Parameters]の[t_Min_Number]番目から[t_Max_Number]番目までを抜き出す
template<same_as_template_class<S_Parameter> T_Parameters,int t_Min_Number,int t_Max_Number>
struct IS_Range_Parameters
{
	template<class TP_Range_Numbers>
	struct S_Range_Parameters;

	using Type = U_Get_Element_P_t<T_Parameters,typename IS_Index_Sequence<t_Max_Number - t_Min_Number, t_Min_Number>::Type>;

};

//仕様
//[T_Parameters]の[t_Min_Number]番目から[t_Max_Number]番目までを抜き出す
template<same_as_template_class<S_Parameter> T_Parameters, int t_Min_Number, int t_Max_Number>
using U_Range_Element_t = IS_Range_Parameters<T_Parameters, t_Min_Number, t_Max_Number>::Type;