#pragma once

#include"Tuple_Class_Declare.h"




namespace N_Tuple
{

	template<class T_Tuple_t, template<class...>class T_Action>
	struct S_Tuple_Action
	{
		using Type = typename T_Action<T_Tuple_t>::Type;
	};

	template<class T_Head_v, auto value, class T_Tail_v, template<class...>class T_Action>
	struct S_Tuple_Action<Tuple_vp<T_Head_v,
		value, T_Tail_v>,T_Action>
	{
		using Change_tp = typename Tuple_vp_To_tp< Tuple_vp<T_Head_v, value, T_Tail_v>>::Type;
		using Action = typename T_Action<Change_tp>::Type;
		using Change_vp = typename Tuple_tp_To_vp<Action>::Type;
		using Type = Change_vp;
	};

}