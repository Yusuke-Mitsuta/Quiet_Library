#pragma once

#include"Tuple_Declare.h"
#include"Concept.h"
#include"Tuple_Head.h"

#include"SwapType.h"

namespace N_Tuple
{

	using N = int;

	template<N t_Point,class T_Tuple_t>
	struct I_Pointer
	{

		template<N t_Point, class T_Tuple_t>
		struct _Pointer;

		template<class ...T_Head_Types, class T, class ...T_Tail_Types>
		struct _Pointer<0, N_Tuple::_t<_Head< T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
		{
			using Type = _t<_Head< T_Head_Types...>, T, _Tail<T_Tail_Types...>>;
		};

		template<N t_Point, class ...T_Head_Types, class T, class ...T_Tail_Types>
			//requires(t_Point > 0)
		struct _Pointer<t_Point, N_Tuple::_t<_Head< T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
		{
			using Type = _Pointer<t_Point-1, typename _Next<_t<_Head< T_Head_Types...>, T, _Tail<T_Tail_Types...>>>::Type>::Type;
		};

		template<N t_Point, class T_Head_Flont_Type, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires(t_Point < 0)
		struct _Pointer<t_Point, N_Tuple::_t<_Head<T_Head_Flont_Type, T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
		{
			using Type = _Pointer<t_Point+ sizeof...(T_Head_Types)+1 , _t<_Head<>, T_Head_Flont_Type, _Tail<T_Head_Types..., T, T_Tail_Types...>>>::Type;
		};


		using Type = typename _Pointer<t_Point - T_Tuple_t::Size_Head,T_Tuple_t>::Type;

	};




}
