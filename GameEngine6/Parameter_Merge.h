#pragma once

template<class ...T_Parameters>
struct IS_Parameter_Merge
{
	template<class T_Result, class T_Flont_Parameter,class ...TP_Parameters>
	struct S_Parameter_Merge
	{
		using Type = T_Result;
	};

	template<class ...TP_Result, class T_Flont_Parameter, class ...TP_Parameters>
	struct S_Parameter_Merge<S_Parameter<TP_Result...>,T_Flont_Parameter,TP_Parameters...>
	{
		using Type = S_Parameter_Merge<S_Parameter<TP_Result...,T_Flont_Parameter>, TP_Parameters...>::Type;
	};

	template<class ...TP_Result, class ...TP_Flont_Inner_Parameters, class ...TP_Parameters>
	struct S_Parameter_Merge<S_Parameter<TP_Result...>, S_Parameter<TP_Flont_Inner_Parameters...>, TP_Parameters...>
	{
		using Type= S_Parameter_Merge<S_Parameter<TP_Result..., TP_Flont_Inner_Parameters...>, TP_Parameters...>::Type;
	};

	using Type = S_Parameter_Merge<S_Parameter<>, T_Parameters...>::Type;

};

template<class ...T_Parameters>
using U_Merge_Element_t = typename IS_Parameter_Merge<T_Parameters...>::Type;
