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

		using Action = S_Tuple_Action<S_Change, T_Tuple_p>;

		friend struct Action;

	public:

		using Type = typename Action::Type;

	};

}