#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{	
	//仕様
	//[Tuple_t]の選択位置をひとつ進める
	template<class T_Tuple_t>
	struct I_Next
	{
	private:

		template<class T_Tuple_t>
		struct S_Next
		{
			using type = T_Tuple_t;
		};

		//仕様
		//[Tuple_t]の選択位置をひとつ進める
		template<class ...T_Head_Types, class T, class T_Next_Type, class ...T_Tail_Types>
		struct S_Next<Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<T_Next_Type, T_Tail_Types...>>>
		{
			using type = Tuple_tp<Head_t<T_Head_Types..., T>, T_Next_Type, Tail_t<T_Tail_Types...>>;
		};

		template<class ...T_Head_Types, not_is_nullopt T>
		struct S_Next<Tuple_tp<Head_t<T_Head_Types...>, T, Tail_t<>>>
		{
			using type = Tuple_tp<Head_t<T_Head_Types..., T>, std::nullopt_t, Tail_t<>>;
		};

		template< class T_Next_Type, class ...T_Tail_Types>
		struct S_Next<Tuple_tp<Head_t<>, std::nullopt_t, Tail_t<T_Next_Type, T_Tail_Types...>>>
		{
			using type = Tuple_tp<Head_t<>, T_Next_Type, Tail_t< T_Tail_Types...>>;
		};

	public:

		using type = S_Action_Tuple_tp<S_Next, T_Tuple_t>::type;

	};


}