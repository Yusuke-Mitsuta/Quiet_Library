#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{
	//édól
	//[T]Ç[tuple_tp,vp]Ç©ÇÁÅA[tuple_t,v]Ç…ïœä∑Ç∑ÇÈ
	template<class T_Tuple_p>
	struct I_Remove_Pointer
	{
	private:

		template<class T_Tuple>
		struct S_Remove_Pointer
		{
			using type = T_Tuple;
		};

		template<class ...T_Head_Types,class T,class ...T_Tail_Types>
		struct S_Remove_Pointer<tuple_tp<tuple_t<T_Head_Types...>, T, tuple_t< T_Tail_Types...>>>
		{
			using type = tuple_t<T_Head_Types..., T, T_Tail_Types...>;
		};

		template<class ...T_Head_Types,class ...T_Tail_Types>
		struct S_Remove_Pointer<tuple_tp<tuple_t<T_Head_Types...>,invalid_t, tuple_t< T_Tail_Types...>>>
		{
			using type = tuple_t<T_Head_Types..., T_Tail_Types...>;
		};

		template<auto ...t_head_value,auto t_value ,auto ...t_tail_value>
		struct S_Remove_Pointer<tuple_vp<tuple_v<t_head_value...>,t_value, tuple_v< t_tail_value...>>>
		{
			using type = tuple_v<t_head_value..., t_value, t_tail_value...>;
		};

		template<auto ...t_head_value, auto ...t_tail_value>
		struct S_Remove_Pointer<tuple_vp<tuple_v<t_head_value...>, invalid, tuple_v< t_tail_value...>>>
		{
			using type = tuple_v<t_head_value...,t_tail_value...>;
		};


	public:

		using type = S_Remove_Pointer<T_Tuple_p>::type;

	};

}
