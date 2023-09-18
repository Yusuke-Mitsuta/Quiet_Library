#pragma once

#include"Tuple_Class_Declare.h"
#include"SwapType.h"

namespace N_Tuple
{
	//仕様
	//[T_Base_Tuple]の選択中の箇所に[T_Insert_Tuple]の要素を追加する
	template<class T_Base_Tuple, class T_Insert_Tuple>
	struct I_Insert
	{
	private:

		using Insert_Tuple = typename Tuple_v_To_t<typename I_Remove_Pointer<T_Insert_Tuple>::Type>::Type;

		template<class T_Base_Tuple, class T_Insert_Tuple = Insert_Tuple>
		struct S_Insert
		{
			using Type = T_Base_Tuple;
		};

		template<class T_Base_Head,class T_Base,class ...T_Base_Tail_Types,class T_Insert_Flont_Type,class ...T_Insert_Types>
		struct S_Insert<Tuple_tp<T_Base_Head,T_Base,_Tail<T_Base_Tail_Types...>>,
			Tuple_t<T_Insert_Flont_Type,T_Insert_Types...>>
		{
			using Type = Tuple_tp<T_Base_Head, T_Insert_Flont_Type,
				_Tail<T_Insert_Types..., T_Base, T_Base_Tail_Types...>>;
		};

		template<class T_Base_Head, class ...T_Base_Tail_Types, class T_Insert_Flont_Type, class ...T_Insert_Types>
		struct S_Insert<Tuple_tp<T_Base_Head,std::nullopt_t, _Tail<T_Base_Tail_Types...>>,
			Tuple_t<T_Insert_Flont_Type, T_Insert_Types...>>
		{
			static constexpr bool is_tail_Empty = !static_cast<bool>(sizeof...(T_Base_Tail_Types));

			using Tail = U_Swap_t1<_Tail<T_Insert_Flont_Type, T_Insert_Types..., T_Base_Tail_Types...>,
				_Tail<T_Insert_Types...>, is_tail_Empty>;

			using SelectPoint = U_Swap_t1<std::nullopt_t, T_Insert_Flont_Type,is_tail_Empty>;

			using Type = Tuple_tp<T_Base_Head, SelectPoint, Tail>;
		};

		using Action = S_Tuple_Action<S_Insert, T_Base_Tuple>;

		friend struct Action;

	public:

		using Type = typename Action::Type;


	};
}
