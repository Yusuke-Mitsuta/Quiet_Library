#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	//仕様
	//[Tuple_t]の選択位置をひとつ前にする
	template<class T_Tuple_t>
	struct _Prev
	{
		using Type = T_Tuple_t;
	};

	template<class ...T_Tail_Types>
	struct _Prev<_p<_Head<>,std::nullopt_t, _Tail<T_Tail_Types...>>>
	{
		using Type = _p<_Head<>, std::nullopt_t, _Tail<T_Tail_Types...>>;
	};

	template<class ...T_Head_Types, class T, class ...T_Tail_Types>
		requires (sizeof...(T_Head_Types)!=0 || not_is_nullopt<T>)
	struct _Prev<_p<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
	{
		using Type = typename Pointer<sizeof...(T_Head_Types) - 1, _p<_Head< T_Head_Types...>, T, _Tail<T_Tail_Types...>>>::Type;
	};
	
}