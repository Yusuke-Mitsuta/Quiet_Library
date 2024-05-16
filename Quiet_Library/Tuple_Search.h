#pragma once

#include"Tuple_Class_Declare.h"

namespace quiet::N_Tuple
{
	template<class T_Search_Tuple, class T_Search_Type>
	struct I_Search_t
	{

		template<class T_Tuple,size_t ...t_hit_Number>
		struct S_Search_t
		{
			using type = tuple_v<t_hit_Number...>;
		};
		
		template<class T_Tuple, size_t ...t_hit_Number>
			requires requires
		{
			requires same_as<typename T_Tuple::front_t, T_Search_Type>;
		}
		struct S_Search_t<T_Tuple,t_hit_Number...>
		{
			using type = S_Search_t<typename T_Tuple::next, 
				t_hit_Number..., T_Tuple::head_size>::type;
		};

		template<class T_Tuple, size_t ...t_hit_Number>
			requires requires
		{
			requires same_as_nor<typename T_Tuple::front_t, T_Search_Type,invalid_t>;
		}
		struct S_Search_t<T_Tuple, t_hit_Number...>
		{
			using type = S_Search_t<typename T_Tuple::next,
				t_hit_Number...>::type;
		};

		using type = S_Search_t<

	};


	template<class T_Tuple,class T_Search_Type>
	int Search();


}