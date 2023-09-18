#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{
	template<class T_Tuple_p>
	struct I_Remove_Pointer
	{
	private:

		template<class T_Tuple>
		struct S_Remove_Pointer
		{
			using Type = T_Tuple;
		};

		template<class ...T_Head_Types,class T,class ...T_Tail_Types>
		struct S_Remove_Pointer<Tuple_tp<_Head<T_Head_Types...>, T, _Tail< T_Tail_Types...>>>
		{
			using Type = Tuple_t<T_Head_Types..., T, T_Tail_Types...>;
		};

		template<class ...T_Head_Types,class ...T_Tail_Types>
		struct S_Remove_Pointer<Tuple_tp<_Head<T_Head_Types...>,std::nullopt_t, _Tail< T_Tail_Types...>>>
		{
			using Type = Tuple_t<T_Head_Types..., T_Tail_Types...>;
		};

		using Action = S_Tuple_Action<S_Remove_Pointer, T_Tuple_p>;

		friend struct Action;

	public:

		using Type = typename Action::Type;

	};

}
