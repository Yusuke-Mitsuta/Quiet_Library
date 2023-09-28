#pragma once

#include"Tuple_Class_Declare.h"
#include"SwapType.h"

namespace N_Tuple
{
	//仕様
	//[T_Base_Tuple]の選択中の箇所に[T_Insert_Tuple]の要素を追加する
	template<class T_Base_Tuple, class T_Insert_Tuple, size_t t_Insert_Point>
	struct I_Insert
	{
	private:

		using Insert_Tuple = U_Tuple_v_To_t<U_Remove_p<T_Insert_Tuple>>;

		template<class T_Base_Tuple, class T_Insert_Tuple = Insert_Tuple>
		struct S_Insert
		{
			using type = T_Base_Tuple;
		};

		template<class T_Base_Head,class T_Base,class ...T_Base_Tail_Types,class T_Insert_Flont_Type,class ...T_Insert_Types>
		struct S_Insert<Tuple_tp<T_Base_Head,T_Base,Tail_t<T_Base_Tail_Types...>>,
			Tuple_t<T_Insert_Flont_Type,T_Insert_Types...>>
		{
			using type = Tuple_tp<T_Base_Head, T_Insert_Flont_Type,
				Tail_t<T_Insert_Types..., T_Base, T_Base_Tail_Types...>>;
		};

		template<class T_Base_Head, class ...T_Base_Tail_Types, class T_Insert_Flont_Type, class ...T_Insert_Types>
		struct S_Insert<Tuple_tp<T_Base_Head,std::nullopt_t, Tail_t<T_Base_Tail_Types...>>,
			Tuple_t<T_Insert_Flont_Type, T_Insert_Types...>>
		{
			static constexpr bool is_tail_Empty = !static_cast<bool>(sizeof...(T_Base_Tail_Types));

			using Tail = U_Swap_t1<Tail_t<T_Insert_Flont_Type, T_Insert_Types..., T_Base_Tail_Types...>,
				Tail_t<T_Insert_Types...>, is_tail_Empty>;

			using SelectPoint = U_Swap_t1<std::nullopt_t, T_Insert_Flont_Type,is_tail_Empty>;

			using type = Tuple_tp<T_Base_Head, SelectPoint, Tail>;
		};

	public:

		using type = S_Action_Tuple_tp<S_Insert, T_Base_Tuple, t_Insert_Point>::type;


	};
}
