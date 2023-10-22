#pragma once

#include"Concept.h"
#include"Parameter.h"

namespace N_Function
{

	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data;

	template<class ...T_Fn_Parts>
	struct IS_Function_Multiple_Helper;

	template<class ...T_Fn_Parts>
	struct IS_Function_Helper
	{
		using Single_Judge = S_Function_Single_Data<T_Fn_Parts...>;

		template<class T_Fn>
		struct S_Function_Helper
		{
			using Pointer_Judge = tuple_t<Single_Judge>;
			using Not_Pointer_Judge = tuple_t<Single_Judge>;
		};


		template<>
		struct S_Function_Helper<invalid_t>
		{
			using Pointer_Judge = IS_Function_Multiple_Helper<T_Fn_Parts...>::Pointer_Judge;
			using Not_Pointer_Judge = IS_Function_Multiple_Helper<T_Fn_Parts...>::Not_Pointer_Judge;
		};

		using Pointer_Judge = S_Function_Helper<typename
			Single_Judge::function>::Pointer_Judge;

		using Not_Pointer_Judge = S_Function_Helper<typename
			Single_Judge::method>::Not_Pointer_Judge;

	};


}