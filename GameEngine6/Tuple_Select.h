#pragma once

#include"Tuple_Declare.h"
#include"Concept.h"

#include"SwapType.h"

namespace N_Tuple
{

	//仕様
	//[T_Tuple_t]の選択位置を[t_Point]に移動させる
	template<int t_Point, is_Element<t_Point> T_Tuple_t>
	struct Pointer
	{
	private:
		template<int t_Point, class T_Tuple_t>
		struct Pointer_Core
		{
			using Type = T_Tuple_t;
		};

		template<int t_Point, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires(t_Point > 0)
		struct Pointer_Core<t_Point, _t<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
		{
			using Type = Pointer_Core<t_Point - 1, typename _Next<_t<_Head< T_Head_Types...>, T, _Tail<T_Tail_Types...>>>::Type>::Type;
		};

		template<int t_Point, class T_Head_Flont_Type, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires(t_Point < 0)
		struct Pointer_Core<t_Point, _t<_Head<T_Head_Flont_Type, T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
		{
			using Type = Pointer_Core<t_Point + sizeof...(T_Head_Types) + 1, _t<_Head<>, T_Head_Flont_Type, _Tail<T_Head_Types..., T, T_Tail_Types...>>>::Type;
		};
	public:
		using Type = typename Pointer_Core<t_Point - S_Parameter<T_Tuple_t>::Size_Head, T_Tuple_t>::Type;
	};

	//仕様
	//[T_Tuple_t]の選択位置を[t_Point]に移動させる
	template<int t_Point, is_Element<t_Point> T_Tuple_t>
	using U_Pointer_t = Pointer<t_Point, T_Tuple_t>::Type;

}
