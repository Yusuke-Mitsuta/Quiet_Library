#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{
	template<class T_Tuple_p>
	struct I_Create_Pointer
	{
	private:

		template<class T_Tuple>
		struct S_Create_Pointer
		{
			using Type = Tuple_tp<Head_t<>, std::nullopt_t, Tail_t<>>;
		};

		template<class T_Flont_Type,class ...T_Types>
		struct S_Create_Pointer<Tuple_t<T_Flont_Type,T_Types...>>
		{
			using Type= Tuple_tp<Head_t<>,T_Flont_Type, Tail_t<T_Types...>>;
		};


		using Action = S_Tuple_Action<S_Create_Pointer, T_Tuple_p>;

		friend struct Action;

	public:

		using Type = typename Action::Type;

	};

}
