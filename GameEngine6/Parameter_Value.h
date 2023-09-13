#pragma once

#include<type_traits>
#include"Parameter_Value_Index_Sequence.h"
#include"Tuple_Value.h"

template<class ...T_Parameters>
struct S_Parameter;

//仕様
//パラメータパック[t_Parameters...]をラッピングする
//
//template
//t_Parameters...::非型のパラメータパック
template<auto ...t_Parameters>
struct S_Parameter_Value
{

	template<class T_Result_Parameter = S_Parameter<>,class T_Rest_Parameter = S_Parameter< integral_constant<t_Parameters>...>>
	struct S_Inner_Parameter_Value_Search;

	template<class ...TP_Migrated_Parameter, class TP_Rest_Flnot_Parameter, class ...TP_Rest_Parameter>
	struct S_Inner_Parameter_Value_Search<
		S_Parameter<TP_Migrated_Parameter...>,
		S_Parameter<TP_Rest_Flnot_Parameter, TP_Rest_Parameter...>>
	{
		template<class T>
		struct S_Parameter_Value_Deployment
		{
			using Type = S_Inner_Parameter_Value_Search<S_Parameter<TP_Migrated_Parameter..., TP_Rest_Flnot_Parameter>, S_Parameter<TP_Rest_Parameter...>>::Type;
		};

		template<auto ...v>
		struct S_Parameter_Value_Deployment<S_Parameter_Value<v...>>
		{
			using Type = S_Inner_Parameter_Value_Search<S_Parameter<TP_Migrated_Parameter...>, S_Parameter<integral_constant<v>...,TP_Rest_Parameter...>>::Type;
		};
		using Type = S_Parameter_Value_Deployment<std::remove_const_t<typename TP_Rest_Flnot_Parameter::value_type>>::Type;
	};

	template<class ...TP_Migrated_Parameter>
	struct S_Inner_Parameter_Value_Search<S_Parameter<TP_Migrated_Parameter...>, S_Parameter<>>
	{
		using Type = S_Parameter<TP_Migrated_Parameter...>;
	};

	constexpr S_Parameter_Value() {}

	//仕様
	//[S_Parameter< integral_constant< t_Parameters >...>]の形に変形する
	using Parameter_Type =S_Inner_Parameter_Value_Search<>::Type;

	static constexpr size_t Size = Parameter_Type::Size;
};

template<>
struct S_Parameter_Value<>
{
	using Parameter_Type = S_Parameter<>;

	static constexpr size_t Size = 0;
};

template<class T_Parameter>
struct IS_Parameter_Class_Change_Value;

template<auto ...t_Parameters>
struct IS_Parameter_Class_Change_Value<S_Parameter<integral_constant<t_Parameters>...>>
{
	using Type = S_Parameter_Value<t_Parameters...>;
};