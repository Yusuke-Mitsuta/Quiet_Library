#pragma once

#include"SwapType.h"

template<size_t _Index, class T_FlontParameter, class ...T_Parameters>
struct S_Parameter_Element_Type
{
	using Type = IS_Swap_t1<T_FlontParameter, typename S_Parameter_Element_Type<_Index - 1, T_Parameters...>::Type, _Index>;
};

template<size_t _Index, class ...T_Parameters>
using S_Parameter_Element_t = S_Parameter_Element_Type<_Index, T_Parameters...>::Type;


template<size_t _Index, auto t_FlontParameter, auto ...t_Parameters>
struct S_Parameter_Element_Variable
{
private:
	template<auto t_Variable>
	struct S_Variable
	{
		Constant Variable = t_Variable;
	};
public:

	using Type = IS_Swap_t1<S_Variable<t_FlontParameter>, typename S_Parameter_Element_Variable<_Index - 1, t_Parameters...>::Type, _Index>;

	Constant Variable = Type::Variable;
};

template<size_t _Index, auto ...t_Parameters>
using S_Parameter_Element_v = S_Parameter_Element_Variable<_Index, t_Parameters...>::Variable;


