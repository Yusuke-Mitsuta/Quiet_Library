#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{
	template<class T_Tuple_t>
	struct _Next
	{
		using Type = std::nullopt_t;
	};

	//仕様
	//[Tuple_t]の選択位置をひとつ進める
	template<class ...T_Head_Types, class T, class T_Next_Type, class ...T_Tail_Types>
	struct _Next<_t<_Head<T_Head_Types...>, T, _Tail<T_Next_Type, T_Tail_Types...>>>
	{
		using Type = _t<_Head<T_Head_Types..., T>, T_Next_Type, _Tail<T_Tail_Types...>>;
	};


}