#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	template<class T_Tuple_t>
	struct _Prev;

	template< class T,class ...T_Tail_Types>
	struct _Prev<_t<_Head<>, T, _Tail<T_Tail_Types...>>>
	{
		using Type = std::nullopt_t;
	};


	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct _Prev<_t<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
	{
		using Type = typename I_Pointer<sizeof...(T_Head_Types) - 1, _t<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>>::Type;





	};

}