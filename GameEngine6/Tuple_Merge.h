#pragma once

#include"Tuple_Declare.h"

namespace N_Tuple
{

	//d—l
	//[T_Base_Tuple]‚ÌŒã‚ë‚É[T_Add_Type...]‚Ì—v‘f‚ğ’Ç‰Á‚·‚é
	//
	//using
	//[tuple_expand]::[T_Add_type...]‚Ì’†‚Étuple‚ªŠÜ‚Ü‚ê‚éê‡Atuple‚ğ“WŠJ‚µAŠi”[‚·‚é
	template<class T_Base_Tuple, class ...T_Add_Type>
	struct I_Merge
	{
	private:




		template<class T_Base_Tuple,class T_Add_Types_Tuple = tuple_t<T_Add_Type...>, 
			class T_Merge_Tuple = U_Tuple_v_To_t<U_Remove_p<typename T_Add_Types_Tuple::type>>>
		struct S_Merge_Tuple_Expand
		{
			using type = T_Base_Tuple;
		};


		template<class ...T_Base_Types, class T_Add_Types_Tuple,not_is_invalid T_Merge_Types>
		struct S_Merge_Tuple_Expand<tuple_t<T_Base_Types...>,
			T_Add_Types_Tuple,T_Merge_Types>
		{
			using type = S_Merge_Tuple_Expand<
				tuple_t<T_Base_Types..., T_Merge_Types>,
				typename T_Add_Types_Tuple::next>::type;
		};

		template<class ...T_Base_Types,class T_Add_Types_Tuple, class ...T_Merge_Types>
		struct S_Merge_Tuple_Expand<tuple_t<T_Base_Types...>,
			T_Add_Types_Tuple,tuple_t<T_Merge_Types...>>
		{
			using type = S_Merge_Tuple_Expand<
				tuple_t<T_Base_Types..., T_Merge_Types...>,
				typename T_Add_Types_Tuple::next>::type;
		};

		template<class T_Base_Tuple>
		struct S_Merge_Tuple_Expand_Access;


		template<class T_Base_Head,class T_Merge_Front_Type, class ...T_Merge_Types>
		struct S_Merge_Tuple_Expand<tuple_tp<T_Base_Head, invalid_t, tuple_t<>>,
			tuple_t<T_Merge_Front_Type,T_Merge_Types...>>
		{
			using type = tuple_tp<T_Base_Head,T_Merge_Front_Type,tuple_t<T_Merge_Types...>>;
		};

		template<class T_Base_Tuple>
		struct S_Merge;

		template<class ...T_Types>
		struct S_Merge<tuple_t<T_Types...>>
		{
			using type = tuple_t<T_Types..., T_Add_Type...>;
		};


	public:

		using tuple_expand= S_Action_Tuple_tp<S_Merge_Tuple_Expand,T_Base_Tuple>::type;

		using type = S_Action_Tuple_t<S_Merge, T_Base_Tuple>::type;
	};
}