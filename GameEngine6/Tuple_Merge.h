#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	//Žd—l
	//[T_Base_Tuple]‚ÌŒã‚ë‚É[T_Merge_Tuple]‚Ì—v‘f‚ð’Ç‰Á‚·‚é
	template<class T_Base_Tuple, class T_Merge_Tuple>
	struct I_Merge
	{
	private:

		using Merge_Tuple = typename Tuple_v_To_t<typename I_Remove_Pointer<T_Merge_Tuple>::Type>::Type;

		template<class T_Base_Tuple, class T_Merge_Tuple = Merge_Tuple>
		struct S_Merge;

		template<class T_Base_Head, class T_Base, class ...T_Base_Tail_Types,class ...T_Merge_Types>
		struct S_Merge<Tuple_tp<T_Base_Head, T_Base, Tail_t<T_Base_Tail_Types...>>,
			Tuple_t<T_Merge_Types...>>
		{
			using Type = Tuple_tp<T_Base_Head, T_Base,
				Tail_t< T_Base_Tail_Types..., T_Merge_Types...>>;
		};

		template<class T_Base_Head,class T_Merge_Flont_Type, class ...T_Merge_Types>
		struct S_Merge<Tuple_tp<T_Base_Head, std::nullopt_t, Tail_t<>>,
			Tuple_t<T_Merge_Flont_Type,T_Merge_Types...>>
		{
			using Type = Tuple_tp<T_Base_Head,T_Merge_Flont_Type,Tail_t<T_Merge_Types...>>;
		};

		using Action = S_Tuple_Action<S_Merge, T_Base_Tuple>;

		friend struct Action;

	public:

		using Type = typename Action::Type;
	};
}