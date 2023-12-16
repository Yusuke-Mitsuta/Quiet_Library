#pragma once

#include"Concept.h"
#include"Tuple_ID.h"

namespace N_Tuple
{
	template<class ...T_Types>
	struct S_Parameter;


	template<class T_Tuple>
	concept same_as_tuple_t = (S_Parameter<T_Tuple>::ID == E_Tuple_ID::TUPLE_T);

	template<class T_Tuple>
	concept same_as_tuple_tp = (S_Parameter<T_Tuple>::ID == E_Tuple_ID::TUPLE_TP);

	template<class T_Tuple>
	concept same_as_tuple_v = (S_Parameter<T_Tuple>::ID == E_Tuple_ID::TUPLE_V);

	template<class T_Tuple>
	concept same_as_tuple_vp = (S_Parameter<T_Tuple>::ID == E_Tuple_ID::TUPLE_VP);


	
	template<class T_Tuple_p>
	concept is_Tuple_p = same_as_tuple_tp<T_Tuple_p> || same_as_tuple_vp<T_Tuple_p>;

	template<class T_Tuple>
	concept is_Tuple_not_p = same_as_tuple_t<T_Tuple> || same_as_tuple_v<T_Tuple>;

	template<class T_Tuple_v>
	concept is_Tuple_v = same_as_tuple_v<T_Tuple_v> || same_as_tuple_vp<T_Tuple_v>;

	template<class T_Tuple_t>
	concept is_Tuple_t = same_as_tuple_t<T_Tuple_t> || same_as_tuple_tp<T_Tuple_t>;

	template<class T_Tuple>
	concept is_Tuple = is_Tuple_t<T_Tuple> || is_Tuple_v<T_Tuple>;

}
