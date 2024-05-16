#pragma once

#include"Tuple_Declare.h"

namespace quiet::N_Tuple
{
	//仕様
	//[Tuple_t]と互換性のある型のリストから、指定した型が何番目に含まれるか探す。
	//
	//テンプレート
	//[T_Search_Tuple]::指定した型を探す、[Tuple_t]と互換性のある型
	//[T_Search_Type]::[T_Search_Tuple]から探す型
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

		using type = S_Search_t<U_Change_Tuple_t<T_Search_Tuple>>::type;

	};

	//仕様
	//[Tuple_v]と互換性のある型のリストから、指定した値が何番目に含まれるか探す。
	//
	//テンプレート
	//[T_Search_Tuple]::指定した値を探す、[Tuple_v]と互換性のある型
	//[T_Search_Value]::[T_Search_Tuple]から探す型
	template<class T_Search_Tuple, auto t_Search_Value>
	struct I_Search_v
	{
		using type = I_Search_t<U_Change_Tuple_t<T_Search_Tuple>,
			integral_constant<t_Search_Value>>::type;
	};

}