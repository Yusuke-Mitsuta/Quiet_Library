#pragma once

#include"Concept.h"

//#include"Tuple_Value.h"

namespace N_Tuple
{
	template<class ...T_Types>
	struct S_Parameter;

	template<class ...T_Head_Type>
	struct Head_t;

	template<auto ...t_Head_Value>
	struct Head_v;

	template<class ...T_Tail_Types>
	struct Tail_t;

	template<auto ...t_Tail_Value>
	struct Tail_v;

	template<class ...T_Types>
	struct Tuple_t;

	template<same_as_template_type<Head_t> T_Head, class T, same_as_template_type<Tail_t> T_Tail>
	struct Tuple_tp;

	template<auto ..._Value>
	struct Tuple_v;

	template<same_as_template_value<Head_v> T_Head, auto _value, same_as_template_value<Tail_v> T_Tail>
	struct Tuple_vp;



	template<class T_Tuple, int t_Number>
	concept is_Element_Head = is_Element<typename S_Parameter<T_Tuple>::Head, t_Number>;

	template<class T_Tuple, int t_Number>
	concept is_Element_Tail = is_Element<typename S_Parameter<T_Tuple>::Tial, t_Number>;

	template<class T>
	struct S_same_as_Tuple_vp :
		std::false_type {};

	template<same_as_template_value<Head_v> T_Head_v, auto value, same_as_template_value<Tail_v> T_Tail_v>
	struct S_same_as_Tuple_vp<Tuple_vp<T_Head_v, value, T_Tail_v>> :
		std::true_type {};


	template<class T>
	concept same_as_Tuple_vp = S_same_as_Tuple_vp<T>::value;

	template<class T_Tuple_p>
	concept is_Tuple_p = same_as_Tuple_vp<T_Tuple_p> || same_as_template_type<T_Tuple_p, Tuple_tp>;

	template<class T_Tuple>
	concept is_Tuple_not_p = same_as_template_type<T_Tuple, Tuple_t> || same_as_template_value<T_Tuple, Tuple_v>;

	template<class T_Tuple_v>
	concept is_Tuple_v = same_as_Tuple_vp<T_Tuple_v> || same_as_template_value<T_Tuple_v, Tuple_v>;

	template<class T_Tuple_t>
	concept is_Tuple_t = same_as_template_type<T_Tuple_t,Tuple_t> || same_as_template_type<T_Tuple_t, Tuple_t>;

	

	//template<class T_Head_t>
	//concept is_Head_t = same_as_template_type<T_Head_t, Head_t>;

	//template<class T_Head_v>
	//concept is_Head_v = same_as_template_value<T_Head_v, Head_v>;

	//template<class T_Tail_t>
	//concept is_Tail_t = same_as_template_type<T_Tail_t,Tail_t>;

	//template<class T_Tail_v>
	//concept is_Tail_v = same_as_template_value<T_Tail_v, Tail_v>;

}