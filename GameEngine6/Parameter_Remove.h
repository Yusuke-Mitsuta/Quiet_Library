#pragma once

#include"Concept.h"
#include"Parameter_Element.h"

//仕様
//[S_Parameter]から[t_Remove_Indexs...]番目の要素を取り除く
// 
//テンプレート
//T_Parameter::要素を取り除くパラメータ
//t_Remove_Indexs...::取り除く要素の番号
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

	//仕様
	//[S_Remove_Parameters]のステート管理を行う
	//
	//Remove::[t_Remove_Indexs...]の番号に当てはまった時
	//Not_Remove::[t_Remove_Indexs...]の番号に当てはまらない時
	//End::全ての処理が終了した時
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

//仕様
//[S_Parameter_Value]から[t_Remove_Indexs...]を取り出し、[IS_Remove_Parameters]に送る
template<same_as_template_class<S_Parameter> T_Parameter, int ...t_Remove_Indexs>
struct S_Remove_Parameters_Helper<T_Parameter,S_Parameter_Value<t_Remove_Indexs...>>
{
	using Type= typename IS_Remove_Parameters<T_Parameter, t_Remove_Indexs...>::Type;
};

template<same_as_template_class<S_Parameter> T_Parameter, int ...t_Remove_Indexs>
using U_Remove_Element = IS_Remove_Parameters<T_Parameter, t_Remove_Indexs...>;

//仕様
//[S_Parameter]から[t_Remove_Indexs...]番目の要素を取り除く
// 
//テンプレート
//T_Parameter::要素を取り除くパラメータ
//t_Remove_Indexs...::取り除く要素の番号
//
//補足
//[t_Remove_Indexs...]を[S_Parameter_Value]で受け取る場合は[U_Remove_Element_P_t]を利用する事
template<same_as_template_class<S_Parameter> T_Parameter, int ...t_Remove_Indexs>
using U_Remove_Element_t = typename IS_Remove_Parameters<T_Parameter, t_Remove_Indexs...>::Type;

//仕様
//[S_Parameter]から[S_Parameter_Value< t_Remove_Indexs... >]番目の要素を取り除く
//
//テンプレート
//T_Parameter::要素を取り除くパラメータ
//T_Remove_Index::[S_Parameter_Value]にラッピングされた取り除く要素の番号
// 
//補足
//[t_Remove_Indexs...]を可変長引数で受け取る場合は[U_Remove_Element_t]を利用する事
template<same_as_template_class<S_Parameter> T_Parameter, same_as_template_value<S_Parameter_Value> T_Remove_Index>
using U_Remove_Element_P_t = typename S_Remove_Parameters_Helper<T_Parameter, T_Remove_Index>::Type;

//仕様
//[S_Parameter_Value]から[t_Remove_Indexs...]番目の要素を取り除く
// 
//テンプレート
//T_Parameter_Value::要素を取り除くパラメータ
//t_Remove_Indexs...::取り除く要素の番号
// 
//補足
//[t_Remove_Indexs...]を[S_Parameter_Value]で受け取る場合は[U_Remove_Element_P_v]を利用する事
template<same_as_template_value<S_Parameter_Value> T_Parameter_Value, int ...t_Remove_Indexs>
using U_Remove_Element_v = typename IS_Parameter_Class_Change_Value<typename IS_Remove_Parameters<typename T_Parameter_Value::Parameter_Type, t_Remove_Indexs...>::Type>::Type;

//仕様
//[S_Parameter_Value]から[S_Parameter_Value< t_Remove_Indexs... >]番目の要素を取り除く
//
//テンプレート
//T_Parameter_Value::要素を取り除くパラメータ
//T_Remove_Index::[S_Parameter_Value]にラッピングされた取り除く要素の番号
// 
//補足
//[t_Remove_Indexs...]を可変長引数で受け取る場合は[U_Remove_Element_P_v]を利用する事
template<same_as_template_value<S_Parameter_Value> T_Parameter_Value, same_as_template_value<S_Parameter_Value> T_Remove_Index>
using U_Remove_Element_P_v = typename IS_Parameter_Class_Change_Value<typename S_Remove_Parameters_Helper<typename T_Parameter_Value::Parameter_Type, T_Remove_Index>::Type>::Type;
