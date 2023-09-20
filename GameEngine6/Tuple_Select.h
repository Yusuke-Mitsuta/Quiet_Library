#pragma once

#include"Tuple_Declare.h"
#include"Concept.h"

#include"Outer_Change.h"
#include"SwapType.h"

namespace N_Tuple
{

	//仕様
	//[Type]の選択位置を[t_Point]に移動させる
	template<int t_Point, class T_Tuple_t>
	struct I_Select
	{
	private:

		//仕様
		//目的ポイントまで距離[t_Point]が
		//	[+]であれば[Type::Next],
		//	[-]であれば[Type::Flont]
		//	[0]であれば移動完了となる
		template<int t_Point, class T_Tuple_t>
		struct Select_Core
		{
			using Type = T_Tuple_t;
		};

		template<int t_Point, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires(t_Point > 0)
		struct Select_Core<t_Point, Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<T_Tail_Types...>>>
		{
			using Type = Select_Core<t_Point - 1, typename I_Next<Tuple_tp<Head_t< T_Head_Types...>, T, Tail_t<T_Tail_Types...>>>::Type>::Type;
		};

		template<int t_Point, class T_Head_Flont_Type, class ...T_Head_Types, class T, class ...T_Tail_Types>
			requires(t_Point < 0)
		struct Select_Core<t_Point, Tuple_tp<Head_t<T_Head_Flont_Type, T_Head_Types...>, T, Tail_t<T_Tail_Types...>>>
		{
			using Type = Select_Core<t_Point + sizeof...(T_Head_Types) + 1, Tuple_tp<Head_t<>, T_Head_Flont_Type, Tail_t<T_Head_Types..., T, T_Tail_Types...>>>::Type;
		};


		template<class T_Tuple_t>
		using Pointer_Core_t = typename Select_Core<t_Point - static_cast<int>(S_Parameter<T_Tuple_t>::Size_Head), T_Tuple_t>::Type;


		//仕様
		//目的ポイント[t_Point]が
		//	[0 <= t_Point <= t_Tuple_Size] かつ、
		//	[Type::Type]が[std::nullopt_t]で無ければ探索に移行
		//		であれば[std::nullopt_t]を除いて探索に移行
		// 
		//	[0 <= t_Point <= t_Tuple_Size] で無ければ、[std::nullopt_t]による範囲外処理
		template<int t_Point, size_t t_Tuple_Size, class T_Tuple_t ,bool t_Out_Range = (t_Point < 0) || (t_Point >= t_Tuple_Size)>
		struct Select_Range_Judge
		{
			using Type = Pointer_Core_t<T_Tuple_t>;
		};

		template<int t_Point, size_t t_Tuple_Size, class ...T_Head_Types , class ...T_Tail_Types>
		struct Select_Range_Judge<t_Point, t_Tuple_Size, Tuple_tp<Head_t<T_Head_Types...>,std::nullopt_t, Tail_t<T_Tail_Types...>>,false>
		{
			using Type = Pointer_Core_t<typename I_Create_Pointer<Tuple_t< T_Head_Types..., T_Tail_Types...>>::Type>;
				
		};

		template<int t_Point, size_t t_Tuple_Size, class ...T_Head_Types, class T, class ...T_Tail_Types>
		struct Select_Range_Judge<t_Point,t_Tuple_Size, Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<T_Tail_Types...>>,true>
		{
			using Swap_Null = U_Swap_t1<Head_t<T_Head_Types..., T_Tail_Types...>, Head_t<T_Head_Types..., T, T_Tail_Types...>, not_is_nullopt<T>>;

			using Swap_Head = U_Swap_t1<Head_t<>,Swap_Null, (t_Point > 0) >;
			using Swap_Tail = U_Swap_t1< U_Change_Outer<Tail_t, Swap_Null>, Tail_t<>, (t_Point > 0)>;

			using Type = Tuple_tp<Swap_Head, std::nullopt_t, Swap_Tail>;

		};

		template<class T_Tuple_t>
		struct S_Action
		{
			using Type = typename Select_Range_Judge<t_Point, S_Parameter<T_Tuple_t>::Size, T_Tuple_t>::Type;
		};

		template<>
		struct S_Action<Tuple_tp<Head_t<>,std::nullopt_t,Tail_t<>>>
		{
			using Type = Tuple_tp<Head_t<>, std::nullopt_t, Tail_t<>>;

		};

		using Action= S_Tuple_Action<S_Action, T_Tuple_t>;

		friend struct Action;

	public:

		using Type = typename Action::Type;

	};

	//仕様
	//[Type]の選択位置を[t_Point]に移動させる
	template<int t_Point, is_Element<t_Point> T_Tuple_t>
	using U_Select_t = I_Select<t_Point, T_Tuple_t>::Type;


}
