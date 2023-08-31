#pragma once

#include<type_traits>

template<class ...T_Parameters>
struct S_Parameter;

template<auto t_Value>
struct integral_constant
{
	using value_type = decltype(t_Value);
	static constexpr auto value = t_Value;

};

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