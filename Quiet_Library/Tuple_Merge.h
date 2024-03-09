/*!
 * Tuple_Merge.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{

	//d—l
	//[T_Insert_Base_Tuple]‚ÌŒã‚ë‚É[T_Merge_Types...]‚Ì—v‘f‚ğ’Ç‰Á‚·‚é
	//
	//using
	//[tuple_expand]::[T_Add_type...]‚Ì’†‚Étuple‚ªŠÜ‚Ü‚ê‚éê‡Atuple‚ğ“WŠJ‚µAŠi”[‚·‚é
	template<class T_Merge_Base_Tuple,class ...T_Merge_Types>
	struct I_Merge
	{
	private:

		template<class T_Base_Tuple, class T_Add_Types_Tuple = tuple_t<T_Merge_Types...>>
		struct S_Merge;

		template<class ...T_Types, class T_Add_Type>
		struct S_Merge<tuple_t<T_Types...>, T_Add_Type>
		{
			using type = tuple_t<T_Types..., T_Add_Type>;
		};

		template<class ...T_Types,class ...T_Add_Type>
		struct S_Merge<tuple_t<T_Types...>, tuple_t<T_Add_Type...>>
		{
			using type = tuple_t<T_Types..., T_Add_Type...>;
		};



		template<class T_Base_Tuple,class T_Add_Types_Tuple = tuple_t<T_Merge_Types...>, 
			class T_Merge_Tuple = U_Tuple_v_To_t<U_Remove_p<typename T_Add_Types_Tuple::type>>>
		struct S_Merge_Tuple_Expand
		{
			using type =
				S_Merge_Tuple_Expand<
				typename S_Merge<T_Base_Tuple, T_Merge_Tuple>::type,
				U_Next<T_Add_Types_Tuple>>::type;
		};

		template<class T_Base_Tuple, class T_Add_Types_Tuple>
		struct S_Merge_Tuple_Expand<T_Base_Tuple,T_Add_Types_Tuple,invalid_t>
		{
			using type = T_Base_Tuple;
		};

	public:

		using tuple_expand= S_Tuple_t_Change_Action<S_Merge_Tuple_Expand,T_Merge_Base_Tuple>::type;

		using type = S_Tuple_t_Change_Action<S_Merge, T_Merge_Base_Tuple>::type;
	};
}