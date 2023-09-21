#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	template<class T_Tuple_p,class T_Change>
	struct I_Change
	{
	private:

		template<class T_Tuple_p, class T_Change>
		struct S_Change
		{
			using Type = T_Tuple_p;
		};

		template<class T_Head,not_is_nullopt T,class T_Tail, class T_Change>
		struct S_Change<Tuple_tp<T_Head,T,T_Tail>,T_Change>
		{
			using Type = Tuple_tp<T_Head, T_Change, T_Tail>;
		};

	public:

		using Type = typename S_Action_Tuple_tp<S_Change, T_Tuple_p>::type;

	};

}