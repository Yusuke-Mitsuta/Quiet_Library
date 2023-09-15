#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	template<class T_Tuple_t>
	struct _Next
	{
		using Type = T_Tuple_t;
	};

	//仕様
	//[Tuple_t]の選択位置をひとつ進める
	template<class ...T_Head_Types, class T, class T_Next_Type, class ...T_Tail_Types>
	struct _Next<_p<_Head<T_Head_Types...>, T, _Tail<T_Next_Type, T_Tail_Types...>>>
	{
		using Type = _p<_Head<T_Head_Types..., T>, T_Next_Type, _Tail<T_Tail_Types...>>;
	};

	template<class ...T_Head_Types,not_is_nullopt T>
	struct _Next<_p<_Head<T_Head_Types...>, T, _Tail<>>>
	{
		using Type = _p<_Head<T_Head_Types..., T>, std::nullopt_t, _Tail<>>;
	};

	template< class T_Next_Type, class ...T_Tail_Types>
	struct _Next<_p<_Head<>, std::nullopt_t, _Tail<T_Next_Type, T_Tail_Types...>>>
	{
		using Type = _p<_Head<>, T_Next_Type, _Tail< T_Tail_Types...>>;
	};

}