#pragma once
#include"Tuple_Declare.h"

namespace N_Tuple
{

	template<class T_Tuple>
	struct S_Size
	{
		static constexpr size_t head_size = 0;
		static constexpr size_t tail_size = 0;
	};

	template<class ...T_Types>
	struct S_Size<tuple_t<T_Types...>> :
		S_Size<invalid_t>
	{
		static constexpr size_t size = sizeof...(T_Types);
	};

	template< auto ...t_value>
	struct S_Size<tuple_v< t_value...>> :
		S_Size<invalid_t>
	{
		static constexpr size_t size = sizeof...(t_value);
	};

	template<class T_Head, class T, class T_Tail>
	struct S_Size<tuple_tp<T_Head, T, T_Tail>>
	{
		static constexpr size_t head_size = S_Size<T_Head>::size;
		static constexpr size_t tail_size = S_Size<T_Tail>::size;

		static constexpr size_t size = head_size + tail_size + is_invalid_not<T>;
	};

	template<class T_Head, auto t_value, class T_Tail>
	struct S_Size<tuple_vp<T_Head, t_value, T_Tail>>
	{
		static constexpr size_t head_size = S_Size<T_Head>::size;
		static constexpr size_t tail_size = S_Size<T_Tail>::size;

		static constexpr size_t size = head_size + tail_size + is_invalid_not<decltype(t_value)>;
	};

	//template<is_Tuple_v T_Tuple_v>
	//struct S_Size<T_Tuple_v> :
	//	S_Size<U_Tuple_v_To_t<T_Tuple_v>>
	//{};

};
