#pragma once

#include"Tuple_Declare.h"
#include"Concept.h"

#include"Outer_Change.h"
#include"SwapType.h"

namespace N_Tuple
{

	//仕様
	//[type]の選択位置を[t_Point]に移動させる
	template<int t_Point, class T_Tuple_t>
	struct I_Select
	{
	private:

		//仕様
		//目的ポイントまで距離[t_Point]が
		//	[+]であれば[type::Next],
		//	[-]であれば[type::Front]
		//	[0]であれば移動完了となる
		template<int t_Point, class T_Tuple_t>
		struct Select_Core
		{
			using type = T_Tuple_t;
		};

		template<int t_Point, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires(t_Point > 0)
		struct Select_Core<t_Point, tuple_tp<tuple_t<T_Head_Types...>, T, tuple_t<T_Tail_Types...>>>
		{
			using type = Select_Core<t_Point - 1,U_Next<tuple_tp<tuple_t< T_Head_Types...>, T, tuple_t<T_Tail_Types...>>>>::type;
		};

		template<int t_Point, class T_Head_Front_Type, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires(t_Point < 0)
		struct Select_Core<t_Point, tuple_tp<tuple_t<T_Head_Front_Type, T_Head_Types...>, T, tuple_t<T_Tail_Types...>>>
		{
			using type = Select_Core<t_Point + sizeof...(T_Head_Types) + 1, tuple_tp<tuple_t<>, T_Head_Front_Type, tuple_t<T_Head_Types..., T, T_Tail_Types...>>>::type;
		};


		template<class T_Tuple_t>
		using Pointer_Core_t = typename Select_Core<t_Point - static_cast<int>(S_Parameter<T_Tuple_t>::head_size), T_Tuple_t>::type;


		//仕様
		//目的ポイント[t_Point]が
		//	[0 <= t_Point <= t_Tuple_Size] かつ、
		//	[type::type]が[invalid_t]で無ければ探索に移行
		//		であれば[invalid_t]を除いて探索に移行
		// 
		//	[0 <= t_Point <= t_Tuple_Size] で無ければ、[invalid_t]による範囲外処理
		template<int t_Point, size_t t_Tuple_Size, class T_Tuple_t ,bool t_Out_Range = (t_Point < 0) || (t_Point >= t_Tuple_Size)>
		struct Select_Range_Judge
		{
			using type = Pointer_Core_t<T_Tuple_t>;
		};

		template<int t_Point, size_t t_Tuple_Size, class ...T_Head_Types , class ...T_Tail_Types>
		struct Select_Range_Judge<t_Point, t_Tuple_Size, tuple_tp<tuple_t<T_Head_Types...>,invalid_t, tuple_t<T_Tail_Types...>>,false>
		{
			using type = Pointer_Core_t<U_Create_p<tuple_t< T_Head_Types..., T_Tail_Types...>>>;
				
		};

		template<int t_Point, size_t t_Tuple_Size, class ...T_Head_Types, class T, class ...T_Tail_Types>
		struct Select_Range_Judge<t_Point,t_Tuple_Size, tuple_tp<tuple_t<T_Head_Types...>, T, tuple_t<T_Tail_Types...>>,true>
		{
			using Swap_Null = U_Swap_t1<tuple_t<T_Head_Types..., T_Tail_Types...>, tuple_t<T_Head_Types..., T, T_Tail_Types...>, is_invalid_not<T>>;

			using Swap_Head = U_Swap_t1<tuple_t<>,Swap_Null, (t_Point > 0) >;
			using Swap_Tail = U_Swap_t1< U_Change_Outer<tuple_t, Swap_Null>, tuple_t<>, (t_Point > 0)>;

			using type = tuple_tp<Swap_Head, invalid_t, Swap_Tail>;

		};

		template<class T_Tuple_t>
		struct S_Action
		{
			using type = typename Select_Range_Judge<t_Point, S_Parameter<T_Tuple_t>::size, T_Tuple_t>::type;
		};

	public:

		using type = S_Tuple_tp_Change_Action<S_Action, T_Tuple_t>::Return_p;

	};


}
