#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{	
	//仕様
	//[tuple_t]の選択位置をひとつ進める
	template<class T_Tuple_t>
	struct I_Next
	{
	private:

		template<class T_Tuple_t>
		struct S_Next
		{
			using type = T_Tuple_t;
		};

		//仕様
		//[tuple_t]の選択位置をひとつ進める
		template<class ...T_Head_Types, class T, class T_Next_Type, class ...T_Tail_Types>
		struct S_Next<tuple_tp<tuple_t<T_Head_Types...>, T, tuple_t<T_Next_Type, T_Tail_Types...>>>
		{
			using type = tuple_tp<tuple_t<T_Head_Types..., T>, T_Next_Type, tuple_t<T_Tail_Types...>>;
		};

		template<class ...T_Head_Types, is_invalid_not T>
		struct S_Next<tuple_tp<tuple_t<T_Head_Types...>, T, tuple_t<>>>
		{
			using type = tuple_tp<tuple_t<T_Head_Types..., T>, invalid_t, tuple_t<>>;
		};

		template< class T_Next_Type, class ...T_Tail_Types>
		struct S_Next<tuple_tp<tuple_t<>, invalid_t, tuple_t<T_Next_Type, T_Tail_Types...>>>
		{
			using type = tuple_tp<tuple_t<>, T_Next_Type, tuple_t< T_Tail_Types...>>;
		};

	public:

		using type = S_Tuple_tp_Change_Action<S_Next, T_Tuple_t>::Return_p;

	};


}