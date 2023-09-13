#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	template<class T_Tuple_t>
	struct _Remove;

	template<class ...T_Head_Types, class T>
	struct _Remove<_t<_Head<T_Head_Types...>, T, _Tail<>>>
	{
		using Type = typename I_Pointer<
			static_cast<int>(sizeof...(T_Head_Types)) - 1,
			_t<_Head<T_Head_Types...>, T, _Tail<>>>::Type;


	};

	template<class ...T_Head_Types, class T, class T_Next_Type, class ...T_Tail_Types>
	struct _Remove<_t<_Head<T_Head_Types...>, T, _Tail<T_Next_Type, T_Tail_Types...>>>
	{
		using Type = _t<_Head<T_Head_Types...>, T_Next_Type, _Tail<T_Tail_Types...>>::Type;
	};

}
