#pragma once

#include"Tuple_Declare.h"
#include"Concept.h"

#include"Outer_Change.h"
#include"SwapType.h"

namespace N_Tuple
{

	//仕様
	//[T_Tuple_t]の選択位置を[t_Point]に移動させる
	template<int t_Point, class T_Tuple_t>
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
		struct Pointer_Core<t_Point, _p<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
		{
			using Type = Pointer_Core<t_Point - 1, typename _Next<_p<_Head< T_Head_Types...>, T, _Tail<T_Tail_Types...>>>::Type>::Type;
		};

		template<int t_Point, class T_Head_Flont_Type, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires(t_Point < 0)
		struct Pointer_Core<t_Point, _p<_Head<T_Head_Flont_Type, T_Head_Types...>, T, _Tail<T_Tail_Types...>>>
		{
			using Type = Pointer_Core<t_Point + sizeof...(T_Head_Types) + 1, _p<_Head<>, T_Head_Flont_Type, _Tail<T_Head_Types..., T, T_Tail_Types...>>>::Type;
		};


		template<class T_Tuple_t>
		//using Pointer_Core_t = typename Pointer_Core<(t_Point - 1) - S_Parameter<T_Tuple_t>::Size_Head, T_Tuple_t>::Type;
		using Pointer_Core_t = typename Pointer_Core<t_Point - S_Parameter<T_Tuple_t>::Size_Head, T_Tuple_t>::Type;

		//using Pointer_Core_t = typename Pointer_Core<1, T_Tuple_t>::Type;


		template<int t_Point, size_t t_Tuple_Size, class T_Tuple_t ,bool t_Out_Range = (t_Point < 0) || (t_Point >= t_Tuple_Size)>
		struct Pointer_Range_Judge
		{
			using Type = Pointer_Core_t<T_Tuple_t>;
		};

		template<int t_Point, size_t t_Tuple_Size, class ...T_Head_Types , class ...T_Tail_Types>
		struct Pointer_Range_Judge<t_Point, t_Tuple_Size, _p<_Head<T_Head_Types...>,std::nullopt_t, _Tail<T_Tail_Types...>>,false>
		{
			using Type = Pointer_Core_t<
				typename _Create_Tuple_Pointer< T_Head_Types..., T_Tail_Types...>::Type>;
		};

		template<int t_Point, size_t t_Tuple_Size, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires (t_Point < 0)
		struct Pointer_Range_Judge<t_Point,t_Tuple_Size, _p<_Head<T_Head_Types...>, T, _Tail<T_Tail_Types...>>,true>
		{
			using Swap_Null = U_Swap_t1<_Head<T_Head_Types..., T_Tail_Types...>, _Head<T_Head_Types..., T, T_Tail_Types...>, not_is_nullopt<T>>;

			using Swap_Head = U_Swap_t1<_Head<>,Swap_Null, (t_Point > 0) >;
			using Swap_Tail = U_Swap_t1< U_Change_Outer<_Tail, Swap_Null>, _Tail<>, (t_Point > 0)>;

			using Type = _p<Swap_Head, std::nullopt_t, Swap_Tail>;

		};

	public:

		using Type = typename Pointer_Range_Judge<t_Point, S_Parameter<T_Tuple_t>::Size, T_Tuple_t>::Type;
	};

	//仕様
	//[T_Tuple_t]の選択位置を[t_Point]に移動させる
	template<int t_Point, is_Element<t_Point> T_Tuple_t>
	using U_Pointer_t = Pointer<t_Point, T_Tuple_t>::Type;


}
