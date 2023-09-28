#pragma once

#include"Concept.h"


template<class ...T_Types>
struct tuple_t;

template<same_as_template_type<tuple_t> T_Head, class T, same_as_template_type<tuple_t> T_Tail>
struct tuple_tp;

template<auto ..._Value>
struct tuple_v;

template<same_as_template_value<tuple_v> T_Head, auto _value, same_as_template_value<tuple_v> T_Tail>
struct tuple_vp;

namespace N_Tuple
{
	template<class ...T_Types>
	struct S_Parameter;

	template<class T_Tuple, int t_Number>
	concept is_Element_Head = is_Element<typename S_Parameter<T_Tuple>::Head, t_Number>;

	template<class T_Tuple, int t_Number>
	concept is_Element_Tail = is_Element<typename S_Parameter<T_Tuple>::Tial, t_Number>;

	template<class T>
	struct S_same_as_Tuple_vp :
		std::false_type {};

	template<same_as_template_value<tuple_v> T_Head_v, auto value, same_as_template_value<tuple_v> T_Tail_v>
	struct S_same_as_Tuple_vp<tuple_vp<T_Head_v, value, T_Tail_v>> :
		std::true_type {};


	template<class T>
	concept same_as_Tuple_vp = S_same_as_Tuple_vp<T>::value;

	template<class T_Tuple_p>
	concept is_Tuple_p = same_as_Tuple_vp<T_Tuple_p> || same_as_template_type<T_Tuple_p, tuple_tp>;

	template<class T_Tuple>
	concept is_Tuple_not_p = same_as_template_type<T_Tuple, tuple_t> || same_as_template_value<T_Tuple, tuple_v>;

	template<class T_Tuple_v>
	concept is_Tuple_v = same_as_Tuple_vp<T_Tuple_v> || same_as_template_value<T_Tuple_v, tuple_v>;

	template<class T_Tuple_t>
	concept is_Tuple_t = same_as_template_type<T_Tuple_t,tuple_tp> || same_as_template_type<T_Tuple_t, tuple_t>;

	template<class T_Tuple>
	concept is_Tuple = is_Tuple_t<T_Tuple> || is_Tuple_v<T_Tuple>;

}