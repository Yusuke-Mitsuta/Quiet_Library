#pragma once

#include"Parameter_Remove.h"
#include"Parameter_Insert.h"

//Žd—l
//[T_Parameter]‚Ì[t_Change_Number_1]”Ô–Ú‚Ì—v‘f‚Æ[t_Change_Number_2]”Ô–Ú‚Ì—v‘f‚ð“ü‚ê‘Ö‚¦‚é
template<int t_Change_Number_1, int t_Change_Number_2, same_as_template_class<S_Parameter> T_Parameter>
struct IS_Change_Parameters
{
private:
	using Swap_v = U_Swap_v<t_Change_Number_1, t_Change_Number_2, (t_Change_Number_1 > t_Change_Number_2)>;

	using Remove =typename U_Remove_Element<T_Parameter, Swap_v::_1, Swap_v::_2>::Type;

	using Insert_min = typename U_Insert_Element<Remove, Swap_v::_1, U_Element_t<Swap_v::_2, T_Parameter>>::Type;

	using Insert_max = typename U_Insert_Element<Insert_min, Swap_v::_2, U_Element_t<Swap_v::_1, T_Parameter>>::Type;

public:

	using Type = Insert_max;
};

template<size_t t_Change_Number_1, size_t t_Change_Number_2, same_as_template_class<S_Parameter> T_Parameter>
using U_Change_Element = IS_Change_Parameters<t_Change_Number_1, t_Change_Number_2, T_Parameter>;

template<size_t t_Change_Number_1, size_t t_Change_Number_2, same_as_template_class<S_Parameter> T_Parameter>
using U_Change_Element_t = typename U_Change_Element<t_Change_Number_1, t_Change_Number_2, T_Parameter>::Type;

template<size_t t_Change_Number_1, size_t t_Change_Number_2, same_as_template_value<S_Parameter_Value> T_Parameter_Value>
using U_Change_Element_v = typename IS_Parameter_Class_Change_Value<
	typename U_Change_Element<t_Change_Number_1, t_Change_Number_2,typename T_Parameter_Value::Parameter_Type>::Type>::Type;