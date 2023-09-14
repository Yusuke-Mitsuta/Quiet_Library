#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	//仕様
	//[Tuple_t]の選択位置をひとつ前にする
	template<class T_Tuple_t>
	struct _Prev;

	template<class T, class ...T_Tail_Types>
	struct _Prev<_t<_Head<>, T, _Tail<T_Tail_Types...>>>
	{
		using Type = std::nullopt_t;
	};

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
	struct _Prev<_t<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
	{
		using Type = typename Pointer<sizeof...(T_Head_Types) - 1, _t<_Head< T_Head_Types...>, T, _Tail<T_Tail_Types...>>>::Type;
	};

}