#pragma once
#include"Tuple_Declare.h"

namespace N_Tuple
{

	template<class T_Tuple>
	struct S_Size
	{
		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
		static constexpr size_t size = 0;
	};

	template<class T_Tuple>
		requires requires
	{
		requires S_ID_Select<T_Tuple>::ID == E_Tuple_ID::TUPLE_V ||
			 	 S_ID_Select<T_Tuple>::ID == E_Tuple_ID::TUPLE_VP;
	}
	struct S_Size<T_Tuple> :
		S_Size<U_Tuple_v_To_t<T_Tuple>>
	{};

	template<class T_Tuple>
		requires requires
	{
		requires S_ID_Select<T_Tuple>::ID == E_Tuple_ID::TUPLE_T;
	}
	struct S_Size<T_Tuple> :
		S_Size<U_Create_p<T_Tuple>>
	{};

	template<class ...T_Head, class T, class ...T_Tail>
	struct S_Size<tuple_tp<tuple_t<T_Head...>, T, tuple_t<T_Tail...>>>
	{
		static constexpr size_t head_size = sizeof...(T_Head);
		static constexpr size_t tail_size = sizeof...(T_Tail);

		static constexpr size_t size = head_size + tail_size + is_invalid_not<T>;
	};

};
